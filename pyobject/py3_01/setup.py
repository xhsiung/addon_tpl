from distutils.core import setup, Extension

setup(name = 'addon', version = '1.0',  \
   ext_modules = [
       Extension('addon', ['addon.c','libaddon.c'], 
        #-I
        include_dirs=[],
        #header
        depends=[] )
       ]
    )
