#ifndef LIBRARY_SIEVE_H_
#define LIBRARY_SIEVE_H_

#include <cstddef>
#include <cstdint>
#include <memory>

namespace mylib {

class Sieve final {
 public:
  Sieve(std::size_t size);
  bool operator[](std::size_t index) const;
  std::size_t size() const;

 private:
  std::size_t size_;
  // actually stores inverted bit mask, e.g. 'false' for prime numbers
  std::unique_ptr<std::uint8_t[]> data_;

  void SetNotPrime(std::size_t index) const;
};

}  // namespace mylib

#endif  // LIBRARY_SIEVE_H_