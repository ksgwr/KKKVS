#include "kkkvs/value_index.hpp"

#include <iostream>

namespace kkkvs {

const std::vector<byte> EMPTY;

ValueIndex::ValueIndex() {
  checked_ = 0;
}

ValueIndex::~ValueIndex() {
  //std::vector<std::vector<byte>>().swap(values_);
}

std::size_t ValueIndex::add(const std::vector<byte>& data) {
  std::size_t i;
  std::size_t size = values_.size();
  
  if (values_.capacity() == size && !removes_.empty() 
      && checked_ > 0) {
    i = removes_.front();
    removes_.pop_front();
    // TODO:: change iterator
    checked_--;
    Value& value = values_.at(i);
    value.data = data;
    value.used = true;
  } else {
    values_.push_back({data, true});
    i = size;
  }
  return i;
}

void ValueIndex::put(std::size_t i, const std::vector<byte>& data) {
  Value& value = values_.at(i);
  value.data = data;
  value.used = true;
}

bool ValueIndex::exists(std::size_t i) {
  if (values_.size() <= i) {
    return false;
  }
  return values_.at(i).used;
}

const std::vector<byte> ValueIndex::get(std::size_t i) {
  if (values_.size() <= i) {
    return EMPTY;
  }
  return values_.at(i).data;
}

void ValueIndex::remove(std::size_t i) {
  Value& value = values_.at(i);
  value.data = EMPTY;
  value.used = false;

  removes_.push_back(i);
}

int ValueIndex::getUncheckedOldestRemovedIndex() {
  if (removes_.empty() || checked_ >= removes_.size()) {
    return -1;
  }
  return removes_.at(checked_);
}

void ValueIndex::checkOldestRemovedIndex() {
  ++checked_;
}

}