#include <SI/detail/unit.h>
#include <SI/stream.h>
#include <catch2/catch.hpp>

#include <cstring>
#include <sstream>

namespace SI {

// specialize unit_symbol for usage with stream operators
template <>
struct unit_symbol<'X', std::ratio<1>>
    : SI::detail::unit_symbol_impl<'x', 'x'> {};

template <typename _ratio>
struct unit_symbol<'X', _ratio>
    : SI::detail::unit_symbol_impl<SI::detail::ratio_prefix<_ratio>::value, 'x',
                                   'x'> {};

} // namespace SI

TEST_CASE("GIVEN a character sequence WHEN passed to unit_symbol_impl THEN "
          "string is stored inside struct") {
  constexpr const SI::detail::unit_symbol_impl<'A', 'B', 'C'> v;
  STATIC_REQUIRE(decltype(v)::str[0] == 'A');
  STATIC_REQUIRE(decltype(v)::str[1] == 'B');
  STATIC_REQUIRE(decltype(v)::str[2] == 'C');
}

// honest tests

TEST_CASE("GIVEN a ratio atto WHEN passed to ratio_prefix THEN resulting char "
          "is 'a'") {
  STATIC_REQUIRE(SI::detail::ratio_prefix<std::atto>::value == 'a');
}

namespace {
template <typename _ratio, char _literal> struct helper_struct {
  using ratio = _ratio;
  using literal = std::integral_constant<char, _literal>;
};
} // namespace

TEMPLATE_TEST_CASE(
    "GIVEN a ratio WHEN passed to ratio_prefix THEN resulting "
    "char is the SI-defined literal",
    "[detail][streaming]", (helper_struct<std::atto, 'a'>),
    (helper_struct<std::femto, 'f'>), (helper_struct<std::pico, 'p'>),
    (helper_struct<std::nano, 'n'>), (helper_struct<std::micro, 'u'>),
    (helper_struct<std::milli, 'm'>), (helper_struct<std::kilo, 'k'>),
    (helper_struct<std::mega, 'M'>), (helper_struct<std::giga, 'G'>),
    (helper_struct<std::peta, 'P'>), (helper_struct<std::exa, 'E'>)) {

  STATIC_REQUIRE(SI::detail::ratio_prefix<typename TestType::ratio>::value ==
                 TestType::literal::value);
}

TEST_CASE("GIVEN a unit AND ratio is <1> WHEN passed to an stringstream THEN "
          "resulting string contains value and unit symbol") {
  constexpr SI::detail::unit_t<'X', 1, int64_t, std::ratio<1>> v{100};

  std::stringstream ss;

  ss << v;
  REQUIRE(ss.str() == "100xx");
}

TEST_CASE("GIVEN a unit AND ratio is kilo WHEN passed to an stringstream THEN "
          "resulting string contains value and unit symbol AND unit symbol is "
          "prefixed with 'k'") {
  constexpr SI::detail::unit_t<'X', 1, int64_t, std::kilo> v{100};

  std::stringstream ss;

  ss << v;
  REQUIRE(ss.str() == "100kxx");
}

TEST_CASE("GIVEN a unit AND ratio is atto WHEN passed to an stringstream THEN "
          "resulting string contains value and unit symbol AND unit symbol is "
          "prefixed with 'a'") {
  constexpr SI::detail::unit_t<'X', 1, int64_t, std::atto> v{100};

  std::stringstream ss;

  ss << v;
  REQUIRE(ss.str() == "100axx");
}