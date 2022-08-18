#define __PYBIND_MODULE__

#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vhash/vhash.h>

namespace py = pybind11;
using std::vector;


PYBIND11_MODULE(_vhash, m) {
    m.doc() = "Vectorizing Hash Tables Module";
    py::class_<vhash::VHash>(m, "VHash")
        .def(
            py::init <
                const size_t&,
                const float&,
                const size_t&,
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
            py::arg("live_evaluation_step") = (size_t)10E3,
            py::arg("smallest_ngram") = (size_t)1
        )
        .def(
            "fit",
            &vhash::VHash::fit,
            py::arg("docs"),
            py::arg("labels")
        )
        .def(
            "fit_transform",
            &vhash::VHash::fit_transform,
            py::arg("docs"),
            py::arg("labels")
        )
        .def(
            "transform",
            &vhash::VHash::transform,
            py::arg("docs")
        )
        .def(
            py::pickle(
                &vhash::VHash::__get_state__,
                &vhash::VHash::__set_state__
            )
        );
}
