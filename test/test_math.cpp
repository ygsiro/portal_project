#include <portal/math/fs_vector.hpp>
#include <gtest/gtest.h>
#include <array>

using namespace portal::math;

TEST(Math, Abs) {
  EXPECT_DOUBLE_EQ(1.0, absolute(-1.0));
  EXPECT_FLOAT_EQ(1.f, absolute(-1.f));
  EXPECT_EQ(1U, absolute(1U));
}

TEST(Math, FpCmp) {
  EXPECT_TRUE(fpcmp(1.0, 1.02, 0.01) < 0);
  EXPECT_TRUE(fpcmp(1.0, 1.01, 0.01) <= 0);
  EXPECT_TRUE(fpcmp(1.0, 0.99, 0.01) == 0);
  EXPECT_TRUE(fpcmp(1.0, 0.98, 0.01) != 0);
  EXPECT_TRUE(fpcmp(1.0, 0.99, 0.01) >= 0);
  EXPECT_TRUE(fpcmp(1.0, 0.98, 0.01) > 0);
}

TEST(Math, IsZero) {
  EXPECT_TRUE(is_zero(0));
  EXPECT_TRUE(is_zero(0.00001f));
  EXPECT_TRUE(is_zero(0.00000000000001));
}

TEST(FSVec, RangeFor) {
  fs_vector<double, 3> lhs{1, 2, 3};
  for (auto &p : lhs)
    std::cout << p << std::endl;
}

TEST(FSVec, Ctor) {
  constexpr fs_vector<double, 3> a{1, 2, 3};
  constexpr fs_vector<double, 3> b{a};
  constexpr fs_vector<double, 3> c{std::move(a)};
  constexpr fs_vector<double, 3> d;
  constexpr std::array<double, 3> e{1, 2, 3};
  constexpr fs_vector<double, 3> f(e);
  constexpr fs_vector<double, 3> g(tag::fill, 1);
}

TEST(FSVec, Assign) {
  fs_vector<double, 3> a{1, 2, 3}, b;
  std::array<double, 3> c{1, 2, 3};
  b = a;
  b = std::move(a);
  b = c;
}

TEST(FSVec, At) {
  fs_vector<double, 3> a{1, 2, 3};
  EXPECT_THROW((void)a.at(a.size()), std::out_of_range);
}

TEST(FSVec, Empty) {
  fs_vector<double, 0> a{};
  EXPECT_TRUE(a.empty());
  fs_vector<double, 3> b{1, 2, 3};
  EXPECT_FALSE(b.empty());
}