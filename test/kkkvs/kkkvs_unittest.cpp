#include "kkkvs.hpp"
#include "gtest/gtest.h"

using namespace KKKVS;

namespace {
    class KKKVSTest : public ::testing::Test {
    protected:
        KKKVSClient client;
    };
}

TEST_F(KKKVSTest, CreateIndex) {
    client.createEmptyIndex();
}