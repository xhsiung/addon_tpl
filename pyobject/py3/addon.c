#include <Python.h>
static PyObject *MyError;

// Function 1: A simple 'hello world' function
static PyObject* testHello(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_BuildValue("s","Hello");
}

static PyObject* testNum(PyObject* self,PyObject* args){
    float a,b,c;
    if ( ! PyArg_ParseTuple(args,"ff",&a, &b ) ){
        PyErr_SetString(MyError, "params error");
        return NULL;
    }
    c = a + b;
    return Py_BuildValue("f",c);
}

static PyObject* testKeywords(PyObject* self,PyObject* args , PyObject* kwargs){
    int x, a = 0, b = 0 ,res;

    // kwlist 裡存放 keyword 的名字，以 NULL 結束,  x=1,a=2,b=3
    static char *kwlist[] = {"x", "a", "b", NULL};  

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii", kwlist, &x, &a, &b)) {
        return NULL;
    }
    res = x + a + b;
    return Py_BuildValue("i", res );
}

static PyObject* testTouple(PyObject* self,PyObject* args){
    PyObject* pTuple;
    
    if (! PyArg_ParseTuple(args, "O!", &PyTuple_Type, &pTuple) ){
        PyErr_SetString(MyError, "params error");
        return NULL;
    }

    for (int i = 0; i < PyTuple_Size(pTuple) ; i++) {       
       PyObject* item = PyTuple_GetItem(pTuple, i);
       if (!PyLong_Check(item)) continue;
       long value = PyLong_AsLong(item);
       printf("%ld\n", value );
    }

    return Py_BuildValue("(ii)",222,333);
}

static PyObject* testList(PyObject* self,PyObject* args){
    PyObject* pList;
    
    if (! PyArg_ParseTuple(args, "O!", &PyList_Type, &pList) ){
        PyErr_SetString(MyError, "params error");
        return NULL;
    }

    for (int i = 0; i < PyList_Size(pList) ; i++) {       
       PyObject* item = PyList_GetItem(pList, i);
       if (!PyLong_Check(item)) continue;
       long value = PyLong_AsLong(item);
       printf("%ld\n", value );
    }

    return Py_BuildValue("[ii]",444,555);
}


static PyObject* testDict(PyObject* self,PyObject* args){
    PyObject* pDict;

    if (! PyArg_ParseTuple(args, "O!", &PyDict_Type, &pDict) ){
        return NULL;
    }

    
    PyObject* name1 = PyDict_GetItemString( pDict, "name1");
    char* nameValue1 = PyUnicode_AsUTF8(name1);
    printf("%s\n", nameValue1);

    PyObject* name2 = PyDict_GetItemString( pDict, "name2");
    char* nameValue2 = PyUnicode_AsUTF8(name2);
    printf("%s\n", nameValue2);

    return Py_BuildValue("{s:i,s:i}","abc", 123, "def", 456);
}


// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition 
//注意 若要return dict,一定要加METH_KEYWORDS
static PyMethodDef myMethods[] = {
    { "testHello", testHello, METH_NOARGS, "testHello" },
    { "testNum", testNum, METH_VARARGS, "testNum" },
    { "testKeywords", testKeywords, METH_VARARGS | METH_KEYWORDS, "testKeywords"},
    { "testTouple", testTouple, METH_VARARGS | METH_KEYWORDS , "testTouple"},
    { "testList", testList, METH_VARARGS | METH_KEYWORDS , "testList"},
    { "testDict", testDict, METH_VARARGS | METH_KEYWORDS , "testDict"},
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

// Initializes our module using our above struct
//PyInit_模組名稱 重要
PyMODINIT_FUNC PyInit_addon(void){
    return PyModule_Create(&myModule);
}
