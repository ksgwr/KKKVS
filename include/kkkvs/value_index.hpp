#ifndef KKKVS_VALUE_INDEX_HPP
#define KKKVS_VALUE_INDEX_HPP

#include <vector>
#include <deque>

using byte = unsigned char;

namespace kkkvs {

typedef struct Value_ {
  std::vector<byte> data;
  bool used;
} Value;

class ValueIndex {
  private:
    std::deque<std::size_t> removes_;
    std::deque<std::size_t> uncheckes_;
    std::vector<Value> values_;

  public:
    ValueIndex();

    ~ValueIndex();

    std::size_t add(const std::vector<byte>&);
    void put(std::size_t, const std::vector<byte>&);
    bool exists(std::size_t);
    const std::vector<byte> get(std::size_t);
    void remove(std::size_t, bool);
    void remove(std::size_t);
    int getUncheckedRemovedIndex();
    void checkRemovedIndex(std::size_t);
  };
  
}

#endif // KKKVS_VALUE_INDEX_HPP_