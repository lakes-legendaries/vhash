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
        version='0.0.18',
        description='hash tables for vectorizing text-based documents',
        author='Mike Powell PhD',
        author_email='mike@lakeslegendaries.com',

        # longer info
        long_description=open('README.rst').read(),
        license='MIT License',

        # packages to include
        packages=find_packages(),

        # requirements
        install_requires=[],
        python_requires='>=3.7',

        # urls
        project_urls={
            "Documentation": "https://lakes-legendaries.github.io/vhash/",
            "GitHub": "https://github.com/lakes-legendaries/vhash/",
            "Bug Tracker": "https://github.com/lakes-legendaries/vhash/issues",
        },

        # classifiers
        classifiers=[
            "Programming Language :: Python :: 3",
            "License :: OSI Approved :: MIT License",
            "Operating System :: OS Independent",
        ],

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
