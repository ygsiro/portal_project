#ifndef PORTAL_RANDOM_HPP
#define PORTAL_RANDOM_HPP

#include <random>
#include <concepts>
#include <cassert>

/**
 * @brief portal namespace
 *
 */
namespace portal {
/**
 * @brief uniform real distribution
 *
 * @tparam T floating-point type
 * @tparam Engine engine
 */
template <std::floating_point T = double, std::uniform_random_bit_generator Engine = std::mt19937>
class uniform_real_distribution {
public:
  using param_type  = std::uniform_real_distribution<T>::param_type;  //!< @param parameter
  using result_type = std::uniform_real_distribution<T>::result_type; //!< @param result type

  /**
   * @brief Construct a new uniform real distribution object
   *
   */
  uniform_real_distribution()
      : uniform_real_distribution(static_cast<T>(0)) {
  }

  /**
   * @brief Construct a new uniform real distribution object
   *
   * @param[in] a min value
   * @param[in] b max value
   *
   * @pre a < b
   */
  explicit uniform_real_distribution(T a, T b = static_cast<T>(1))
      : m_dist(a, b)
      , m_engine(std::random_device{}()) {
    assert(a < b);
  }

  /**
   * @brief Construct a new uniform real distribution object
   * 
   * @param[in] parm parameter
   */
  explicit uniform_real_distribution(const param_type &parm)
      : uniform_real_distribution(parm.a(), parm.b()) {
  }

  /**
   * @brief reset
   * 
   */
  void reset() {
    m_dist.reset();
  }

  /**
   * @brief min value
   * 
   * @return result_type 
   */
  result_type a() const {
    return m_dist.a();
  }

  /**
   * @brief max value
   * 
   * @return result_type 
   */
  result_type b() const {
    return m_dist.b();
  }

  /**
   * @brief min value
   * 
   * @return result_type 
   */
  result_type min() const {
    return m_dist.min();
  }

  /**
   * @brief max value
   * 
   * @return result_type 
   */
  result_type max() const {
    return m_dist.max();
  }

  /**
   * @brief parameter
   * 
   * @return param_type 
   */
  param_type param() const {
    return m_dist.param;
  }

  /**
   * @brief random
   * 
   * @param[in] engine engine
   * @param[in] parm parameter
   * @return result_type 
   */
  result_type operator()(const std::uniform_random_bit_generator auto &engine, const param_type &parm) {
    return m_dist(engine, parm);
  }

  /**
   * @brief random
   * 
   * @param[in] engine engine 
   * @return result_type 
   */
  result_type operator()(const std::uniform_random_bit_generator auto &engine) {
    return m_dist(engine);
  }

  /**
   * @brief random
   * 
   * @return result_type 
   */
  result_type operator()() {
    return m_dist(m_engine);
  }

private:
  std::uniform_real_distribution<T> m_dist;
  Engine m_engine = {};
};

} // namespace portal

#endif // PORTAL_RANDOM_HPP