/*
 * main.cpp
 * */

#include "gtest/gtest.h"
#include "hello.hpp"

TEST(Hello, string) {
    const char* expected = "hello";
	const char* actual = hello();
    ASSERT_STREQ(expected, actual);
}

