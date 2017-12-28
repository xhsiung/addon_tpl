#ifndef INI_H_
#define INI_H_

#include <nan.h>
#include <iostream>
#include <fstream>

#include "json.hpp"

extern "C"{
    #include "bstrlib.h"
}

namespace INI{
    NAN_METHOD(Ini);
}

#endif