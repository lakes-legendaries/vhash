##############
Logic Overview
##############

Here, we provide an overview of the motivation and logic of this package.

**********
Motivation
**********

Systems like BERT do a really good job vectorizing text documents for general
purpose tasks. However, BERT performs less well on tasks in highly specific
knowledege domains, and its training code is held in secret by Alphabet Inc.

This package provides hash tables that can perform fast training and
vectorization on documents with provided class labels, allowing you to
customize your vector quantization to your own discrimination task.

************
Step-by-step
************

This document performs all of the following operations:

#. Learning a term vocabulary (fitting only)

#. Weighting terms (fitting only)

#. Creating sparse representations of documents

#. Saving features for dense vectorization (fitting only)

#. Creating information-rich dense representations by comparing against the
   saved features (transforming only)

When fitting, the model performs (1), (2), (3), and (4).

When transforming, the model performs (3) and (5).

**************************
Learning a term vocabulary
**************************

This class will take the documents it is supplied during training, and keep all
terms and phrases that occur frequently across all training documents.

This class uses an n-gram approach, where each document is broken up into all
possible words and phrases consisting of anywhere from :code:`1` to :code:`n`
consecutive words. Each word and phrase is then inserted into a hash table, and
a running count of the number of instances of each word and phrase across all
training documents is kept.

All words and phrases that occur infrequently are removed from the hash table
(and thus eliminated from this model's vocabulary).

***************
Weighting terms
***************

To compute a phrase's weight:

    #. Compute the phrase's document frequency. A phrase's document frequency
       is the number of documents it appears in in the training set.

    #. Compute the phrase's expected document frequency, if it were evenly
       distributed among all classes. E.g. if a phrase appears in 82% of
       documents, we'd expect that phrase to occur in 82% of the documents
       belonging to each class, if that phrase were evenly distributed.
    
    #. Compute the actual document frequency of each class. E.g. a term might
       occur in 20% of the documents from one class, and 90% of the documents from
       another class.

    #. Compute each phrase's weight as:

       .. math::

          \sqrt( \sum_c( |expected\_freq_c - actual\_freq_c|^2 ) )
    
       where :math:`\sum_c` is the sum over each class, :math:`expected\_freq_c` is the
       expected frequency for class :math:`c`, and :math:`actual\_freq_c` is the actual
       frequency for class :math:`c`.

*******************************
Creating sparse representations
*******************************

To create a sparse representation of a document:

#. Each phrase in the document that exists in the hash table is counted.
   This creates a sparse integer array, where each index in the array
   corresponds to a single phrase.

#. The count of each phrase is transformed via

   .. code-block:: python
        
      count -> log(1 + count)

   This creates a sparse floating-point array.

#. Each phrase is multiplied by its weight. This modifies the existing
   sparse floating-point array.

#. This sparse floating-point array is L2 normalized.

***************
Saving features
***************

During training, a number of features will be saved for later comparison.
Features are simply documents that were used during fitting, and are saved by
the model. These documents are converted into sparse arrays following the
procedure listed above.

******************************
Creating dense representations
******************************

To transform a document's sparse vector into an information-rich dense vector,
compute the dot product between that sparse vector and every saved feature's
sparse vector.

A dense vector can be described as:

.. code-block:: python

    dense_vector[feature_num] = sparse_vector * feature[feature_num]
