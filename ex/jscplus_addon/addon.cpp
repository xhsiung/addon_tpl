#include <nan.h>
#include <stdio.h>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

using namespace v8;

NAN_METHOD(Add){
    info.GetReturnValue().SetUndefined();
}

//part1 JS --> C++
NAN_METHOD(setArg){
    if (info.Length() < 2 ){
        return Nan::ThrowTypeError("less parameter");
    }

    if (!info[0]->IsNumber() ){
        printf("not number\n");
    }
    
    if (!info[0]->IsObject()){
        printf("not Object\n");
    }
    
    if (!info[0]->IsBoolean()){
        printf("not Boolean\n");
    }

    if (!info[0]->IsArray()){
        printf("not Array\n");
    }
    
    if (!info[0]->IsString()){
        printf("not String\n");
    }

    if (!info[0]->IsFunction()){
        printf("not Funtion\n");
    }

    if (!info[0]->IsNull()){
        printf("not Null\n");
    }
    
    if (!info[0]->IsUndefined()){
        printf("not Undefiend\n");
    }


    //Local<Number> num= Number::New( info.GetIsolate() ,123);
    if (!info[1]->IsString()){
        return Nan::ThrowTypeError("info[1] is not String");
    }
    char *ss = strdup(*Nan::Utf8String(info[1]->ToString() ));
    printf("%s\n" , ss);

    
    //test info[2]  [1.1,2.2,3.3,4.4]
    if ( !info[2]->IsArray() ){
        return Nan::ThrowTypeError("info[2] is not array");
    }  
    Local<Array>  arr = Local<Array>::Cast(info[2]) ;
    for (unsigned i=0; i< arr->Length() ; i++){
        if ( Nan::Has( arr, i).FromJust() ){
            double v = Nan::Get( arr , i).ToLocalChecked()->NumberValue();
            printf("%.2f\n", v);
        }
    }


    //test info[3]  {}
    if (!info[3]->IsObject()){
        return Nan::ThrowTypeError("info[3] is not object");
    }

    //Get id
    Local<Object> jsobj =  info[3]->ToObject();
    Local<String> keyid = Nan::Get( jsobj, 
                                    Nan::New<String>("id").ToLocalChecked() 
                                   ).ToLocalChecked()->ToString();
    //Local<String> keyid = Local<String>::Cast( jsobj->Get( Nan::New<String>("id").ToLocalChecked() )) ;
    char *kid = strdup( *Nan::Utf8String( keyid ));
    printf("%s\n"  , kid);

    //Get data
    Local<Array> arr2 =Local<Array>::Cast( jsobj->Get( Nan::New("data").ToLocalChecked()) );
    for (unsigned i=0; i< arr2->Length() ; i++){
        if ( arr2->Has(i) ){
            Local<Object> o = arr2->Get(i)->ToObject();
            //Local<String> name = Local<String>::Cast( o->Get( Nan::New("name").ToLocalChecked()) );
            Local<String> name = Nan::To<String>( o->Get( Nan::New("name").ToLocalChecked()) ).ToLocalChecked();

            char *myname = strdup( *Nan::Utf8String( name ));
            printf("%s\n"  , myname);
        }
    }

    double value1 = Nan::To<double>(info[0]).FromJust();
    info.GetReturnValue().Set( value1 );
}


//part2  JS to C++
NAN_METHOD( setArg2 ){
    Nan::JSON NanJSON;
    Nan::MaybeLocal<String> jsonv8str = NanJSON.Stringify(info[0]->ToObject() );
    char *jsonstr = strdup( *Nan::Utf8String(  jsonv8str.ToLocalChecked() ) );
    auto jobj = json::parse(jsonstr);    
    std::cout << jobj["id"] << std::endl;
    
    json arr =  jobj["data"];
    for( json::iterator it= arr.begin(); it != arr.end(); ++it){
        json o = it.value();
        std::cout << o["name"] << std::endl;
    }

    info.GetReturnValue().SetUndefined();
}

//C++ to JS
NAN_METHOD( getArg ){
    Nan::JSON NanJSON;
    json obj,obj2,obj3,arr;
    //object
    obj["id"] = "002";
  
    //object
    obj2["name2"] = "alex02";
    obj2["name3"] = "alex03";
    obj3["name2"] = "alex022";
    obj3["name3"] = "alex033";
  
    //array object
    arr.push_back( obj2 );
    arr.push_back( obj3 );
    obj["data"] = arr;
    
    Local<String> jsonv8str = Nan::New( obj.dump()).ToLocalChecked();
    Local<Value> v = NanJSON.Parse( jsonv8str ).ToLocalChecked();
    info.GetReturnValue().Set( v );
}

void Init( Local<Object> target){
    Nan::SetMethod( target , "add" , Add);
    Nan::SetMethod( target , "setArg" , setArg);
    Nan::SetMethod( target , "setArg2" , setArg2);
    Nan::SetMethod( target , "getArg" , getArg);
}

NODE_MODULE( NODE_GYP_MODULE_NAME, Init)
