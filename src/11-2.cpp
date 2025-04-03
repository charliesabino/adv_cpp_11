
#include "Tuple.h"
#include <cstddef>
#include <cstdint>
#include <type_traits>

template <typename... Ts>
constexpr auto length(const mpcs::Tuple2<Ts...> &t) -> uint32_t;

template <> constexpr auto length(const mpcs::Tuple2<> &_) -> uint32_t {
  return 0;
}

template <typename T, typename... Ts>
constexpr auto length(const mpcs::Tuple2<T, Ts...> &t) -> uint32_t {
  mpcs::Tuple2<Ts...> const &restOfVals = t;
  return 1 + length(restOfVals);
}

template <class TL, int i> struct TypeAt;

template <class T, typename... Ts> struct TypeAt<mpcs::Tuple2<T, Ts...>, 0> {
  using type = T;
};

template <class T, typename... Ts, int i>
struct TypeAt<mpcs::Tuple2<T, Ts...>, i> {
  using type = TypeAt<mpcs::Tuple2<Ts...>, i - 1>::type;
};

template <size_t I, typename TL> constexpr auto type_at() {
  return std::type_identity<typename TypeAt<TL, I>::type>{};
}

int main() {
  // Because partial function template specialization is not allowed,
  // passing a parameter was the best implementation I saw fit.
  using Tuple = mpcs::Tuple2<int, double, float>;
  auto t1 = Tuple{1, 2, 3};
  constexpr auto l1 = length(t1);
  static_assert(l1 == 3);

  // Once again, I had to create a helper struct to work around partial function
  // template specialization not being allowed.
  auto t = type_at<1, Tuple>();
  static_assert(std::is_same_v<decltype(t)::type, double>);
}
