#include <iostream>

#include "library/sieve.h"

int main() {
  std::size_t count;
  
  std::cout << "Primes up to: ";
  std::cin >> count;

  mylib::Sieve sieve{count};
  std::size_t total = 0;
  for(std::size_t i = 0; i < sieve.size(); ++i) {
    if (!sieve[i]) continue;
    std::cout << i << " ";
    ++total;
  }
  std::cout << std::endl << total << " primes in total" << std::endl;

  return 0;
}