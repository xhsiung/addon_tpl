var addon = require("bindings")("addon");
addon.add();
var ini = addon.ini("config.ini");
console.log(ini);

