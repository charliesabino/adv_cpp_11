#include "Tuple.h"
#include "variadic_examples.h"
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

template <typename Target, typename... Ts>
struct TypeGetterHelper<Target, mpcs::Tuple2<Target, Ts...>> {
  constexpr static Target get(mpcs::Tuple2<Target, Ts...> &tup) {
    return tup.val;
  }
};

template <typename Target, typename... Ts>
constexpr Target get(mpcs::Tuple2<Ts...> &tup) {
  static_assert(!(mpcs::Count<Target, mpcs::Tuple2<Ts...>>::value == 0),
                "No matches found\n");
  static_assert(mpcs::Count<Target, mpcs::Tuple2<Ts...>>::value == 1,
                "Duplicate matches found\n");
  return TypeGetterHelper<Target, mpcs::Tuple2<Ts...>>::get(tup);
}

int main() {
  using Tup = mpcs::Tuple2<int, double, float, float>;
  Tup t{1, 2, 3, 4};
  auto i = get<int>(t);
  auto d = get<double>(t);

  // uncommenting the line below will result in compilation failure
  // auto f = get<float>(t);

  std::cout << std::format("Int: {}, Double: {}\n", i, d);
}
