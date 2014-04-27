
#ifndef PYGPGME_COMPAT_H
#define PYGPGME_COMPAT_H

#if PY_VERSION_HEX < 0x02060000

#  define PyVarObject_HEAD_INIT(type, size) \
          PyObject_HEAD_INIT(type) size,
#  define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)


#  define PyBytesObject PyStringObject
#  define PyBytes_Type PyString_Type

#  define PyBytes_Check PyString_Check
#  define PyBytes_CheckExact PyString_CheckExact 
#  define PyBytes_CHECK_INTERNED PyString_CHECK_INTERNED
#  define PyBytes_AS_STRING PyString_AS_STRING
#  define PyBytes_GET_SIZE PyString_GET_SIZE
#  define Py_TPFLAGS_BYTES_SUBCLASS Py_TPFLAGS_STRING_SUBCLASS

#  define PyBytes_FromStringAndSize PyString_FromStringAndSize
#  define PyBytes_FromString PyString_FromString
#  define PyBytes_FromFormatV PyString_FromFormatV
#  define PyBytes_FromFormat PyString_FromFormat
#  define PyBytes_Size PyString_Size
#  define PyBytes_AsString PyString_AsString
#  define PyBytes_Repr PyString_Repr
#  define PyBytes_Concat PyString_Concat
#  define PyBytes_ConcatAndDel PyString_ConcatAndDel
#  define PyBytes_Format PyString_Format
#  define PyBytes_DecodeEscape PyString_DecodeEscape
#  define PyBytes_Decode PyString_Decode
#  define PyBytes_Encode PyString_Encode
#  define PyBytes_AsEncodedObject PyString_AsEncodedObject
#  define PyBytes_AsEncodedString PyString_AsEncodedString
#  define PyBytes_AsDecodedObject PyString_AsDecodedObject
#  define PyBytes_AsDecodedString PyString_AsDecodedString
#  define PyBytes_AsStringAndSize PyString_AsStringAndSize

#endif

#if PY_VERSION_HEX > 0x03000000
/* Ugh.  I'll need to fix this code, but the text/bytes changes take
   precedence. */
#  define PyInt_Check PyLong_Check
#  define PyInt_FromLong PyLong_FromLong
#  define PyInt_AsLong PyLong_AsLong
#endif

#endif /* PYGPGME_COMPAT_H */
