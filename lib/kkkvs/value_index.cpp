#include "kkkvs/value_index.hpp"

namespace kkkvs {

ValueIndex::ValueIndex() {
  checked_ = 0;
}

ValueIndex::~ValueIndex() {
  //std::vector<std::vector<byte>>().swap(values_);
}

std::size_t ValueIndex::add(std::vector<byte>* data) {
  std::size_t i;
  std::size_t size = values_.size();
  if (values_.capacity() == size && !removes_.empty() 
      && checked_ > 0) {
    i = removes_.front();
    removes_.pop_front();
    // TODO:: change iterator
    checked_--;
    values_[i] = data;
  } else {
    values_.push_back(data);
    i = size;
  }
  return i;
}

void ValueIndex::put(std::size_t i, std::vector<byte>* data) {
  values_[i] = data;
}

bool ValueIndex::exists(std::size_t i) {
  if (values_.size() <= i) {
    return false;
  }
  
  if (!removes_.empty()) {
    for (std::size_t j=checked_; j<removes_.size();j++) {
      if (i == j) {
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
  values_[i] = nullptr;
  removes_.push_back(i);
}

std::size_t ValueIndex::getUncheckedRemovedIndex() {
  return checked_;
}

void ValueIndex::checkedRemovedIndex() {
  ++checked_;
}

}