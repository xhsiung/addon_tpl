var addon = require('bindings')('addon');
addon.add();

addon.setArg(2.1, 
            "i love you",
            [1.1,2.2,3.3,4.4],
            {   id : "001",
                data:[
                    {name:"alex"},
                    {name:"alex2"},
                ]
            }
    );

addon.setArg2( 
    {   id : "001",
        data:[
        {name:"alex"},
        {name:"alex2"}, 
    ]
});

console.log( addon.getArg() );