#include "kkkvs/value_index.hpp"

#include <iostream>

namespace kkkvs {

const std::vector<byte> EMPTY;

ValueIndex::ValueIndex() {
}

ValueIndex::~ValueIndex() {
  //std::vector<std::vector<byte>>().swap(values_);
}

std::size_t ValueIndex::add(const std::vector<byte>& data) {
  std::size_t i;
  std::size_t size = values_.size();
  
  if (values_.capacity() == size && !removes_.empty()) {
    i = removes_.front();
    removes_.pop_front();
    // TODO:: change iterator
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
  // TODO : size check and should not replace unused data
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

void ValueIndex::remove(std::size_t i, bool hard) {
  // TODO : check used flag, should not add duplicate index
  Value& value = values_.at(i);  
  value.used = false;

  if (hard) {
    value.data = EMPTY;
    removes_.push_back(i);
  } else {
    uncheckes_.push_back(i);
  }
}

void ValueIndex::remove(std::size_t i) {
  ValueIndex::remove(i, false);
}

int ValueIndex::getUncheckedRemovedIndex() {
  if (uncheckes_.empty()) {
    return -1;
  }
  std::size_t i = uncheckes_.front();
  uncheckes_.pop_front();
  return i;
}

void ValueIndex::checkRemovedIndex(std::size_t i) {
  if (values_.size() <= i) {
    return;
  }
  values_.at(i).data = EMPTY;
  removes_.push_back(i);
}

}