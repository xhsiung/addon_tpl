#ifndef __LIBADDON_H__
#define __LIBADDON_H__
#include <Python.h>

PyObject* testHello(PyObject* self, PyObject* args);
PyObject* testNum(PyObject* self,PyObject* args);
PyObject* testKeywords(PyObject* self,PyObject* args , PyObject* kwargs);
PyObject* testTouple(PyObject* self,PyObject* args);
PyObject* testList(PyObject* self,PyObject* args);
PyObject* testDict(PyObject* self,PyObject* args);

#endif
