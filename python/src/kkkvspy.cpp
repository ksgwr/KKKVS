#include "kkkvs/value_index.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

//std::vector<byte> create() {
py::bytes create() {    
    std::string str1("data1");
    std::vector<byte> value(str1.begin(), str1.end());
    std::vector<byte> v(value.size());
    std::copy(value.begin(), value.end(), v.begin());
    std::string s(v.begin(), v.end());
    return py::bytes(s);
}

class PyValueIndex : public kkkvs::ValueIndex {
public:

    std::size_t add(const std::string &data) {
        std::vector<byte> byteData(data.begin(), data.end());
        return kkkvs::ValueIndex::add(byteData);
    }

    void put(std::size_t i, const std::string &data) {
        std::vector<byte> byteData(data.begin(), data.end());
        kkkvs::ValueIndex::put(i, byteData);
    }

    py::bytes get(std::size_t i) {
        std::vector<byte> v = kkkvs::ValueIndex::get(i);
        std::string s(v.begin(), v.end());
        return py::bytes(s);
    }
};

PYBIND11_MODULE(kkkvspy, m) {
    m.doc() = "kkkvspy library";

    m.def("add", &add, "A function which adds two numbers")
        .def("create", &create, "create sample data");

    py::class_<PyValueIndex>(m, "ValueIndex")
            .def(py::init<>())
            //.def("add", (std::size_t (WrapValueIndex::*)(std::vector<byte> *)) & WrapValueIndex::add, py::arg("data"))
            .def("add", (std::size_t (PyValueIndex::*)(const std::string &)) & PyValueIndex::add, py::arg("data"))
            //.def("put", (void (WrapValueIndex::*)(std::size_t, std::vector<byte> *)) & WrapValueIndex::put, py::arg("i"), py::arg("data"))
            .def("put", (void (PyValueIndex::*)(std::size_t, const std::string &)) & PyValueIndex::put, py::arg("i"), py::arg("data"))
            .def("exists", &PyValueIndex::exists, py::arg("i"))
            .def("get", (py::bytes (PyValueIndex::*)(std::size_t)) & PyValueIndex::get, py::arg("i"))
            .def("remove", (void (PyValueIndex::*)(std::size_t, bool)) & PyValueIndex::remove, py::arg("i"), py::arg("hard"))
            .def("remove", (void (PyValueIndex::*)(std::size_t)) & PyValueIndex::remove, py::arg("i"))
            .def("getUncheckedOldestRemovedIndex", &PyValueIndex::getUncheckedOldestRemovedIndex)
            .def("checkRemovedIndex", &PyValueIndex::checkRemovedIndex, py::arg("i"));
}
