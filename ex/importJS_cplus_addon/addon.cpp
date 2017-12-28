#include <nan.h>
#include <iostream>
using namespace v8;

//Persistent<Object> perObj;
Nan::Persistent<Object> xperObj;

NAN_METHOD( Import ){
    Local<Object> obj = info[0]->ToObject();

    //set global variables
    //perObj.Reset( info.GetIsolate() , obj );
    xperObj.Reset( obj );
}

NAN_METHOD( Show ){
    Local<Object> xobj = Nan::New<Object>( xperObj );
    Local<Function> cb = Local<Function>::Cast( xobj->Get(Nan::New("show").ToLocalChecked()) ) ;    
    int argc = 1;
    Local<Value> argv[argc] = {
        Nan::New("alex").ToLocalChecked()
    };
    
    Nan::MakeCallback(info.This(), cb , argc ,argv );
}

NAN_METHOD( CallEmit ){
    Local<Object> xobj = Nan::New<Object>( xperObj );
    int argc2 = 2;
    Local<Value> argv2[argc2] = {
        Nan::New("event").ToLocalChecked(),
        Nan::New("mytest").ToLocalChecked()
    };

    Nan::MakeCallback(xobj, "emit", argc2 , argv2 );
}


void Init(Local<Object> target){
    Nan::SetMethod( target , "import" , Import);
    Nan::SetMethod( target , "show" , Show);
    Nan::SetMethod( target , "callemit" , CallEmit);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
