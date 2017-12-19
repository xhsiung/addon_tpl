#include <nan.h>
#include "emitter.h"

using namespace v8;

NAN_METHOD(Show){
    int argc = 2;
    Local<Value> argv[argc] = {
        Nan::New("event").ToLocalChecked(),
        Nan::New("123").ToLocalChecked()
    };
    
    Emitter::instance->emit->Call( Emitter::instance->handle(), argc , argv );
    info.GetReturnValue().SetUndefined();
}

void Init(Local<Object> target){
    Nan::SetMethod( target , "show" , Show);
    Emitter::Init( target);
}

NODE_MODULE( addon , Init)