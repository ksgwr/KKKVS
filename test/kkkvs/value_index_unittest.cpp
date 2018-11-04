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
    // add 2 data
    std::string str1 = "data1";
    std::vector<byte> data1(str1.begin(), str1.end());
    EXPECT_EQ(0, index.add(&data1));
    std::string str2 = "data2";
    std::vector<byte> data2(str2.begin(), str2.end());
    EXPECT_EQ(1, index.add(&data2));

    ASSERT_TRUE(index.exists(0));

    std::vector<byte> actual1 = index.get(0);
    std::string actualStr1(actual1.begin(), actual1.end());
    EXPECT_EQ(str1, actualStr1);

    // remove 1 data
    index.remove(0);

    EXPECT_FALSE(index.exists(0));

    // add 1 data (new allocation)
    std::string str3 = "data3";
    std::vector<byte> data3(str3.begin(), str3.end());
    EXPECT_EQ(2, index.add(&data3));

    ASSERT_TRUE(index.exists(2));
    
    std::vector<byte> actual2 = index.get(2);
    std::string actualStr2(actual2.begin(), actual2.end());
    EXPECT_EQ(str3, actualStr2);

    // add 1 data (reuse)
    std::size_t i = index.getUncheckedRemovedIndex();
    
    EXPECT_EQ(0, i);

    index.checkedRemovedIndex();

    bool findReuseIndex = false;
    for (int j=0;j<100;j++) {
        std::string tmpStr = "tmp";
        std::vector<byte> tmpData(tmpStr.begin(), tmpStr.end());
        std::size_t tmpi = index.add(&tmpData);
        if (tmpi == 0) {
            findReuseIndex = true;
        }
    }
    EXPECT_TRUE(findReuseIndex);
    
}