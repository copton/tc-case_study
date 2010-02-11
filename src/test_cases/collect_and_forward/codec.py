import struct
from cStringIO import StringIO

format="!i"
sizeofInt = struct.calcsize(format)
assert (sizeofInt == 4)

def encode(vals):
    buf = StringIO()
    for val in vals:
        buf.write(struct.pack(format, val))

    bytes = buf.getvalue()
    buf.close()
    return bytes

def decode(bytes):
    assert (len(bytes) % sizeofInt) == 0, "format error: %d" % len(bytes)
    return [struct.unpack(format, bytes[i:i+sizeofInt])[0] for i in range(0, len(bytes), sizeofInt)]

