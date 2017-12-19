{
    "targets":[
        {
            "target_name": "addon",
            "sources":[ "addon.cpp","emitter.cpp"],
            "include_dirs":[
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}