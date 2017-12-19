{
    "targets":[
        { 
            "target_name":"addon",
            "sources":["addon.cpp","ini.cpp" ,"bstrlib.c"],
            "cflags": [ "-std=c++11" ],
            "include_dirs":[
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}