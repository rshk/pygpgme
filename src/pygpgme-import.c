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
#include "pygpgme.h"
#include <structmember.h>

static void
pygpgme_import_dealloc(PyGpgmeImportResult *self)
{
    Py_XDECREF(self->considered);
    Py_XDECREF(self->no_user_id);
    Py_XDECREF(self->imported);
    Py_XDECREF(self->imported_rsa);
    Py_XDECREF(self->unchanged);
    Py_XDECREF(self->new_user_ids);
    Py_XDECREF(self->new_sub_keys);
    Py_XDECREF(self->new_signatures);
    Py_XDECREF(self->new_revocations);
    Py_XDECREF(self->secret_read);
    Py_XDECREF(self->secret_imported);
    Py_XDECREF(self->secret_unchanged);
    Py_XDECREF(self->skipped_new_keys);
    Py_XDECREF(self->not_imported);
    Py_XDECREF(self->imports);
    PyObject_Del(self);
}

static PyMemberDef pygpgme_import_members[] = {
    { "considered", T_OBJECT, offsetof(PyGpgmeImportResult, considered), READONLY},
    { "no_user_id", T_OBJECT, offsetof(PyGpgmeImportResult, no_user_id), READONLY},
    { "imported", T_OBJECT, offsetof(PyGpgmeImportResult, imported), READONLY},
    { "imported_rsa", T_OBJECT, offsetof(PyGpgmeImportResult, imported_rsa), READONLY},
    { "unchanged", T_OBJECT, offsetof(PyGpgmeImportResult, unchanged), READONLY},
    { "new_user_ids", T_OBJECT, offsetof(PyGpgmeImportResult, new_user_ids), READONLY},
    { "new_sub_keys", T_OBJECT, offsetof(PyGpgmeImportResult, new_sub_keys), READONLY},
    { "new_signatures", T_OBJECT, offsetof(PyGpgmeImportResult, new_signatures), READONLY},
    { "new_revocations", T_OBJECT,
      offsetof(PyGpgmeImportResult, new_revocations), READONLY},
    { "secret_read", T_OBJECT,
      offsetof(PyGpgmeImportResult, secret_read), READONLY},
    { "secret_imported", T_OBJECT,
      offsetof(PyGpgmeImportResult, secret_imported), READONLY},
    { "secret_unchanged", T_OBJECT,
      offsetof(PyGpgmeImportResult, secret_unchanged), READONLY},
    { "skipped_new_keys", T_OBJECT,
      offsetof(PyGpgmeImportResult, skipped_new_keys), READONLY},
    { "not_imported", T_OBJECT,
      offsetof(PyGpgmeImportResult, not_imported), READONLY},
    { "imports", T_OBJECT, offsetof(PyGpgmeImportResult, imports), READONLY},
    { NULL, 0, 0, 0}
};

PyTypeObject PyGpgmeImportResult_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "gpgme.Import",
    sizeof(PyGpgmeImportResult),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_init = pygpgme_no_constructor,
    .tp_dealloc = (destructor)pygpgme_import_dealloc,
    .tp_members = pygpgme_import_members,
};

PyObject *
pygpgme_import_result(gpgme_ctx_t ctx)
{
    gpgme_import_result_t result;
    gpgme_import_status_t status;
    PyGpgmeImportResult *self;

    result = gpgme_op_import_result(ctx);

    if (result == NULL)
        Py_RETURN_NONE;

    self = PyObject_New(PyGpgmeImportResult, &PyGpgmeImportResult_Type);
    if (!self)
        return NULL;

#define ADD_INT(name) \
    self->name = PyInt_FromLong(result->name)

    ADD_INT(considered);
    ADD_INT(no_user_id);
    ADD_INT(imported);
    ADD_INT(imported_rsa);
    ADD_INT(unchanged);
    ADD_INT(new_user_ids);
    ADD_INT(new_sub_keys);
    ADD_INT(new_signatures);
    ADD_INT(new_revocations);
    ADD_INT(secret_read);
    ADD_INT(secret_imported);
    ADD_INT(secret_unchanged);
    ADD_INT(skipped_new_keys);
    ADD_INT(not_imported);

    self->imports = PyList_New(0);
    if (!self->imports)
        return NULL;
    for (status = result->imports; status != NULL; status = status->next) {
        PyObject *py_fpr, *item;

        if (status->fpr)
            py_fpr = PyUnicode_DecodeASCII(status->fpr, strlen(status->fpr),
                                           "replace");
        else {
            py_fpr = Py_None;
            Py_INCREF(py_fpr);
        }
        item = Py_BuildValue("(NNi)",
                             py_fpr,
                             pygpgme_error_object(status->result),
                             status->status);
        if (!item) {
            Py_DECREF(self);
            return NULL;
        }
        PyList_Append(self->imports, item);
        Py_DECREF(item);
    }
    
    return (PyObject *)self;
}
