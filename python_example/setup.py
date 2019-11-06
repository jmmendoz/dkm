from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

connector_extension = Extension(
    name="connector",
    sources=["connector.pyx"],
    libraries=["dkm.hpp"],
    library_dirs=["../include"],
    include_dirs=["../include"]
)
setup(
    name="connector",
    ext_modules=cythonize([connector_extension])
)