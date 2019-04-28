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
    int i1 = index.getUncheckedOldestRemovedIndex();
    
    EXPECT_EQ(-1, i1);
    
    // add 2 data
    std::string str1 = "data1";
    std::vector<byte> data1(str1.begin(), str1.end());
    EXPECT_EQ(0, index.add(data1));
    std::string str2 = "data2";
    std::vector<byte> data2(str2.begin(), str2.end());
    EXPECT_EQ(1, index.add(data2));

    ASSERT_TRUE(index.exists(1));

    // get 2 data
    std::vector<byte> actual1 = index.get(0);
    std::string actualStr1(actual1.begin(), actual1.end());
    EXPECT_EQ(str1, actualStr1);
    std::vector<byte> actual2 = index.get(1);
    std::string actualStr2(actual2.begin(), actual2.end());
    EXPECT_EQ(str2, actualStr2);

    // remove 1 data
    index.remove(1);

    EXPECT_FALSE(index.exists(1));

    // add 1 data (new allocation)
    std::string str3 = "data3";
    std::vector<byte> data3(str3.begin(), str3.end());
    EXPECT_EQ(2, index.add(data3));

    ASSERT_TRUE(index.exists(2));
    
    std::vector<byte> actual3 = index.get(2);
    std::string actualStr3(actual3.begin(), actual3.end());
    EXPECT_EQ(str3, actualStr3);

    // add 1 data (reuse)
    int i2 = index.getUncheckedOldestRemovedIndex();
    
    EXPECT_EQ(1, i2);

    index.checkOldestRemovedIndex();

    int i3 = index.getUncheckedOldestRemovedIndex();

    EXPECT_EQ(-1, i3);

    bool findReuseIndex = false;
    for (int j=0;j<100;j++) {
        std::string tmpStr = "tmp";
        std::vector<byte> tmpData(tmpStr.begin(), tmpStr.end());
        std::size_t tmpi = index.add(tmpData);
        if (tmpi == 1) {
            findReuseIndex = true;
            break;
        }
    }
    EXPECT_TRUE(findReuseIndex);
    
}