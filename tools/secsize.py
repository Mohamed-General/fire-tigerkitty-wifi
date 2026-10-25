#!/usr/bin/env python3
"""Print the size (decimal + hex) of .gnu.linkonce.this_module in a .ko file.

The kernel refuses (and on this MTK tree: panics) when this section size does
not equal sizeof(struct module) of the running kernel.
"""
import struct
import sys


def this_module_size(path):
    d = open(path, "rb").read()
    if d[:4] != b"\x7fELF":
        raise SystemExit("%s: not an ELF file" % path)
    is64 = d[4] == 2
    if not is64:
        raise SystemExit("%s: not a 64-bit ELF" % path)
    shoff, = struct.unpack_from("<Q", d, 0x28)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x3A)
    stroff, = struct.unpack_from("<Q", d, shoff + shstrndx * shentsize + 0x18)
    for i in range(shnum):
        base = shoff + i * shentsize
        nameoff, = struct.unpack_from("<I", d, base)
        size, = struct.unpack_from("<Q", d, base + 0x20)
        name = d[stroff + nameoff:d.index(b"\x00", stroff + nameoff)].decode()
        if name == ".gnu.linkonce.this_module":
            return size
    return None


if __name__ == "__main__":
    for f in sys.argv[1:]:
        s = this_module_size(f)
        print("%-28s this_module=%s (0x%x)" % (f.split("/")[-1], s, s or 0))
