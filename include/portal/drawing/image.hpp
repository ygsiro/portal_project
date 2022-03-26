/**
 * @file image.hpp
 * @author ygsiro (entoyukari@gmail.com)
 * @brief image
 * @version 0.1
 * @date 2022-03-26
 *
 * @copyright &copy; 2022 ygsiro
 *
 */

#ifndef PORTAL_DRAWING_IMAGE_HPP
#define PORTAL_DRAWING_IMAGE_HPP

#include "color.hpp"
#include <concepts>
#include <memory>
#include <cassert>
#include <stdexcept>

namespace portal::drawing {
/**
 * @brief basic image
 * 
 * @tparam T type
 */
template <pixel_color T>
class basic_image {
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
   * @brief direct access to the underlying array
   *
   * @return Pointer to the underlying element storage.
   * For non-empty containers, the returned pointer compares equal to the address of the first element.
   */
  [[nodiscard]] pointer data() noexcept {
    return m_buf.get();
  }

  /**
   * @brief direct access to the underlying array
   *
   * @return Pointer to the underlying element storage.
   * For non-empty containers, the returned pointer compares equal to the address of the first element.
   */
  [[nodiscard]] const_pointer data() const noexcept {
    return m_buf.get();
  }

  /**
   * @brief Get the width object
   * 
   * @return Return image width
   */
  [[nodiscard]] size_type get_width() const noexcept {
    return m_width;
  }

  /**
   * @brief Get the height object
   * 
   * @return Return image height
   */
  [[nodiscard]] size_type get_height() const noexcept {
    return m_height;
  }

  /**
   * @brief image size
   * 
   * @return Return image size 
   */
  [[nodiscard]] size_type size() const noexcept {
    return get_width() * get_height();
  }

  /**
   * @brief Accessing a specified element
   * 
   * @param[in] x x position
   * @param[in] y y position
   * @return Returns the position of the specified element
   */
  [[nodiscard]] reference operator()(size_type x, size_type y) &noexcept {
    assert(x < get_width());
    assert(y < get_height());
    return data() + get_width() * y + x;
  }

  /**
   * @brief Accessing a specified element
   * 
   * @param[in] x x position
   * @param[in] y y position
   * @return Returns the position of the specified element
   */
  [[nodiscard]] const_reference operator()(size_type x, size_type y) const &noexcept {
    assert(x < get_width());
    assert(y < get_height());
    return data() + get_width() * y + x;
  }

  /**
   * @brief Accessing a specified element
   * 
   * @param[in] x x position
   * @param[in] y y position
   * @return Returns the position of the specified element
   */
  [[nodiscard]] value_type operator()(size_type x, size_type y) const &&noexcept {
    assert(x < get_width());
    assert(y < get_height());
    return data() + get_width() * y + x;
  }

  /**
   * @brief access specified element with bounds checking
   *
   * @param[in] x position of the element to return
   * @param[in] y position of the element to return
   * @return Value to the requested element.
   * 
   * @exception std::out_of_range if x >= get_width() || y >= get_height()
   */
  [[nodiscard]] reference at(size_type x, size_type y) & {
    if (x >= get_width() || y >= get_height())
      throw std::out_of_range("out of range");
    return (*this)(x, y);
  }

  /**
   * @brief access specified element with bounds checking
   *
   * @param[in] x position of the element to return
   * @param[in] y position of the element to return
   * @return Value to the requested element.
   * 
   * @exception std::out_of_range if x >= get_width() || y >= get_height()
   */
  [[nodiscard]] const_reference at(size_type x, size_type y) const & {
    if (x >= get_width() || y >= get_height())
      throw std::out_of_range("out of range");
    return (*this)(x, y);
  }
  
  /**
   * @brief access specified element with bounds checking
   *
   * @param[in] x position of the element to return
   * @param[in] y position of the element to return
   * @return Value to the requested element.
   * 
   * @exception std::out_of_range if x >= get_width() || y >= get_height()
   */
  [[nodiscard]] value_type at(size_type x, size_type y) const && {
    if (x >= get_width() || y >= get_height())
      throw std::out_of_range("out of range");
    return (*this)(x, y);
  }

  /**
   * @brief returns an iterator to the beginning
   *
   * @return Iterator to the first element.
   */
  [[nodiscard]] iterator begin() noexcept {
    return data();
  }

  /**
   * @brief returns an iterator to the beginning
   *
   * @return Iterator to the first element.
   */
  [[nodiscard]] const_iterator begin() const noexcept {
    return data();
  }

  /**
   * @brief returns an iterator to the beginning
   *
   * @return Iterator to the first element.
   */
  [[nodiscard]] const_iterator cbegin() const noexcept {
    return data();
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] iterator end() noexcept {
    return data() + size();
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] const_iterator end() const noexcept {
    return data() + size();
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] const_iterator cend() const noexcept {
    return data() + size();
  }

  /**
   * @brief returns a reverse iterator to the beginning
   *
   * @return Reverse iterator to the first element.
   */
  [[nodiscard]] reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }

  /**
   * @brief returns a reverse iterator to the beginning
   *
   * @return Reverse iterator to the first element.
   */
  [[nodiscard]] const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  /**
   * @brief returns a reverse iterator to the beginning
   *
   * @return Reverse iterator to the first element.
   */
  [[nodiscard]] const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cend());
  }

  /**
   * @brief returns a reverse iterator to the end
   *
   * @return Reverse iterator to the last element.
   */
  [[nodiscard]] reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }

  /**
   * @brief returns a reverse iterator to the end
   *
   * @return Reverse iterator to the last element.
   */
  [[nodiscard]] const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }

  /**
   * @brief returns a reverse iterator to the end
   *
   * @return Reverse iterator to the last element.
   */
  [[nodiscard]] const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cbegin());
  }

  /**
   * @brief fill the container with specified value
   *
   * @param[in] pixel the pixel to assign to the elements
   * @return *this
   */
  constexpr basic_image &fill(const value_type &pixel) noexcept {
    for (auto &ptr : *this)
      ptr = pixel;
    return *this;
  }

private:
  size_type m_width          = 0;
  size_type m_height         = 0;
  std::unique_ptr<T[]> m_buf = nullptr;
};
} // namespace portal::drawing

#endif // PORTAL_DRAWING_IMAGE_HPP