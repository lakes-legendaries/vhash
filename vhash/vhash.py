"""Vectorizing hash table for fast quantization of text documents"""

from __future__ import annotations
from typing import Any

from nptyping import NDArray
from numpy import array, unique, zeros

from _vhash import VHash as _VHash


class VHash(_VHash):
    """Vectorizing hash table for fast quantization of text documents

    Parameters
    ----------
    largest_ngram: int, optional, default=3
        Maximum number of words to take as a single phrase. This table's
        vocabulary will consist of phrases from :code:`smallest_ngram`-words
        long to :code:`largest_ngram`-words long.
    min_phrase_occurrence: float, default=1E-3
        Only the most common phrases are kept. Uncommon phrases are removed if
        the total count of that phrase across all training documents meets the
        following criteria:

        .. code-block:: python

            if min_phrase_occurrence < 1:
                min_count = min_phrase_occurrence * docs.size()
            else:
                min_count = min_phrase_occurrence
            remove from table if count < min_count

    num_features: int, optional, default=1E3
        number of features to compute (which equals the dimension of each
        output dense vector). If fewer training documents than this are used
        when fitting, then :code:`num_features` will be reduced to the number
        of training documents.
    max_num_phrases: int, optional, default=1E6
        maximum size of term vocabulary, including phrases of all lengths
    downsample_to: int, optional, default=100E3
        maximum number of documents to use when fitting. If more are provided,
        then documents are downsampled
    live_evaluation_step: int, optional, default=10E3
        when fitting a table, to speed things up, infrequent terms are removed
        every :code:`live_evaluation_step` number of documents
    smallest_ngram: int, optional, default=1
        Minimum number of words to take as a single phrase. This table's
        vocabulary will consist of phrases from :code:`smallest_ngram`-words
        long to :code:`largest_ngram`-words long.
    """

    def fit(
        self,
        /,
        docs: list[str],
        labels: list
    ) -> VHash:
        """Fit model

        Parameters
        ----------
        docs: list[str]
            documents to use to train model
        labels: list
            class label for each document

        Returns
        -------
        VHash
            Calling instance
        """
        class_labels = zeros(len(labels), dtype=int)
        for class_num, label_value in enumerate(unique(labels)):
            class_labels[labels == label_value] = class_num
        _VHash.fit(self, docs, class_labels.tolist())
        return self

    def fit_transform(
        self,
        /,
        docs: list[str],
        labels: list
    ) -> NDArray[(Any, Any), float]:
        """Fit model, get numeric representation of docs

        Parameters
        ----------
        docs: list[str]
            documents to use to train model
        labels: list
            class label for each document

        Returns
        -------
        numeric: NDArray([Any, Any], float)
            Numeric representation of documents.
            :code:`rep[x]` is for :code:`docs[x]`.
            :code:`rep[x].size() == num_features` (set in constructor)
        """
        return self.fit(docs, labels).transform(docs)

    def transform(
        self,
        /,
        docs: list[str],
    ) -> NDArray[(Any, Any), float]:
        """Get numeric representation of docs

        Parameters
        ----------
        docs: list[str]
            documents to numerically represent

        Returns
        -------
        numeric: NDArray([Any, Any], float)
            Numeric representation of documents.
            :code:`rep[x]` is for :code:`docs[x]`.
            :code:`rep[x].size() == num_features` (set in constructor)
        """
        if type(docs) is str:
            docs = [docs]
        return array(_VHash.transform(self, docs))
