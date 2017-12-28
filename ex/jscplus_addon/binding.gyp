{
    "targets":[
        {
            "target_name":"addon",
            "sources": ["addon.cpp"],
            "cflags":["-std=c++11"],
            "include_dirs":[
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}