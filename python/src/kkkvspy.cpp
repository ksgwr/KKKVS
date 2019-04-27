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

class ValueIndex : public kkkvs::ValueIndex {
public:

    std::size_t add(const std::string &data) {
        std::cout << data << std::endl;
        std::vector<byte> byteData(data.begin(), data.end());
        return kkkvs::ValueIndex::add(&byteData);
    }

    py::bytes get(std::size_t i) {
        std::vector<byte> v = kkkvs::ValueIndex::get(i);
        std::string s(v.begin(), v.end());
        /*
        std::string str1("data2");
        std::vector<byte> value(str1.begin(), str1.end());
        std::size_t last = kkkvs::ValueIndex::add(&value);
        std::vector<byte> v = kkkvs::ValueIndex::get(last);
        std::string s(v.begin(), v.end());
        */
        return py::bytes(s);
    }
};

PYBIND11_MODULE(kkkvspy, m) {
    m.doc() = "kkkvspy library";

    m.def("add", &add, "A function which adds two numbers")
        .def("create", &create, "create sample data");

    py::class_<ValueIndex>(m, "ValueIndex")
            .def(py::init<>())
            .def("add", (std::size_t (ValueIndex::*)(std::vector<byte> *)) & ValueIndex::add, py::arg("data"))
            .def("add", (std::size_t (ValueIndex::*)(const std::string &)) & ValueIndex::add, py::arg("data"))
            .def("put", &ValueIndex::put, py::arg("i"), py::arg("data"))
            .def("exists", &ValueIndex::exists, py::arg("i"))
            .def("get", (py::bytes (ValueIndex::*)(std::size_t)) & ValueIndex::get, py::arg("i"))
            .def("remove", &ValueIndex::remove, py::arg("i"))
            .def("get_unchecked_oldest_removed_index", &ValueIndex::getUncheckedOldestRemovedIndex)
            .def("checkOldestRemovedIndex", &ValueIndex::checkOldestRemovedIndex);
}
