#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vhash/vhash.h>

namespace py = pybind11;


PYBIND11_MODULE(vhash, m) {
    m.doc() = "Vectorizing Hash Tables Module";
    py::class_<vhash::VHash>(
        m,
        "VHash",
        R"STRING_LITERAL(
            Vectorizing hash table for fast quantization of text documents

            Parameters
            ----------
            largest_ngram: int, optional, default=3
                Maximum number of words to take as a single phrase.
                This table's vocabulary will consist of phrases from
                1 word long to :code:`largest_ngram` words long.
            min_phrase_occurrence: float, default=1E-3
                Only the most common phrases are kept. Uncommon phrases
                are removed if the total count of that phrase across all
                training documents meets the following criteria:

                .. code-block:: python

                    if min_phrase_occurrence < 1:
                        remove from table if count < min_phrase_occurrence * docs.size()
                    else:
                        remove from table if count < min_phrase_occurrence

            num_features: int, optional, default=1E3
                number of features to compute
                (which equals the dimension of each output dense vector).
                If fewer training documents than this are used when fitting,
                then :code:`num_features` will be reduced to the number
                of training documents.
            max_num_phrases: int, optional, default=1E6
                maximum size of term vocabulary, including phrases of all
                lengths
            downsample_to: int, optional, default=100E3
                maximum number of documents to use when fitting.
                If more are provided, then documents are downsampled
            live_evaluation_step: int, optional, default=10E3
                when fitting a table, to speed things up, infrequent terms
                are removed every :code:`live_evaluation_step` number of
                documents

        )STRING_LITERAL")
        .def(
            py::init <
                const size_t&,
                const float&,
                const size_t&,
                const size_t&,
                const size_t&,
                const size_t&
            >(),
            py::arg("largest_ngram") = (size_t)3,
            py::arg("min_phrase_occurrence") = (float)1E-3,
            py::arg("num_features") = (size_t)1000,
            py::arg("max_num_phrases") = (size_t)1E6,
            py::arg("downsample_to") = (size_t)100E3,
            py::arg("live_evaluation_step") = (size_t)10E3
        )
        .def(
            "fit",
            &vhash::VHash::fit,
            R"STRING_LITERAL(
                Fit model

                Parameters
                ----------
                docs: list[str]
                    documents to use to train model
                labels: list[list[int]]
                    class label for each document.
                    Assumes that classes are numbered sequentially, starting at zero.
                
                Returns
                -------
                VHash
                    Calling object

            )STRING_LITERAL",
            py::arg("docs"),
            py::arg("labels")
        )
        .def(
            "fit_transform",
            &vhash::VHash::fit_transform,
            R"STRING_LITERAL(
               Fit model, transform docs 

                Parameters
                ----------
                docs: list[str]
                    documents to use to train model, then to transform
                labels: list[list[int]]
                    class label for each document.
                    Assumes that classes are numbered sequentially, starting at zero.

                Returns
                -------
                rep: list[list[float]]
                    Numeric representation of documents.
                    :code:`rep[x]` is for :code:`docs[x]`.
                    :code:`rep[x].size() == num_features` (set in constructor)

            )STRING_LITERAL",
            py::arg("docs"),
            py::arg("labels")
        )
        .def(
            "transform",
            &vhash::VHash::transform,
            R"STRING_LITERAL(
                Transform docs, using fitted model

                Parameters
                ----------
                docs: list[str]
                    documents to transform

                Returns
                -------
                rep: list[list[float]]
                    Numeric representation of documents.
                    :code:`rep[x]` is for :code:`docs[x]`.
                    :code:`rep[x].size() == num_features` (set in constructor)

            )STRING_LITERAL",
            py::arg("docs")
        )
        .def(
            "save",
            &vhash::VHash::save,
            R"STRING_LITERAL(
                Save model to file

                Parameters
                ----------
                fname: str
                    name of output file
            )STRING_LITERAL",
            py::arg("fname")
        )
        .def_static(
            "load",
            &vhash::VHash::load,
            R"STRING_LITERAL(
                Load model from file

                Parameters
                ----------
                fname: str
                    name of input file

                Returns
                -------
                VHash
                    instance loaded from file
            )STRING_LITERAL",
            py::arg("fname")
        );
}
