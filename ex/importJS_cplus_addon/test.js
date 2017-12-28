var addon = require('bindings')('addon');
var EventEmitter = require("events");

class My extends EventEmitter{
    constructor(){
        super();
        console.log("init");
    }

    show( data ){
        console.log("show:" + data);
    }
}

var o = new My();
o.on("event" , (data )=>{
    console.log("test:" + data);
});

//import
addon.import(o);
//method show
addon.show();
//call emit
addon.callemit();