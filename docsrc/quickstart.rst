##########
Quickstart
##########

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

   from nptyping import NDArray
   
   from vhash import VHash


    # sample data
    docs = [
        'hi, my name is Mike',
        'hi, my name is George',
        'hello, my name is Mike',
    ]
    labels = [1, 0, 1]

    # create & train model
    vhash = VHash().fit(docs, labels)

    # create numeric representation
    numeric: NDArray[(Any, Any), float] = vhash.transform(docs)
