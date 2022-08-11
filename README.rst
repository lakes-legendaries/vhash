##############################
VHash: Vectorizing Hash Tables
##############################

If you have documents with class labels, and you want to create numeric
representations of those documents that maximize inter-class differences, then
this package is for you. This package provides vectorizing hash tables that
quickly transform your text, optimizing for the maximum distance between
document-class vectors.

This project has a C++ backend with a python interface, allowing for maximum
speed and maximum interopability.

************
Installation
************

To install, use :code:`pip`:

.. code-block:: bash

    pip install vhash

***********************
Minimum Working Example
***********************

This package follows the conventions of :code:`scikit-learn` to provide an
intuitive and familiar interface.

.. code-block:: python

   from typing import Any
   
   from nptyping import NDArray
   
   from vhash import VHash


    # sample documents: each item in the list is its own document
    docs = [
        'hi, my name is Mike',
        'hi, my name is George',
        'hello, my name is Mike',
    ]

    # class labels for each document
    labels = [1, 0, 1]

    # create & train model
    vhash = VHash().fit(docs, labels)

    # create numeric representation (2D float array)
    numeric: NDArray[(Any, Any), float] = vhash.transform(docs)

*******
Metrics
*******

To see how this text transformer compares to BERT, check out the
`sample notebook <https://github.com/lakes-legendaries/vhash/blob/main/stats/bert.ipynb>`_,
where we show how :code:`vhash` outperforms :code:`sBERT` on a sentiment analysis task.

.. docs-links

*************
Documentation
*************

To get started, check out the `docs <https://lakes-legendaries.github.io/vhash/>`_!

If you will be contributing to this repo, checkout the
`developer guide <https://lakes-legendaries.github.io/vhash/dev.html>`_.
