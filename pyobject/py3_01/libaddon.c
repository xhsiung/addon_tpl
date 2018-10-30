#include "libaddon.h"

 PyObject *MyError;

// Function 1: A simple 'hello world' function
 PyObject* testHello(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_BuildValue("s","Hello");
}

 PyObject* testNum(PyObject* self,PyObject* args){
    float a,b,c;
    if ( ! PyArg_ParseTuple(args,"ff",&a, &b ) ){
        PyErr_SetString(MyError, "params error");
        return NULL;
    }
    c = a + b;
    return Py_BuildValue("f",c);
}

 PyObject* testKeywords(PyObject* self,PyObject* args , PyObject* kwargs){
    int x, a = 0, b = 0 ,res;

    // kwlist 裡存放 keyword 的名字，以 NULL 結束,  x=1,a=2,b=3
    static char *kwlist[] = {"x", "a", "b", NULL};  

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii", kwlist, &x, &a, &b)) {
        return NULL;
    }
    res = x + a + b;
    return Py_BuildValue("i", res );
}

 PyObject* testTouple(PyObject* self,PyObject* args){
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

 PyObject* testList(PyObject* self,PyObject* args){
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


 PyObject* testDict(PyObject* self,PyObject* args){
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

    // printf("%s\n", test);

    // printf("run add3\n");
    
    // PyObject* list = PyList_New(0);
    // PyList_Append( list , Py_BuildValue("i",1));
    // PyList_Append( list , Py_BuildValue("i",3));
    // PyList_Append( list , Py_BuildValue("i",5));
    //PyList_Insert(list, 0, Py_BuildValue("i", "inserted"));

    //PyObject* list = PyTuple_New(0);
    //PyObject* list = Py_BuildValue("(ii)", 11,22) ;

    //PyObject* list = PyList_New(3);
    // PyList_SetItem(list,0, Py_BuildValue("i",1) );
    // PyList_SetItem(list,1, Py_BuildValue("i",2) );
    // PyList_SetItem(list,2, Py_BuildValue("i",4) );

    //show
    //for (int i = 0; i < PyList_Size(list) ; i++) {
    // for (int i = 0; i < PyTuple_Size(list) ; i++) {        
    //     //PyObject* item = PyList_GetItem(list, i); 
    //     PyObject* item = PyTuple_GetItem(list, i); 

    //     if (!PyLong_Check(item)) continue; 
    //     long value = PyLong_AsLong(item);
    //     printf("%d\n", value );
    // }
    

    // PyObject* dict2 = PyDict_New();
    // PyDict_SetItem(dict2 , Py_BuildValue("s","name"), Py_BuildValue("i",123456));
    // PyObject* name2 = PyDict_GetItemString( dict2, "name");
    
    // //char* test2 = PyUnicode_AsUTF8(name2);
    // long test2 = PyLong_AS_LONG( name2);
    // printf("---->%ld\n" , test2);

    
    return Py_BuildValue("{s:i,s:i}","abc", 123, "sum", 456);
}
