"""Extract kernel from an Android boot image (header v3/v4) and pull:
 - the kernel release string ("Linux version ...")
 - the vermagic string
 - the embedded kernel config (/proc/config.gz blob, CONFIG_IKCONFIG)
"""
import sys, struct, re, gzip, io, os

def parse_boot(path):
    d = open(path, "rb").read()
    if d[:8] != b"ANDROID!":
        raise SystemExit(f"{path}: not an Android boot image")
    kernel_size, ramdisk_size, os_version, header_size = struct.unpack_from("<IIII", d, 8)
    header_version = struct.unpack_from("<I", d, 40)[0]
    cmdline_len = 1536 if header_version >= 3 else 512
    cmdline = d[48:48+cmdline_len].split(b"\x00")[0].decode(errors="replace")
    # v3/v4 images align the kernel to the page size after the header
    page = 4096
    koff = header_size if header_version < 3 else ((header_size + page - 1) // page) * page
    if d[koff:koff + 2] != b"\x1f\x8b" and header_version >= 3:
        # fall back: find first page-aligned gzip/Image
        probe = ((header_size + page - 1) // page) * page
        koff = probe
    kernel = d[koff:koff+kernel_size]
    ramdisk = d[koff+kernel_size:koff+kernel_size+ramdisk_size]
    return dict(data=d, header_version=header_version, header_size=header_size,
                kernel_size=kernel_size, ramdisk_size=ramdisk_size,
                cmdline=cmdline, kernel=kernel, ramdisk=ramdisk)

def find_gzip_blobs(buf):
    """yield (offset, decompressed) for every gzip stream that decompresses."""
    i = 0
    while True:
        i = buf.find(b"\x1f\x8b\x08", i)
        if i < 0:
            return
        try:
            out = gzip.GzipFile(fileobj=io.BytesIO(buf[i:])).read()
            yield i, out
            i += 2
        except Exception:
            i += 3

def main():
    path = sys.argv[1]
    outdir = sys.argv[2] if len(sys.argv) > 2 else "."
    b = parse_boot(path)
    print(f"header v{b['header_version']}  header_size={b['header_size']}  kernel={b['kernel_size']:,}  ramdisk={b['ramdisk_size']:,}")
    print(f"cmdline: {b['cmdline']}")

    k = b["kernel"]
    print(f"kernel magic: {k[:4].hex()}")
    if k[:2] == b"\x1f\x8b":
        img = gzip.decompress(k)
        open(os.path.join(outdir, "Image"), "wb").write(img)
        print(f"decompressed Image: {len(img):,} bytes -> Image")
    else:
        img = k
        open(os.path.join(outdir, "Image"), "wb").write(img)

    m = re.findall(rb"Linux version [^\x00]{0,200}", img)
    for x in m[:2]:
        print("RELEASE:", x.decode(errors="replace"))
    vm = set(re.findall(rb"[0-9]+\.[0-9]+\.[0-9]+[^\x00\x20]{0,40} SMP[^\x00]{0,60}", img))
    for x in list(vm)[:3]:
        print("VERMAGIC:", x.decode(errors="replace"))

    # embedded config (IKCONFIG): search gzip streams whose payload looks like a kconfig
    found = 0
    for off, out in find_gzip_blobs(img):
        if b"CONFIG_" in out[:200000] and b"Automatically generated" in out[:2000]:
            p = os.path.join(outdir, "config-gki.txt")
            open(p, "wb").write(out)
            print(f"CONFIG: found at 0x{off:x}, {len(out):,} bytes -> {p}")
            found += 1
            break
    if not found:
        print("CONFIG: not found in image")

if __name__ == "__main__":
    main()
