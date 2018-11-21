#include <catch.hpp>

#include <SI/time.h>

TEST_CASE("s returns ratio 1 to 1") {
  constexpr auto one = 1_s;
  static_assert(decltype(one)::ratio::num == 1, "One s is 1 / 1");
  static_assert(decltype(one)::ratio::den == 1, "One s is 1 / 1");
}

TEST_CASE("min returns ratio 60 to 1") {
  constexpr auto one = 1_min;
  static_assert(decltype(one)::ratio::num == 60, "min is 60 / 1");
  static_assert(decltype(one)::ratio::den == 1, "One min is 60 / 1");
}

TEST_CASE("negative duration test") {
  constexpr auto minus_one = -1_s;
  REQUIRE(minus_one.raw_value().count() == -1);
}

TEST_CASE("Assert on overflow for s") { REQUIRE_NOTHROW(0xffffffffffffffff_s); }