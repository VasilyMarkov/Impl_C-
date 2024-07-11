#include <iostream>
#include "Controllable.hpp"
#include <vector>
#include "string.h"
#include <memory>
#include <type_traits>
#include <ranges>
#include <concepts>


namespace rng = std::ranges;
namespace view = rng::views;

template <typename T>
void print(const std::vector<T>& vec) {
    for(const auto i : vec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template <typename T, typename U>
struct is_same: std::false_type {};

template <typename T>
struct is_same<T, T>: std::true_type {};

template <typename T, typename U>
bool is_same_v = is_same<T, U>::value;

template <typename T, typename U>
requires(std::same_as<T, std::decay_t<U>>)
void foo(T* it, U&& rhs) {
  if constexpr(std::is_rvalue_reference_v<U&&>) {
    std::cout << "U&&" << std::endl;
  }
  else {
    std::cout << "U&" << std::endl;
  }
}

int main() {
  std::cout << std::boolalpha;
  int* it = new int();
  int a = 5;
  int& b = a;
  foo(it, b);
  foo(it, std::move(b));
}