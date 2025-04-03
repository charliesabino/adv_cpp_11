#include "Tuple.h"
#include <cstddef>
#include <format>
#include <iostream>

template <typename Target, typename TL> struct TypeGetterHelper;

template <typename Target, typename T, typename... Ts>
struct TypeGetterHelper<Target, mpcs::Tuple2<T, Ts...>> {
  constexpr static auto get(mpcs::Tuple2<T, Ts...> &tup) {
    mpcs::Tuple2<Ts...> &restOfVals = tup;
    return TypeGetterHelper<Target, mpcs::Tuple2<Ts...>>::get(restOfVals);
  }
};

template <typename Target> struct TypeGetterHelper<Target, mpcs::Tuple2<>> {
  constexpr static Target get(mpcs::Tuple2<> &_) {
    throw std::runtime_error("No matches");
  }
};

template <typename Target, typename... Ts>
struct TypeGetterHelper<Target, mpcs::Tuple2<Target, Ts...>> {
  constexpr static Target get(mpcs::Tuple2<Target, Ts...> &tup) {
    mpcs::Tuple2<Ts...> &restOfVals = tup;
    try {
      TypeGetterHelper<Target, mpcs::Tuple2<Ts...>>::get(restOfVals);
      throw std::runtime_error("Duplicate matches");
    } catch (const std::runtime_error &e) {
      if (std::string(e.what()) != "No matches") {
        throw;
      }
    }
    return tup.val;
  }
};

template <typename Target, typename... Ts>
constexpr Target get(mpcs::Tuple2<Ts...> &tup) {
  return TypeGetterHelper<Target, mpcs::Tuple2<Ts...>>::get(tup);
}

int main() {
  using Tup = mpcs::Tuple2<int, double, float, float>;
  Tup t{1, 2, 3, 4};
  auto i = get<int>(t);
  auto d = get<double>(t);

  try {
    auto _ = get<float>(t);
  } catch (const std::runtime_error &e) {
    std::cout << e.what() << '\n';
  }

  std::cout << std::format("Int: {}, Double: {}", i, d);
}
