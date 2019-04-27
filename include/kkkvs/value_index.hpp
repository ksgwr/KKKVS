#ifndef KKKVS_VALUE_INDEX_HPP
#define KKKVS_VALUE_INDEX_HPP

#include <vector>
#include <deque>

using byte = unsigned char;

namespace kkkvs {

class ValueIndex {
  private:
    std::deque<std::size_t> removes_;
    std::size_t checked_;
    std::vector<std::vector<byte>*> values_;
    //std::vector<bool> usedList_;

  public:
    ValueIndex();

    ~ValueIndex();

    std::size_t add(std::vector<byte>*);
    void put(std::size_t, std::vector<byte>*);
    bool exists(std::size_t);
    std::vector<byte> get(std::size_t);
    void remove(std::size_t);
    std::size_t getUncheckedOldestRemovedIndex();
    void checkOldestRemovedIndex();
  };
  
}

#endif // KKKVS_VALUE_INDEX_HPP_