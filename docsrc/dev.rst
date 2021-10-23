###############
Developer Notes
###############

#. The core code of this repo is written in C++, with a :code:`pybind11`
   wrapping to make it available in python.

#. Numpydoc-style docstrings have been used in the C++ code, and every
   reasonable effort has been made to follow the PEP8 standards in the C++
   code.

#. To test your C++ code, run :code:`make test` in the :code:`cxx` folder.

   This code has been tested and developed using g++ (version 9.3.0) and gnu
   make (version 4.2.1) on Ubuntu 20.04.03.

#. To test the python bindings, use pytest, e.g.:

   .. code-block:: console

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

#. Documentation is automatically built through GitHub Actions, published to
   the :code:`docs` branch to keep the :code:`main` branch light.

   To test documentation, run :code:`docsrc/build`.

   Do NOT check in documentation to your branch.

#. The version number is automatically updated through GitHub Actions on each
   push to main. With each update, the main branch is tagged with the version
   number.

#. Pull requests are welcome.
