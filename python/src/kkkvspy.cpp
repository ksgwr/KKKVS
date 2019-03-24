#include "kkkvs/value_index.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

using namespace kkkvs;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(kkkvspy, m) {
    m.doc() = "kkkvspy library";

    m.def("add", &add, "A function which adds two numbers");

    py::class_<ValueIndex>(m, "ValueIndex")
            .def(py::init<>())
            .def("add", &ValueIndex::add, py::arg("data"))
            .def("put", &ValueIndex::put, py::arg("i"), py::arg("data"))
            .def("exists", &ValueIndex::exists, py::arg("i"))
            .def("get", &ValueIndex::get, py::arg("i"))
            .def("remove", &ValueIndex::remove, py::arg("i"))
            .def("get_unchecked_oldest_removed_index", &ValueIndex::getUncheckedOldestRemovedIndex)
            .def("checkOldestRemovedIndex", &ValueIndex::checkOldestRemovedIndex);
}
