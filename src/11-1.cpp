#include "variadic_examples.h"
#include <format>
#include <iostream>
#include <tuple>
#include <type_traits>

template <typename TL, typename T, typename U> struct ReplaceAll;

template <typename T, typename U> struct ReplaceAll<std::tuple<>, T, U> {
  using type = std::tuple<>;
};

template <typename... Ts, typename T, typename U>
struct ReplaceAll<std::tuple<T, Ts...>, T, U> {
  using type = typename mpcs::Append<
      std::tuple<U>, typename ReplaceAll<std::tuple<Ts...>, T, U>::type>::type;
};

template <typename H, typename... Ts, typename T, typename U>
struct ReplaceAll<std::tuple<H, Ts...>, T, U> {
  using type = typename mpcs::Append<
      std::tuple<H>, typename ReplaceAll<std::tuple<Ts...>, T, U>::type>::type;
};

int main() {
  using T1 = std::tuple<int, int, double, float>;
  using T2 = ReplaceAll<T1, int, double>::type;
  T2 t{1.1, 2.2, 3, 4};
  static_assert(std::is_same_v<T2, std::tuple<double, double, double, float>>);

  std::cout << std::format("Elements at indexes 0 and 1 are {} and {} -- "
                           "replaced ints with doubles!\n",
                           std::get<0>(t), std::get<1>(t));
}
