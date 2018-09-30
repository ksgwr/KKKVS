#ifndef KKKVS_VALUE_INDEX_HPP
#define KKKVS_VALUE_INDEX_HPP

#include <vector>
#include <deque>

using byte = unsigned char;

namespace kkkvs {

class ValueIndex {
  private:
    std::deque<std::size_t>::iterator checked_;
    std::deque<std::size_t> removes_;
    std::vector<std::vector<byte>*> values_;

  public:
    ValueIndex();

    ~ValueIndex();

    std::size_t add(byte*, std::size_t);
    void put(std::size_t, byte*, std::size_t);
    bool exists(std::size_t);
    std::vector<byte> get(std::size_t);
    void remove(std::size_t);
  };
  
}

#endif // KKKVS_VALUE_INDEX_HPP_