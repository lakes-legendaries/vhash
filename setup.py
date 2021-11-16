from glob import glob
from os import path
from setuptools import find_packages, setup

from pybind11.setup_helpers import build_ext, Pybind11Extension


# setup script
if __name__ == '__main__':

    # get files
    cxx_files = glob('cxx/utils/*.cxx')
    cxx_files.extend(glob('cxx/vhash/*.cxx'))
    cxx_files.append('cxx/pybind.cxx')

    # run setup
    setup(

        # standard info
        name='vhash',
        version='0.0.16',
        description='hash tables for vectorizing text-based documents',
        author='Mike Powell PhD',
        author_email='mike@lakeslegendaries.com',

        # longer info
        long_description=open('README.rst').read(),
        license=open('LICENSE').read(),

        # packages to include
        packages=find_packages(),

        # requirements
        install_requires=[],
        python_requires='>=3.7',

        # pybind11 code
        cmdclass={"build_ext": build_ext},
        ext_modules=[
            Pybind11Extension(
                "vhash",
                cxx_files,
                include_dirs=[path.join(path.dirname(__file__), 'cxx')],
            ),
        ]
    )
