from glob import glob
from setuptools import find_packages, setup
from pybind11.setup_helpers import build_ext, Pybind11Extension


if __name__ == '__main__':
    setup(
        name='vhash',
        version='0.0.0',
        description='C++ Vectorizing Hash Tables',
        author='Mike Powell PhD',
        author_email='mike@lakeslegendaries.com',
        requires=[],
        packages=find_packages(),
        cmdclass={"build_ext": build_ext},
        ext_modules=[
            Pybind11Extension(
                "python_example",
                [
                    'cxx/vhash.cxx',
                    'cxx/main.cxx',
                ],
            ),
        ]
    )
