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
#include <Python.h>
#include <errno.h>
#include "pygpgme.h"

/* called when a Python exception is set.  Clears the exception and tries
 * to set errno appropriately. */
static void
set_errno(void)
{
    PyObject *exc, *value, *tb, *py_errno;

    PyErr_Fetch(&exc, &value, &tb);

    /* if we have an IOError, try and get the actual errno */
    if (PyErr_GivenExceptionMatches(exc, PyExc_IOError) && value != NULL) {
        py_errno = PyObject_GetAttrString(value, "errno");
        if (py_errno != NULL && PyInt_Check(py_errno)) {
            errno = PyInt_AsLong(py_errno);
        } else {
            PyErr_Clear();
            errno = EINVAL;
        }
        Py_XDECREF(py_errno);
    } else {
        errno = EINVAL;
    }
    Py_XDECREF(tb);
    Py_XDECREF(value);
    Py_DECREF(exc);
}

static ssize_t
read_cb(void *handle, void *buffer, size_t size)
{
    PyGILState_STATE state;
    PyObject *fp = handle;
    PyObject *result;
    int result_size;

    state = PyGILState_Ensure();
    result = PyObject_CallMethod(fp, "read", "l", (long)size);
    /* check for exceptions or non-string return values */
    if (result == NULL) {
        set_errno();
        result_size = -1;
        goto end;
    }
    /* if we don't have a string return value, consider that an error too */
    if (!PyBytes_Check(result)) {
        Py_DECREF(result);
        errno = EINVAL;
        result_size = -1;
        goto end;
    }
    /* copy the result into the given buffer */
    result_size = PyBytes_Size(result);
    if (result_size > size)
        result_size = size;
    memcpy(buffer, PyBytes_AsString(result), result_size);
    Py_DECREF(result);
 end:
    PyGILState_Release(state);
    return result_size;
}

static ssize_t
write_cb(void *handle, const void *buffer, size_t size)
{
    PyGILState_STATE state;
    PyObject *fp = handle;
    PyObject *py_buffer = NULL;
    PyObject *result = NULL;
    ssize_t bytes_written = -1;

    state = PyGILState_Ensure();
    py_buffer = PyBytes_FromStringAndSize(buffer, size);
    if (py_buffer == NULL) {
        set_errno();
        goto end;
    }
    result = PyObject_CallMethod(fp, "write", "O", py_buffer);
    if (result == NULL) {
        set_errno();
        goto end;
    }
    bytes_written = size;
 end:
    Py_XDECREF(result);
    Py_XDECREF(py_buffer);
    PyGILState_Release(state);
    return bytes_written;
}

static off_t
seek_cb(void *handle, off_t offset, int whence)
{
    PyGILState_STATE state;
    PyObject *fp = handle;
    PyObject *result;

    state = PyGILState_Ensure();
    result = PyObject_CallMethod(fp, "seek", "li", (long)offset, whence);
    if (result == NULL) {
        set_errno();
        offset = -1;
        goto end;
    }
    Py_DECREF(result);

    /* now get the file location */
    result = PyObject_CallMethod(fp, "tell", NULL);
    if (result == NULL) {
        set_errno();
        offset = -1;
        goto end;
    }
    if (!PyInt_Check(result)) {
        Py_DECREF(result);
        errno = EINVAL;
        offset = -1;
        goto end;
    }
    offset = PyInt_AsLong(result);
    Py_DECREF(result);
 end:
    PyGILState_Release(state);
    return offset;
}

static void
release_cb(void *handle)
{
    PyGILState_STATE state;
    PyObject *fp = handle;

    state = PyGILState_Ensure();
    Py_DECREF(fp);
    PyGILState_Release(state);
}

static struct gpgme_data_cbs python_data_cbs = {
    .read    = read_cb,
    .write   = write_cb,
    .seek    = seek_cb,
    .release = release_cb,
};

/* create a gpgme data object wrapping a Python file like object */
int
pygpgme_data_new(gpgme_data_t *dh, PyObject *fp)
{
    gpgme_error_t error;

    if (fp == Py_None) {
        *dh = NULL;
        return 0;
    }

    error = gpgme_data_new_from_cbs(dh, &python_data_cbs, fp);

    if (pygpgme_check_error(error)) {
        *dh = NULL;
        return -1;
    }

    /* if no error, then the new gpgme_data_t object owns a reference to
     * the python object */
    Py_INCREF(fp);
    return 0;
}
