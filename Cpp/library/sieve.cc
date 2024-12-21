#include "sieve.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace mylib {

namespace {

template<typename T>
constexpr std::size_t kBits = sizeof(T) * 8;

template<typename T>
constexpr T DivideUp(T a, T b) {
  return (a + b - 1) / b;
}

}  // namespace

Sieve::Sieve(std::size_t size) {
  std::size_t bytes = DivideUp(size, kBits<std::uint8_t>);
  data_ = std::make_unique<std::uint8_t[]>(bytes);
  size_ = size;

  // initial beginning
  SetNotPrime(0);
  SetNotPrime(1);
  std::size_t current = 1;
  while (true) {
    // find the next prime
    ++current;
    while ((current < size_) && !this->operator[](current))
      ++current;
    // did not found
    if (current == size_) break;
    // set not prime numbers
    for (std::size_t i = current * current; i < size_; i += current)
      SetNotPrime(i);
  }
}

bool Sieve::operator[](std::size_t index) const {
  assert(index < size_);
  std::uint8_t bit = 1 << (index % 8);
  return (data_[index / 8] & bit) == 0;
}

std::size_t Sieve::size() const {
  return size_;
}

void Sieve::SetNotPrime(std::size_t index) const {
  assert(index < size_);
  std::uint8_t bit = 1 << (index % 8);
  data_[index / 8] |= bit;
}

} // namespace mylib
