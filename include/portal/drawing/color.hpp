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

} // namespace portal::drawing

#endif // PORTAL_DRAWING_COLOR_HPP