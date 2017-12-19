#include "emitter.h"
Nan::Persistent<Function> Emitter::construct;
Emitter *Emitter::instance = nullptr;

Emitter::Emitter(){}
Emitter::~Emitter(){
    if ( instance != nullptr){
	delete emit;
        delete instance;
    }
}

NAN_MODULE_INIT(Emitter::Init){
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>( New );
    tpl->SetClassName( Nan::New("Emitter").ToLocalChecked() );
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl , "add" , Add );
    construct.Reset( tpl->GetFunction() );

    target->Set( Nan::New("Emitter").ToLocalChecked() , tpl->GetFunction());
}

NAN_METHOD(Emitter::New){
    if (info.IsConstructCall()){
        Emitter *obj = new Emitter();
        obj->Wrap( info.This());
        obj->instance = obj ;

        obj->emit = new Nan::Callback( Local<Function>::Cast( obj->handle()->Get( Nan::New("emit").ToLocalChecked()) ));
        info.GetReturnValue().Set( info.This() );
    }else{
        const int argc = 1;
        Local<Value> argv[argc] = {info[0]};
        Local<Function> cons = Nan::New<Function>(construct);
        info.GetReturnValue().Set( cons->NewInstance(argc , argv ));
    }
}

NAN_METHOD(Emitter::Add){
    Emitter *obj = Nan::ObjectWrap::Unwrap<Emitter>( info.Holder());
    int argc = 2;
    Local<Value> argv[argc] = {
        Nan::New("event").ToLocalChecked(),
        Nan::New("xxxx").ToLocalChecked()
    };
    obj->emit->Call( obj->handle(), argc , argv );
    info.GetReturnValue().SetUndefined();
}
