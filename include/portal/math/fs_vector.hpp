/**
 * @file fs_vector.hpp
 * @author ygsiro (entoyukari@gmail.com)
 * @brief fix size vector
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright &copy; 2022 ygsiro
 *
 */
#ifndef PORTAL_MATH_FS_VECTOR_HPP
#define PORTAL_MATH_FS_VECTOR_HPP

#include "math.hpp"
#include "../random.hpp"

namespace portal::math {
/**
 * @brief tag namespace
 *
 */
namespace tag {
/**
 * @brief fill tag
 *
 */
struct fill_t {
} fill;
} // namespace tag

/**
 * @brief vector class concept
 *
 * @tparam T type
 */
template <typename T>
concept vector_class = requires(T &a, std::size_t i) {
  typename T::value_type;
  typename T::pointer;
  typename T::reference;
  typename T::const_pointer;
  typename T::const_reference;
  typename T::size_type;
  {a[i]};
  {a.size()};
};

/**
 * @brief fix size vector
 *
 * @tparam T type
 * @tparam N size
 */
template <typename T, std::size_t N>
class fs_vector {
public:
  using value_type      = T;           //!< @brief value type
  using pointer         = T *;         //!< @brief pointer
  using const_pointer   = const T *;   //!< @brief const pointer
  using reference       = T &;         //!< @brief reference
  using const_reference = const T &;   //!< @brief const reference
  using size_type       = std::size_t; //!< @brief size type

  using iterator               = pointer;                               //!< @brief iterator
  using const_iterator         = const_pointer;                         //!< @brief const iterator
  using reverse_iterator       = std::reverse_iterator<iterator>;       //!< @brief reverse iterator
  using const_reverse_iterator = std::reverse_iterator<const_iterator>; //!< @brief const reverse iterator
  /**
   * @brief default constructor
   *
   */
  constexpr fs_vector() noexcept = default;
  /**
   * @brief copy constructor
   *
   */
  constexpr fs_vector(const fs_vector &) noexcept = default;
  /**
   * @brief move constructor
   *
   */
  constexpr fs_vector(fs_vector &&) noexcept = default;

  /**
   * @brief constructor
   *
   * @param[in] args variable argument
   *
   * @pre sizeof...(args) <= N
   *
   */
  constexpr fs_vector(const std::convertible_to<T> auto &...args) noexcept
      : m_elem{static_cast<T>(args)...} {
  }

  /**
   * @brief constructor
   *
   * @param[in] vec vector concept
   *
   */
  constexpr explicit fs_vector(const vector_class auto &vec) {
    if (size() != vec.size())
      throw std::invalid_argument("vector size vary");
    for (size_type i = 0; i < N; ++i)
      m_elem[i] = vec[i];
  }

  /**
   * @brief fill constructor
   *
   * @param[in] tag fill tag
   * @param[in] scalar fill value
   *
   */
  constexpr fs_vector([[maybe_unused]] const tag::fill_t &tag, const T scalar) noexcept {
    fill(scalar);
  }

  /**
   * @brief copy assign
   *
   * @return *this
   */
  constexpr fs_vector &operator=(const fs_vector &) noexcept = default;

  /**
   * @brief move assign
   *
   * @return *this
   */
  constexpr fs_vector &operator=(fs_vector &&) noexcept = default;

  /**
   * @brief assign
   *
   * @param[in] vec vector concept
   * @return *this
   */
  constexpr fs_vector &operator=(const vector_class auto &vec) {
    if (size() != vec.size())
      throw std::invalid_argument("vector size vary");
    for (size_type i = 0; i < N; ++i)
      m_elem[i] = vec[i];
    return *this;
  }

  /**
   * @brief access specified element
   *
   * @param[in] pos	position of the element to return
   * @return Reference to the requested element.
   * 
   * @pre pos < size()
   */
  [[nodiscard]] constexpr reference operator[](size_type pos) &noexcept {
    assert(pos < size());
    return m_elem[pos];
  }

  /**
   * @brief access specified element
   *
   * @param[in] pos	position of the element to return
   * @return Reference to the requested element.
   * 
   * @pre pos < size()
   */
  [[nodiscard]] constexpr const_reference operator[](size_type pos) const &noexcept {
    assert(pos < size());
    return m_elem[pos];
  }

  /**
   * @brief access specified element
   *
   * @param[in] pos	position of the element to return
   * @return Value to the requested element.
   * 
   * @pre pos < size()
   */
  [[nodiscard]] constexpr value_type operator[](size_type pos) const &&noexcept {
    assert(pos < size());
    return m_elem[pos];
  }

  /**
   * @brief access specified element with bounds checking
   *
   * @param[in] pos position of the element to return
   * @return Reference to the requested element.
   * 
   * @exception std::out_of_range if pos >= size
   */
  [[nodiscard]] constexpr reference at(size_type pos) & {
    if (pos >= size())
      throw std::out_of_range("out of range");
    return m_elem[pos];
  }

  /**
   * @brief access specified element with bounds checking
   *
   * @param[in] pos position of the element to return
   * @return Reference to the requested element.
   * 
   * @exception std::out_of_range if pos >= size
   */
  [[nodiscard]] constexpr const_reference at(size_type pos) const & {
    if (pos >= size())
      throw std::out_of_range("out of range");
    return m_elem[pos];
  }

  /**
   * @brief access specified element with bounds checking
   *
   * @param[in] pos position of the element to return
   * @return Value to the requested element.
   * 
   * @exception std::out_of_range if pos >= size
   */
  [[nodiscard]] constexpr value_type at(size_type pos) const && {
    if (pos >= size())
      throw std::out_of_range("out of range");
    return m_elem[pos];
  }

  /**
   * @brief returns the number of elements
   *
   * @return The number of elements in the container.
   */
  [[nodiscard]] constexpr size_type size() const noexcept {
    return N;
  }

  /**
   * @brief checks whether the container is empty
   * 
   * @return true container is empty
   * @return false container isn't empty
   */
  [[nodiscard]] constexpr bool empty() const noexcept {
    return size() == 0;
  }

  /**
   * @brief direct access to the underlying array
   *
   * @return Pointer to the underlying element storage.
   * For non-empty containers, the returned pointer compares equal to the address of the first element.
   */
  [[nodiscard]] constexpr pointer data() noexcept {
    return m_elem;
  }

  /**
   * @brief direct access to the underlying array
   *
   * @return Pointer to the underlying element storage.
   * For non-empty containers, the returned pointer compares equal to the address of the first element.
   */
  [[nodiscard]] constexpr const_pointer data() const noexcept {
    return m_elem;
  }

  /**
   * @brief returns an iterator to the beginning
   *
   * @return Iterator to the first element.
   */
  [[nodiscard]] constexpr iterator begin() noexcept {
    return data();
  }

  /**
   * @brief returns an iterator to the beginning
   *
   * @return Iterator to the first element.
   */
  [[nodiscard]] constexpr const_iterator begin() const noexcept {
    return data();
  }

  /**
   * @brief returns an iterator to the beginning
   *
   * @return Iterator to the first element.
   */
  [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
    return data();
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] constexpr iterator end() noexcept {
    return data() + size();
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] constexpr const_iterator end() const noexcept {
    return data() + size();
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return data() + size();
  }

  /**
   * @brief returns a reverse iterator to the beginning
   *
   * @return Reverse iterator to the first element.
   */
  [[nodiscard]] constexpr reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }

  /**
   * @brief returns a reverse iterator to the beginning
   *
   * @return Reverse iterator to the first element.
   */
  [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  /**
   * @brief returns a reverse iterator to the beginning
   *
   * @return Reverse iterator to the first element.
   */
  [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cend());
  }

  /**
   * @brief returns a reverse iterator to the end
   *
   * @return Reverse iterator to the last element.
   */
  [[nodiscard]] constexpr reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }

  /**
   * @brief returns a reverse iterator to the end
   *
   * @return Reverse iterator to the last element.
   */
  [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }

  /**
   * @brief returns a reverse iterator to the end
   *
   * @return Reverse iterator to the last element.
   */
  [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cbegin());
  }

  /**
   * @brief fill the container with specified value
   *
   * @param[in] value	the value to assign to the elements
   * @return *this
   */
  constexpr fs_vector &fill(const std::convertible_to<T> auto &value) noexcept {
    for (auto &ptr : m_elem)
      ptr = value;
    return *this;
  }

  /**
   * @brief addition assignment operator
   *
   * @param[in] vec vector
   * @return *this
   */
  constexpr fs_vector &operator+=(const fs_vector &vec) noexcept {
    for (size_type index = 0; index < size(); ++index)
      m_elem[index] += vec[index];
    return *this;
  }

  /**
   * @brief addition assignment operator
   *
   * @param[in] vec vector concept
   * @return *this
   * 
   * @exception std::invalid_argumnet if size() != vec.size()
   */
  constexpr fs_vector &operator+=(const vector_class auto &vec) {
    if (size() != vec.size())
      throw std::invalid_argument("vector sizes vary");
    for (size_type index = 0; index < size(); ++index)
      m_elem[index] += vec[index];
    return *this;
  }

  /**
   * @brief subtraction assignment operator
   *
   * @param[in] vec vector concept
   * @return *this
   */
  constexpr fs_vector &operator-=(const fs_vector &vec) noexcept {
    for (size_type index = 0; index < size(); ++index)
      m_elem[index] -= vec[index];
    return *this;
  }
  
  /**
   * @brief subtraction assignment operator
   *
   * @param[in] vec vector concept
   * @return *this
   * 
   * @exception std::invalid_argumnet if size() != vec.size()
   */
  constexpr fs_vector &operator-=(const vector_class auto &vec) {
    if (size() != vec.size())
      throw std::invalid_argument("vector sizes vary");
    for (size_type index = 0; index < size(); ++index)
      m_elem[index] += vec[index];
    return *this;
  }

  
  /**
   * @brief multiplication assignment operator
   *
   * @param[in] scal scalar
   * @return *this
   */
  constexpr fs_vector &operator*=(const T &scal) noexcept {
    for (auto &ptr : m_elem)
      ptr *= scal;
    return *this;
  }

  /**
   * @brief division assignment operator
   *
   * @param[in] scal scalar
   * @return *this
   */
  constexpr fs_vector &operator/=(const T &scal) noexcept {
    assert(!is_zero(scal));
    for (auto &ptr : m_elem)
      ptr /= scal;
    return *this;
  }

  /**
   * @brief unary plus
   *
   * @return copy vector
   */
  [[nodiscard]] constexpr fs_vector operator+() const noexcept {
    return *this;
  }

  /**
   * @brief unary minus
   *
   * @return negated vector
   */
  [[nodiscard]] constexpr fs_vector operator-() const noexcept {
    auto res = *this;
    for (auto &p : res)
      p = -p;
    return res;
  }

  /**
   * @brief specializes the std::swap algorithm 
   *
   * @param[in] vec fs_vector
   * @return *this
   */
  [[nodiscard]] constexpr fs_vector &swap(fs_vector &vec) noexcept {
    std::swap(m_elem, vec.m_elem);
    return *this;
  }

private:
  value_type m_elem[N > 0 ? N : 1] = {};
};

/**
 * @brief addition
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return Returns the result of adding lhs and rhs.
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> operator+(const fs_vector<T, N> &lhs, const vector_class auto &rhs) noexcept(noexcept(fs_vector<T, N>(lhs) += rhs)) {
  return fs_vector<T, N>(lhs) += rhs;
}

/**
 * @brief subtraction
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return Returns the result of subtracting lhs and rhs
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> operator-(const fs_vector<T, N> &lhs, const vector_class auto &rhs) noexcept(noexcept(fs_vector<T, N>(lhs) -= rhs)) {
  return fs_vector<T, N>(lhs) -= rhs;
}

/**
 * @brief multiplication
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs scalar
 * @return Returns the result of multiplying lhs and rhs.
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> operator*(const fs_vector<T, N> &lhs, const T &rhs) noexcept {
  return fs_vector<T, N>(lhs) *= rhs;
}

/**
 * @brief multiplication
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs scalar
 * @param[in] rhs vector
 * @return Returns the result of multiplying lhs and rhs.
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> operator*(const T &lhs, const fs_vector<T, N> &rhs) noexcept {
  return fs_vector<T, N>(rhs) *= lhs;
}

/**
 * @brief division
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs scalar
 * @return Returns the result of dividing lhs by rhs.
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> operator/(const fs_vector<T, N> &lhs, const T &rhs) noexcept {
  assert(!is_zero(rhs));
  return fs_vector<T, N>(lhs) /= rhs;
}

/**
 * @brief Compare
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return true lhs and rhs are the same value
 * @return false lhs and rhs are different values.
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr bool operator==(const fs_vector<T, N> &lhs, const fs_vector<T, N> &rhs) noexcept {
  for (std::size_t i = 0; i < N; ++i)
    if constexpr (std::is_floating_point_v<T>) {
      if (fpcmp(lhs[i], rhs[i]) != 0)
        return false;
    } else {
      if (lhs[i] == rhs[i])
        return false;
    }
  return true;
}

/**
 * @brief Compare
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return true lhs and rhs are different values.
 * @return false lhs and rhs are the same value
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr bool operator!=(const fs_vector<T, N> &lhs, const fs_vector<T, N> &rhs) noexcept {
  return !(lhs == rhs);
}

/**
 * @brief Multiply each element of the vector.
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> mul_peram(const fs_vector<T, N> &lhs, const fs_vector<T, N> &rhs) noexcept {
  fs_vector<T, N> res(lhs);
  for (size_t i = 0; i < N; ++i)
    res[i] *= rhs[i];
  return res;
}

/**
 * @brief Multiply each element of the vector.
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> mul_peram(const fs_vector<T, N> &lhs, const vector_class auto &rhs) {
  if (lhs.size() != rhs.size())
    throw std::invalid_argument("vector sizes vary");
  fs_vector<T, N> res(lhs);
  for (size_t i = 0; i < N; ++i)
    res[i] *= rhs[i];
  return res;
}

/**
 * @brief Select the larger value of each element of the vector
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> max_peram(const fs_vector<T, N> &lhs, const fs_vector<T, N> &rhs) noexcept {
  fs_vector<T, N> res(lhs);
  for (size_t i = 0; i < N; ++i)
    res[i] *= std::max<T>(res[i], rhs[i]);
  return res;
}

/**
 * @brief Select the larger value of each element of the vector
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> max_peram(const fs_vector<T, N> &lhs, const vector_class auto &rhs) {
  if (lhs.size() != rhs.size())
    throw std::invalid_argument("vector sizes vary");
  fs_vector<T, N> res(lhs);
  for (size_t i = 0; i < N; ++i)
    res[i] = std::max<T>(res[i], rhs[i]);
  return res;
}

/**
 * @brief Select a smaller value for each element of the vector
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> min_peram(const fs_vector<T, N> &lhs, const fs_vector<T, N> &rhs) noexcept {
  fs_vector<T, N> res(lhs);
  for (size_t i = 0; i < N; ++i)
    res[i] *= std::min<T>(res[i], rhs[i]);
  return res;
}

/**
 * @brief Select a smaller value for each element of the vector
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> min_peram(const fs_vector<T, N> &lhs, const vector_class auto &rhs) {
  if (lhs.size() != rhs.size())
    throw std::invalid_argument("vector sizes vary");
  fs_vector<T, N> res(lhs);
  for (size_t i = 0; i < N; ++i)
    res[i] = std::min<T>(res[i], rhs[i]);
  return res;
}

/**
 * @brief dot product of vectors
 *
 * @tparam T type
 * @tparam N size
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return Return the dot product of lhs and rhs
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr T dot(const fs_vector<T, N> &lhs, const fs_vector<T, N> &rhs) noexcept {
  T res = {};
  for (std::size_t i = 0; i < N; ++i)
    res += lhs[i] * rhs[i];
  return res;
}

/**
 * @brief square of the norm.
 *
 * @tparam T type
 * @tparam N size
 * @param[in] vec vector
 * @return Return the square norm of vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr T sqr_norm(const fs_vector<T, N> &vec) noexcept {
  return dot(vec, vec);
}

/**
 * @brief norm
 *
 * @tparam T type
 * @tparam N size
 * @param[in] vec vector
 * @return Return the norm of vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr T norm(const fs_vector<T, N> &vec) noexcept {
  return slow_sqrt(sqr_norm(vec));
}

/**
 * @brief nor,alized
 *
 * @tparam T type
 * @tparam N size
 * @param[in] vec vector
 * @return Return normalized vector
 * 
 * @pre vec isn't zero vector
 */
template <typename T, std::size_t N>
[[nodiscard]] constexpr fs_vector<T, N> normalized(const fs_vector<T, N> &vec) noexcept {
  return vec / norm(vec);
}

/**
 * @brief cross
 *
 * @tparam T type
 * @param[in] lhs vector
 * @param[in] rhs vector
 * @return vector
 */
template <typename T>
[[nodiscard]] constexpr fs_vector<T, 3> cross(const fs_vector<T, 3> &lhs, const fs_vector<T, 3> &rhs) noexcept {
  return fs_vector<T, 3>{
      lhs[1] * rhs[2] - lhs[2] * rhs[1],
      lhs[2] * rhs[0] - lhs[0] * rhs[2],
      lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

}; // namespace portal::math

#endif // PORTAL_MATH_FS_VECTOR_HPP