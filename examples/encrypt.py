import gpgme
try:
    from io import BytesIO
except ImportError:
    from StringIO import StringIO as BytesIO

ctx = gpgme.Context()
ctx.armor = True

key = ctx.get_key('B10A449E4CFB9A60A2DB996701AF93D991CFA34D')

plain = BytesIO(b'Hello World\n')
cipher = BytesIO()

ctx.encrypt([key], 0, plain, cipher)

print(cipher.getvalue())
