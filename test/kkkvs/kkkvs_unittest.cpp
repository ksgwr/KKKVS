#include "kkkvs/kkkvs.hpp"
#include "gtest/gtest.h"

using namespace kkkvs;

namespace {
    class KKKVSTest : public ::testing::Test {
    protected:
        KKKVSClient client;
    };
}

TEST_F(KKKVSTest, CreateIndex) {
    client.createEmptyIndex();
}