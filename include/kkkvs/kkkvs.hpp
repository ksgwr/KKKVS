/*
 * kkkvs.hpp
 * */

#ifndef KKKVS_KKKVS_HPP_
#define KKKVS_KKKVS_HPP_

#include "kkkvs/value_index.hpp"

namespace kkkvs {

class KKKVSClient {
  public:
    void createEmptyIndex();
  private:
    ValueIndex value_index_;
  };
}

#endif // KKKVS_KKKVS_H_
