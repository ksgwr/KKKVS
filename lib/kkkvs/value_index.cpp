#include "kkkvs/value_index.hpp"

namespace kkkvs {

ValueIndex::ValueIndex() {
  //next_ = 0;
  //last_ = 0;

}

ValueIndex::~ValueIndex() {
  //std::vector<std::vector<byte>>().swap(values_);
}

std::size_t ValueIndex::add(byte* data, std::size_t len) {
  std::size_t i;
  std::size_t size = values_.size();
  std::vector<byte> value(data, data + len);
  if (values_.capacity() == size && !removes_.empty()) {
    i = removes_.front();
    removes_.pop_front();
    if (std::begin(removes_) != checked_) {
      --checked_;
    }
    values_[i] = &value;
  } else {
    values_.push_back(&value);
    i = size;
  }
  return i;
}


void ValueIndex::put(std::size_t i, byte* data, std::size_t len) {
  std::vector<byte> value(data, data + len);
  values_[i] = &value;
}


bool ValueIndex::exists(std::size_t i) {
  if (values_.size() >= i) {
    return false;
  }
  
  if (!removes_.empty()) {
    // TODO:: use find
    for(auto it = checked_; it != std::end(removes_); ++it){
      if (i == *it) {
        return false;
      }
    }
  }
  
  std::vector<byte>* value = values_.at(i);
  return value == nullptr ? false : true;
}

std::vector<byte> ValueIndex::get(std::size_t i) {
  std::vector<byte>* value = values_.at(i);
  if (value == nullptr) {
    return std::vector<byte>();
  } else {
    std::vector<byte> v(value->size());
    std::copy(value->begin(), value->end(), v.begin());
    return v;
  }
}

void ValueIndex::remove(std::size_t i) {
  std::vector<byte>* p = nullptr;
  values_[i] = p;
  removes_.push_back(i);
}

}