#ifndef __ARES_CURVE_H__
#define __ARES_CURVE_H__

#include <cmath>

namespace ares
{

/**
 * @brief Parametric curve interpolation (defined on the [0, 1] interval)
 */
struct Curve
{
  /**
   * @brief Linear interpolation
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double linear(double progress);

  /**
   * @brief Accelerated quadratic interpolation
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double in_quad(double progress);

  /**
   * @brief Decelerated quadratic interpolation
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double out_quad(double progress);

  /**
   * @brief Accelerated to half way then decelerated (quadratic interpolation)
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double in_out_quad(double progress);

  /**
   * @brief Decelerated to half way then accelerated (quadratic interpolation)
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double out_in_quad(double progress);

  /**
   * @brief Accelerated cubic interpolation
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double in_cubic(double progress);

  /**
   * @brief Decelerated cubic interpolation
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double out_cubic(double progress);

  /**
   * @brief Accelerated to half way then decelerated (cubic interpolation)
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double in_out_cubic(double progress);

  /**
   * @brief Decelerated to half way then accelerated (cubic interpolation)
   * @param progress Progress to use in [0, 1] interval
   * @return Value at progress
   */
  static double out_in_cubic(double progress);
};



inline double Curve::linear(double progress)
{
  return progress;
}



inline double Curve::in_quad(double progress)
{
  return pow(progress, 2);
}



inline double Curve::out_quad(double progress)
{
  return 1 - pow(1 - progress, 2);
}



inline double Curve::in_out_quad(double progress)
{
  return progress <= 0.5 ? 2 * pow(progress, 2) : 1 - 2 * pow(1 - progress, 2);
}



inline double Curve::out_in_quad(double progress)
{
  return progress <= 0.5 ? 0.5 - 2 * pow(0.5 - progress, 2) : 0.5 + 2 * pow(progress - 0.5, 2);
}



inline double Curve::in_cubic(double progress)
{
  return pow(progress, 3);
}



inline double Curve::out_cubic(double progress)
{
  return 1 - pow(1 - progress, 3);
}



inline double Curve::in_out_cubic(double progress)
{
  return progress <= 0.5 ? 4 * pow(progress, 3) : 1 - 4 * pow(1 - progress, 3);
}



inline double Curve::out_in_cubic(double progress)
{
  return progress <= 0.5 ? 0.5 - 4 * pow(0.5 - progress, 3) : 0.5 + 4 * pow(progress - 0.5, 3);
}

} // namespace ares

#endif //__ARES_CURVE_H__
