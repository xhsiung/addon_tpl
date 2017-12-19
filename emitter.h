#ifndef EMITTER_H
#define EMITTER_H

#include <nan.h>
using namespace v8;

class Emitter: public Nan::ObjectWrap {
public:
    Emitter();
    ~Emitter();
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(Add);
    static Nan::Persistent<Function> construct;
    Nan::Callback *emit = nullptr;

    static Emitter *instance;
    
};
#endif