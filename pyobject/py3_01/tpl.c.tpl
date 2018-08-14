#include <Python.h>
static PyObject *MyError;

// Function 1: A simple 'hello world' function
static PyObject* mytest(PyObject* self, PyObject* args)
{
    char name[128];
    if ( ! PyArg_ParseTuple(args,"s",name ) ){
        PyErr_SetString(MyError, "params error");
        return NULL;
    }
    printf("Hello World\n");
    return Py_BuildValue("s","Hello");
}


//注意 若要return dict,一定要加METH_KEYWORDS
static PyMethodDef myMethods[] = {
    { "mytest", mytest, METH_VARARGS | METH_KEYWORDS , "mytest"},
    { NULL, NULL, 0, NULL }
};


// Our Module Definition struct
static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "myModule",
    "Test Module",
    -1,
    myMethods
};

//PyInit_模組名稱 重要
PyMODINIT_FUNC PyInit_addon(void){
    return PyModule_Create(&myModule);
}
