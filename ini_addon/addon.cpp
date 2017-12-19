#include <nan.h>
#include "ini.h"

using namespace v8;

NAN_METHOD(Add){
    info.GetReturnValue().SetUndefined();    
}

void Init(Local<Object> target){
    Nan::SetMethod(target , "add" , Add);
    Nan::SetMethod(target , "ini" , INI::Ini);
}

NODE_MODULE( addon , Init);