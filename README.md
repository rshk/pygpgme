# PyGPGME

**Note:** This is a fork of the original project hosted on launchpad.
The goal here is mainly to add docstrings to methods and generate some
actual documentation of the Python library (w/o making users guess
arguments by reading documentation of the C library..)

## Documentation

http://pygpgme.readthedocs.org/en/latest/

## About pygpgme

A Python binding for the gpgme library, used to drive the gpg command
line program.

More information about gpgme can be found here:
  http://www.gnupg.org/related_software/gpgme/index.html

This binding stays fairly close to the C API with the following
exceptions:

 * Memory management is not exposed to the user

 * Functions like gpgme_get_foo()/gpgme_set_foo() are converted to
   attribute access on gpgme.Context objects.

 * Functions that take gpgme_data_t arguments take arbitrary Python
   file-like objects.  The read(), write(), seek() and tell() methods
   may be used on the object.

 * Non-zero gpgme_error_t return values are converted to gpgme.error
   exceptions.

 * Only the synchronous versions of functions have been wrapped.
   However, the Python global interpreter lock is dropped, so should
   play nicely in multi-threaded Python programs.

 * Function pairs like gpgme_op_import()/gpgme_op_import_result() are
   combined into single method calls.

 * The Python version of gpgme_op_keylist() returns an iterator over
   the matched keys, rather than requiring the user to use a special
   iteration function.

This library is licensed under the LGPL, the same license as the gpgme
library.
