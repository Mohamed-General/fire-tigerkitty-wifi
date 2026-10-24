import sys, zipfile, os, hashlib

zip_path = r"C:\Users\GENERAL\AppData\Local\Temp\opencode\fire_rom\crdroid-fire-12.12.zip"
work = r"C:\Users\GENERAL\AppData\Local\Temp\opencode\fire_ota"
os.makedirs(work, exist_ok=True)

z = zipfile.ZipFile(zip_path)
print("=== entries ===")
for i in z.infolist():
    print(f"{i.filename:50s} {i.file_size:>12,}")

print("\n=== CRC test (reads whole zip) ===")
bad = z.testzip()
print("bad file:", bad if bad else "OK - all CRCs valid")

# extract payload.bin
targets = [n for n in z.namelist() if n.endswith("payload.bin")]
if targets:
    name = targets[0]
    out = os.path.join(work, "payload.bin")
    if os.path.exists(out) and os.path.getsize(out) == z.getinfo(name).file_size:
        print("payload.bin already extracted")
    else:
        print(f"extracting {name} -> {out} ...")
        with z.open(name) as src, open(out, "wb") as dst:
            while True:
                chunk = src.read(1 << 20)
                if not chunk:
                    break
                dst.write(chunk)
        print("done, size:", os.path.getsize(out))
else:
    print("no payload.bin found")
