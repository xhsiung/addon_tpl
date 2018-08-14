#include "libaddon.h"

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
