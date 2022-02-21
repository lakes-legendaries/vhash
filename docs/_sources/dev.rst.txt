###############
Developer Notes
###############

Pull requests are welcome.

If you will be contributing to this repo, please adhere to all the standards
described on this page.

*********
Standards
*********

#. The core code of this repo is written in C++, with a :code:`pybind11`
   wrapping to make it available in python.

#. Numpydoc-style docstrings have been used in the C++ code, and every
   reasonable effort has been made to follow the PEP8 standards in the C++
   code.

#. All code should be thoroughly tested before being checked in.

*******
Testing
*******

#. To test your C++ code, run :code:`make test` in the :code:`cxx` folder.

   This code has been tested and developed using g++ (version 9.3.0) and gnu
   make (version 4.2.1) on Ubuntu 20.04.03.

#. To test the python bindings, use pytest, e.g.:

   .. code-block:: bash

      python -m venv .venv
      source .venv/bin/activate
      pip install --upgrade pip
      pip install -r requirements.txt
      pip install .
      pytest

   Please note that, because this uses a C++ module, you must run :code:`pip
   install .` before running :code:`pytest`. Furthermore, the above code
   snippet assumes that you have aliased :code:`python` to be your most recent
   :code:`python3` version.

   This package's code has been tested and developed using python3.9.7

***************************
Continuous Integration (CI)
***************************

NEVER merge into the :code:`main` branch. Instead, merge into the
:code:`actions` branch, and the following will be automatically performed:

#. The code will be tested, and will NOT be merged into :code:`main` if
   there are any errors. This testing will happen for all python versions
   3.7-3.10

#. Documentation will be built and published to the :code:`docs` branch
   (which keeps the :code:`main` branch light).

   (To test documentation ahead of time, run :code:`docsrc/build`. NEVER
   check in documentation to your branch.)

#. The version number will be updated, and the repo will be
   tagged with the version number.

#. The project will be automatically uploaded to PyPi.

#. All changes will be merged into:code:`main`.
