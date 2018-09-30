#include "kkkvs/value_index.hpp"
#include "gtest/gtest.h"

using namespace kkkvs;

namespace {
    class ValueIndexTest : public ::testing::Test {
    protected:
        ValueIndex index;
    };
}

TEST_F(ValueIndexTest, SimpleCase) {
    std::string str1 = "data1";
    byte data[str1.size() + 1];
    memcpy(data, str1.data(), str1.length());
    index.add(data, str1.length());

    RecordProperty("str1", str1);

    //ASSERT_TRUE(index.exists(0));
}