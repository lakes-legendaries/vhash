#include <pybind11/pybind11.h>
#include "vhash.h"

PYBIND11_MODULE(python_example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}
