/*
 * main.cpp
 * */

#include <iostream>

#include "hello.hpp"

int main(const int, const char* const []) {
    std::cout
        << hello()
        << std::endl;

    return 0;
}