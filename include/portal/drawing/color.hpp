/**
 * @file color.hpp
 * @author ygsiro (entoyukari@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright &copy; 2022 ygsiro
 * 
 */
#ifndef PORTAL_DRAWING_COLOR_HPP
#define PORTAL_DRAWING_COLOR_HPP

#include <cstdint>

/**
 * @brief drawing namespace
 *
 */
namespace portal::drawing {
/**
 * @brief BGRA color
 *
 * @tparam T sample type
 */
template <typename T>
struct basic_bgra {
  using sample_type = T; //!< @brief sample type
  sample_type blue;      //!< @brief blue
  sample_type green;     //!< @brief green
  sample_type red;       //!< @brief red
  sample_type alpha;     //!< @brief alpha
};

/**
 * @brief RGBA color
 *
 * @tparam T sample type
 */
template <typename T>
struct basic_rgba {
  using sample_type = T; //!< @brief sample type
  sample_type red;       //!< @brief red
  sample_type green;     //!< @brief green
  sample_type blue;      //!< @brief blue
  sample_type alpha;     //!< @brief alpha
};

/**
 * @brief BGR color
 *
 * @tparam T sample type
 */
template <typename T>
struct basic_bgr {
  using sample_type = T; //!< @brief sample type
  sample_type blue;      //!< @brief blue
  sample_type green;     //!< @brief green
  sample_type red;       //!< @brief red
};

/**
 * @brief RGB color
 *
 * @tparam T sample type
 */
template <typename T>
struct basic_rgb {
  using sample_type = T; //!< @brief sample type
  sample_type red;       //!< @brief red
  sample_type green;     //!< @brief green
  sample_type blue;      //!< @brief blue
};

/**
 * @brief Grayscale and alpha
 *
 * @tparam T
 */
template <typename T>
struct basic_ga {
  using sample_type = T; //!< @brief sample type
  sample_type gray;      //!< @brief gray
  sample_type alpha;     //!< @brief alpha
};

/**
 * @brief Grayscale
 *
 * @tparam T
 */
template <typename T>
struct basic_g {
  using sample_type = T; //!< @brief sample type
  sample_type gray;      //!< @brief gray
};

/**
 * @brief pixel color
 *
 * @tparam T type
 */
template <typename T>
concept pixel_color = requires(T &a) {
  typename T::sample_type;
};

/**
 * @brief alpha color
 * 
 * @tparam T type
 */
template <typename T>
concept alpha_color = requires(T &a) {
  typename T::sample_type;
  a.alpha;
};

/**
 * @brief RGB color
 * 
 * @tparam T type
 */
template <typename T>
concept true_color = requires(T &a) {
  typename T::sample_type;
  a.red;
  a.green;
  a.blue;
};

/**
 * @brief Grayscale
 * 
 * @tparam T type
 */
template <typename T>
concept gray_color = requires(T &a) {
  typename T::sample_type;
  a.gray;
};

} // namespace portal::drawing

#endif // PORTAL_DRAWING_COLOR_HPP