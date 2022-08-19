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

Each term's / phrase's weight is computed as

.. math::

   w(t) = \sqrt{ \sum_c \bigg[ \bigg| \frac{f_e(t) - f_o(t, c)}{f_e(t)} \bigg|^2 \bigg] }

where :math:`w(t)` is the weight of term :math:`t`, :math:`f_e(t)` is the
(expected) frequency of term :math:`t` across all classes, and :math:`f_o(t,
c)` is the observed frequency of term :math:`t` in class :math:`c`.

*******************************
Creating sparse representations
*******************************

Documents are transformed into sparse representations via:

.. math::

   s(t) = \log{ \big( 1 + c(t) \big) } \times w(t)

where :math:`s(t)` is the sparse representation of term :math:`t` (for any
given article), :math:`c(t)` is the count of term :math:`t` in the article, and
:math`w(t)` is the weight of term :math:`t` (calculated above).

***************
Saving features
***************

During training, a number of features will be saved for later comparison.
Features are simply documents that were used during fitting, and are saved by
the model. These documents are converted into sparse arrays following the
procedure listed above.

Each saved article is referred to as an :math:`\alpha` article.

******************************
Creating dense representations
******************************

To transform a document's sparse vector into an information-rich dense vector,
compute the cosine similarity between that sparse vector and every saved
:math:'\alpha` feature's sparse vector.

A document's dense vector can be described as:

.. math::

   d(\alpha) = \frac{\vec s}{||\vec s||^2} \cdot \frac{\vec \alpha}{||\vec \alpha||^2}

where :math:`d(\alpha)` is :math:`\alpha`'th vector index in the dense
representation of the article, :math:`\vec s` is the sparse representation of
the article (computed above), and :math:`\alpha` is the sparse representation
of the previously-saved :math:`\alpha` feature article.
