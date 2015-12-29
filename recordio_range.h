#pragma once

#include "recordio.h"

#include <iterator>

namespace recordio {

template <class Proto>
class ReaderRange {

 public:
  ReaderRange(const std::string& path)
      : file_(path, std::ios::binary), reader_(&file_) {}
  ~ReaderRange() { reader_.Close(); }

  class iterator : std::iterator<std::input_iterator_tag, Proto> {
   private:
    void read_() {
      if (!reader_->ReadProtocolMessage(&value_)) {
        reader_ = nullptr;
        count_ = 0;
      }
    }

   public:
    iterator() : reader_(nullptr), count_(0) {}
    iterator(RecordReader* reader) : reader_(reader), count_(0) { this->read_(); }
    iterator(const iterator& rhs) : reader_(rhs.reader_), count_(rhs.count_) {
      this->read_();
    }

    iterator& operator++() {
      this->read_();
      return *this;
    }
    iterator operator++(int) {
      iterator res(*this);
      operator++();
      return res;
    }

    Proto& operator*() { return value_; }
    bool operator==(const iterator& rhs) const {
      return reader_ == rhs.reader_ && count_ == rhs.count_;
    }
    bool operator!=(const iterator& rhs) { return !(*this == rhs); }

   private:

    Proto value_;
    RecordReader* reader_;
    std::size_t count_;
  };

  iterator begin() { return iterator(&reader_); }
  iterator end() { return iterator(); }

 private:
  std::ifstream file_;
  RecordReader reader_;
};

}  // namespace recordio
