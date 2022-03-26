/**
 * @file math.hpp
 * @author ygsiro (entoyukari@gmail.com)
 * @brief math namespace
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright &copy; 2022 ygsiro
 *
 */

#ifndef PORTAL_MATH_MATH_HPP
#define PORTAL_MATH_MATH_HPP

#include <concepts>
#include <numbers>
#include <numeric>
#include <cassert>
#include <stdexcept>

/**
 * @brief math namespace
 *
 */
namespace portal::math {
/**
 * @brief absolute
 *
 * @tparam T type
 * @param[in] x value
 * @return The absolute value of x (i.e. |x|).
 */
template <typename T>
[[nodiscard]] constexpr T absolute(T x) noexcept {
  return x < 0 ? -x : x;
}

/**
 * @brief absolute
 *
 * @tparam T type
 * @param[in] x value
 * @return The absolute value of x (i.e. |x|).
 */
template <std::unsigned_integral T>
[[nodiscard]] constexpr T absolute(T x) noexcept {
  return x;
}

/**
 * @brief Compares floating-point values.
 *
 * @tparam T floating-point type
 * @param[in] x floating-point value
 * @param[in] y floating-point value
 * @param[in] tolerance tolerance
 * @return
 * Return a negative value if x is less than y.
 * Return 0 if x and y are the same.
 * If x is greater than y, return a positive value.
 */
template <std::floating_point T>
[[nodiscard]] constexpr int fpcmp(T x, T y, T tolerance) noexcept {
  // clang-format off
  assert(tolerance >= 0);
  return (x > y + tolerance) ? 1 : (y > x + tolerance) ? -1 : 0;
  // clang-format on
}

/**
 * @brief Compares floating-point values.
 *
 * @tparam T floating-point type
 * @param[in] x floating-point value
 * @param[in] y floating-point value
 * @return
 * Return a negative value if x is less than y.
 * Return 0 if x and y are the same.
 * If x is greater than y, return a positive value.
 */
template <std::floating_point T>
[[nodiscard]] constexpr int fpcmp(T x, T y) noexcept {
  // clang-format off
  return fpcmp(x, y,
               std::numeric_limits<T>::epsilon() *
               std::max<T>(1, std::max(absolute(x), absolute(y))));
  // clang-format on
}

/**
 * @brief x is zero?
 *
 * @tparam T type
 * @param[in] x value
 * @return true x is 0.
 * @return false x isn't 0.
 */
template <typename T>
[[nodiscard]] constexpr bool is_zero(T x) noexcept {
  return x == 0;
}

/**
 * @brief x is zero?
 *
 * @tparam T floating-point type
 * @param[in] x value
 * @param[in] tolerance tolerance
 * @return true x is 0.
 * @return false x isn't 0.
 */
template <std::floating_point T>
[[nodiscard]] constexpr bool is_zero(T x, T tolerance) noexcept {
  assert(tolerance >= 0);
  return fpcmp<T>(x, 0, tolerance) == 0;
}

/**
 * @brief x is zero?
 *
 * @tparam T floating-point type
 * @param[in] x value
 * @return true x is 0.
 * @return false x isn't 0.
 */
template <std::floating_point T>
[[nodiscard]] constexpr bool is_zero(T x) noexcept {
  return is_zero(x, std::numeric_limits<T>::epsilon() * std::max<T>(100, absolute(x)));
}

/**
 * @brief slow square root
 *
 * @tparam T floating-point type
 * @param[in] scalar value
 * @return Returns the square root of scalar
 */
template <std::floating_point T>
[[nodiscard]] constexpr T slow_sqrt(const T &scalar) {
  if (std::is_constant_evaluated()) {
    T x    = scalar / 2;
    T prev = 0;

    while (x != prev) {
      prev = x;
      x    = (x + scalar / x) / 2;
    }
    return x;
  } else {
    return std::sqrt(scalar);
  }
}

/**
 * @brief slow sin
 *
 * @tparam T floating-point type
 * @param[in] theta theta
 * @return Returns the sin of theta
 */
template <std::floating_point T>
[[nodiscard]] constexpr T slow_sin(const T &theta) {
  if (std::is_constant_evaluated()) {
    T x_sq   = -(theta * theta);
    T series = theta;
    T tmp    = theta;
    T fact   = static_cast<T>(2);

    do {
      tmp *= x_sq / (fact * (fact + 1));
      series += tmp;
      fact += 2;
    } while (absolute(tmp) >= std::numeric_limits<T>::epsilon());

    return series;
  } else {
    return std::sin(theta);
  }
}

/**
 * @brief slow cos
 *
 * @tparam T floating-point type
 * @param[in] theta theta
 * @return Returns the cos of theta
 */
template <std::floating_point T>
[[nodiscard]] constexpr T slow_cos(const T &theta) {
  if (std::is_constant_evaluated()) {
    return slow_sin(theta + std::numbers::pi_v<T> / 2);
  } else {
    return std::cos(theta);
  }
}

/**
 * @brief slow tan
 *
 * @tparam T floating-point type
 * @param[in] theta theta
 * @return Returns the tan of theta
 */
template <std::floating_point T>
[[nodiscard]] constexpr T slow_tan(const T &theta) {
  if (std::is_constant_evaluated()) {
    return slow_sin(theta) / slow_cos(theta);
  } else {
    return std::tan(theta);
  }
}

/**
 * @brief lerp
 * 
 * @tparam T type
 * @tparam FT param
 * @param[in] a value
 * @param[in] b value
 * @param[in] t parameter
 * @return Linearly complement a and b with the parameter t.
 */
template <typename T, std::floating_point FT>
[[nodiscard]] constexpr T lerp(const T &a, const T &b, FT t) {
  return a + t * (b - a);
}

} // namespace portal::math

#endif // PORTAL_MATH_MATH_HPP