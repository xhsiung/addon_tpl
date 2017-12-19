#include "ini.h"

namespace INI{
    using namespace v8;
    using json = nlohmann::json;
    
    NAN_METHOD(Ini){
        char *fpath= strdup(*Nan::Utf8String(info[0]->ToString()));
        
        std::ifstream in( fpath);
        if ( !in.is_open()){
            std::cout << "file can not open" << std::endl;
            return ;
        }   
    
        std::string inputStr;
        std::vector<bstring> arrstr;
        bstring header;
        
        while ( getline(in ,inputStr)){
            bstring ss = bfromcstr( inputStr.c_str());
            btrimws( ss );
        
            int head = binstr( ss , 0 , bfromcstr("["));
            int tail = binstr( ss , 0 , bfromcstr("]"));
    
            int isblank = bstricmp(ss, bfromcstr("") );  
            if (isblank == 0 ) continue;
    
            if ( head > -1 && tail > -1){
                   header = bmidstr( ss , head+1, tail-head-1);
                   continue;
            }
    
            bstring tmp=bfromcstr("");
            bconcat( tmp , header);
            bconcat( tmp , bfromcstr("=")) ;
            bconcat( tmp , ss);
            arrstr.push_back( tmp );
        }   
    
        json root ,row;
        char* lastheader = ""; 
        for ( auto i= arrstr.begin();i!=arrstr.end();i++){
            bstrList *list =  bsplit( *i , '=');
        
            char* header =(char*)list->entry[0]->data ;
            char* xkey = (char*)list->entry[1]->data ;
            char* xvalue = (char*)list->entry[2]->data ;
        
            if ( strcmp( header , lastheader ) > 0 ){
                row = {};    
            }
        
            row[ xkey ] = xvalue;
            root[ header ] = row;
            lastheader = header;
        }

        //std::cout << root.dump() << std::endl;
        v8::Local<v8::String> jsonString = Nan::New( root.dump()).ToLocalChecked();
        
        Nan::JSON NanJSON;
        v8::Local<v8::Value> parsedValue = NanJSON.Parse(jsonString).ToLocalChecked();
        info.GetReturnValue().Set( parsedValue );
    }
}