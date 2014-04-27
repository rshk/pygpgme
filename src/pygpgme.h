/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
    pygpgme - a Python wrapper for the gpgme library
    Copyright (C) 2006  James Henstridge

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef PYGPGME_H
#define PYGPGME_H

#include <Python.h>
#include <gpgme.h>

/* Provide fallback definitions for older GPGME versions.  */
#if GPGME_VERSION_NUMBER < 0x010400
typedef enum
  {
    GPGME_PINENTRY_MODE_DEFAULT  = 0,
    GPGME_PINENTRY_MODE_ASK      = 1,
    GPGME_PINENTRY_MODE_CANCEL   = 2,
    GPGME_PINENTRY_MODE_ERROR    = 3,
    GPGME_PINENTRY_MODE_LOOPBACK = 4
  }
gpgme_pinentry_mode_t;
#endif /* GPGME < 1.4.0 */


#include "pycompat.h"

#define HIDDEN __attribute__((visibility("hidden")))

typedef struct {
    PyObject_HEAD
    gpgme_ctx_t ctx;
} PyGpgmeContext;

typedef struct {
    PyObject_HEAD
    gpgme_key_t key;
} PyGpgmeKey;

typedef struct {
    PyObject_HEAD
    gpgme_subkey_t subkey;
    PyObject *parent;
} PyGpgmeSubkey;

typedef struct {
    PyObject_HEAD
    gpgme_user_id_t user_id;
    PyObject *parent;
} PyGpgmeUserId;

typedef struct {
    PyObject_HEAD
    gpgme_key_sig_t key_sig;
    PyObject *parent;
} PyGpgmeKeySig;

typedef struct {
    PyObject_HEAD
    PyObject *type;
    PyObject *pubkey_algo;
    PyObject *hash_algo;
    PyObject *timestamp;
    PyObject *fpr;
    PyObject *sig_class;
} PyGpgmeNewSignature;

typedef struct {
    PyObject_HEAD
    PyObject *summary;
    PyObject *fpr;
    PyObject *status;
    PyObject *notations;
    PyObject *timestamp;
    PyObject *exp_timestamp;
    PyObject *wrong_key_usage;
    PyObject *validity;
    PyObject *validity_reason;
} PyGpgmeSignature;

typedef struct {
    PyObject_HEAD
    PyObject *considered;
    PyObject *no_user_id;
    PyObject *imported;
    PyObject *imported_rsa;
    PyObject *unchanged;
    PyObject *new_user_ids;
    PyObject *new_sub_keys;
    PyObject *new_signatures;
    PyObject *new_revocations;
    PyObject *secret_read;
    PyObject *secret_imported;
    PyObject *secret_unchanged;
    PyObject *skipped_new_keys;
    PyObject *not_imported;
    PyObject *imports;
} PyGpgmeImportResult;

typedef struct {
    PyObject_HEAD
    PyObject *primary;
    PyObject *sub;
    PyObject *fpr;
} PyGpgmeGenkeyResult;

typedef struct {
    PyObject_HEAD
    PyGpgmeContext *ctx;
} PyGpgmeKeyIter;

extern HIDDEN PyObject *pygpgme_error;
extern HIDDEN PyTypeObject PyGpgmeContext_Type;
extern HIDDEN PyTypeObject PyGpgmeKey_Type;
extern HIDDEN PyTypeObject PyGpgmeSubkey_Type;
extern HIDDEN PyTypeObject PyGpgmeUserId_Type;
extern HIDDEN PyTypeObject PyGpgmeKeySig_Type;
extern HIDDEN PyTypeObject PyGpgmeNewSignature_Type;
extern HIDDEN PyTypeObject PyGpgmeSignature_Type;
extern HIDDEN PyTypeObject PyGpgmeImportResult_Type;
extern HIDDEN PyTypeObject PyGpgmeGenkeyResult_Type;
extern HIDDEN PyTypeObject PyGpgmeKeyIter_Type;

HIDDEN int           pygpgme_check_error    (gpgme_error_t err);
HIDDEN PyObject     *pygpgme_error_object   (gpgme_error_t err);
HIDDEN gpgme_error_t pygpgme_check_pyerror  (void);
HIDDEN int           pygpgme_no_constructor (PyObject *self, PyObject *args,
                                             PyObject *kwargs);

HIDDEN int           pygpgme_data_new       (gpgme_data_t *dh, PyObject *fp);
HIDDEN PyObject     *pygpgme_key_new        (gpgme_key_t key);
HIDDEN PyObject     *pygpgme_newsiglist_new (gpgme_new_signature_t siglist);
HIDDEN PyObject     *pygpgme_siglist_new    (gpgme_signature_t siglist);
HIDDEN PyObject     *pygpgme_import_result  (gpgme_ctx_t ctx);
HIDDEN PyObject     *pygpgme_genkey_result  (gpgme_ctx_t ctx);

HIDDEN PyObject     *pygpgme_make_constants (PyObject *self, PyObject *args);

#endif
