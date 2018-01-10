var Stream = require("stream");
//var addon = require("bindings")("addon");
var addon = require("./addon");

for ( k in Stream.prototype ){
    addon.Emitter.prototype[k] = Stream.prototype[k];
}

addon.Emitter.prototype.myemit =  addon.myemit;
addon.Emitter.prototype.mytest = function(){
    console.log( "mytest");
}

// o.on("event" , function(data,data2){
//     console.log( data );
//     console.log( data2 );
// })

// o.add();
// o.myemit();
// o.mytest();

class My extends Stream {
    constructor(){
        super();
    }
}

emitter =  addon.Emitter();
var my = new My();

//export this
emitter.on("event", function(data){
    my.emit("event" , data , "test2") ;
});        

my.on("event", function(data , data2){
    console.log( data );
    console.log( data2 );
})

//test
emitter.myemit();
