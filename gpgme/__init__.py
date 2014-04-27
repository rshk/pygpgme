# pygpgme - a Python wrapper for the gpgme library
# Copyright (C) 2006  James Henstridge
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

"""
PyGPGME, a Python wrapper for the GPGME library.

PyGPGME is a Python module that lets you sign, verify, encrypt and decrypt
messages using the OpenPGP format.

It is built on top of the GNU Privacy Guard and the GPGME library.

All interaction begins by creating a Context.
"""

from gpgme._gpgme import *

# create constants
make_constants(globals())
del make_constants
