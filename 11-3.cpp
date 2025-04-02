#include "Tuple.h"
#include <iostream>
#include <type_traits>

template <typename Target, typename... Ts> struct Getter3;

template <typename Target, typename T> struct Getter3<Target, T> {
  static auto &get(mpcs::Tuple2<T> &tup) {
    if (std::is_same_v<T, Target>) {
      return tup.val;
    }
    return -1;
  }
};

template <typename Target, typename T, typename... Ts>
struct Getter3<Target, T, Ts...> {
  static auto &get(mpcs::Tuple2<T, Ts...> &tup) {
    Tuple2<Ts...> const &restOfVals = tup;
    auto idx = Getter2<Target, Ts...>::get(restOfVals);
  }
};

template <int i, typename T, typename... Ts> struct Getter2<i, T, Ts...> {
  static auto &get(Tuple2<T, Ts...> const &tup) {}
};

template <int i, typename... Ts> auto &get(Tuple2<Ts...> &tup) {
  return Getter2<i, Ts...>::get(tup);
}

int main() {
  mpcs::Tuple2<int, int, int> t{3, 3, 3};
  std::cout << std::get<2>(t) << '\n';
}
