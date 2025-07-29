#ifndef __ARES_MATRIX_H__
#define __ARES_MATRIX_H__

#include "concepts.h"
#include "cs3.h"
#include "epsilon.h"
#include "vec3.h"

#include <algorithm>

namespace ares
{

template <typename T>
requires arithmetic<T>
struct Matrix;

using dMatrix = Matrix<double>;
using fMatrix = Matrix<float>;

template <typename T>
requires arithmetic<T>
struct Matrix
{
  /**
   * @brief Indexer operator
   * @param index Index from which to get an element
   * @return Requested element
   */
  constexpr T& operator[](int index);

  /**
   * @brief Indexer operator
   * @param index Index from which to get an element
   * @return Requested element
   */
  constexpr const T& operator[](int index) const;

  /**
   * @brief Multiplication operator
   * @param mx Matrix by which to multiply
   * @return Resulting matrix
   */
  constexpr Matrix operator*(const Matrix& mx) const;

  /**
   * @brief Multiplication assignment operator
   * @param mx Matrix by which to multiply
   */
  constexpr void operator*=(const Matrix& mx);

  /**
   * @brief Multiplication operator
   * @param value Value by which to multiply
   * @return Resulting matrix
   */
  constexpr Matrix operator*(T value) const;

  /**
   * @brief Multiplication assignment operator
   * @param value Value by which to multiply
   */
  constexpr void operator*=(T value);

  /**
   * @brief Division operator
   * @param value Value by which to divide
   * @return Resulting matrix
   */
  constexpr Matrix operator/(T value) const;

  /**
   * @brief Division assignment operator
   * @param value Value by which to divide
   */
  constexpr void operator/=(T value);

  /**
   * @brief Make the inverse matrix
   * @return Resulting matrix
   */
  constexpr Matrix make_inverse() const;

  /**
   * @brief Set this matrix from the provided cs
   * @param cs Coordinate system to use
   */
  constexpr void set_from(const Cs3<T>& cs);

  /**
   * @brief Set the identity matrix
   */
  constexpr void set_identity();

  /**
   * @brief Check if this matrix is the identity matrix
   * @return Result of check
   */
  constexpr bool is_identity() const;

  /**
   * @brief Transform the provided vector by this matrix
   * @param v Vector to transform
   * @return Transformed vector
   */
  constexpr Vec3<T> transform_v(const Vec3<T>& v) const;

  /**
   * @brief Transform the provided point by this matrix
   * @param p Point to transform
   * @return Transformed point
   */
  constexpr Vec3<T> transform_p(const Vec3<T>& p) const;

  // data count
  static const int count{16};
  // matrix data
  T data[count] = {0};
};



template <typename T>
requires arithmetic<T>
constexpr T& Matrix<T>::operator[](int index)
{
  return data[index];
}



template <typename T>
requires arithmetic<T>
constexpr const T& Matrix<T>::operator[](int index) const
{
  return data[index];
}



template <typename T>
requires arithmetic<T>
constexpr Matrix<T> Matrix<T>::operator*(const Matrix& mx) const
{
  Matrix res;
  // 1st row
  res[0] = data[0] * mx[0] + data[4] * mx[1] + data[8] * mx[2] + data[12] * mx[3];
  res[1] = data[1] * mx[0] + data[5] * mx[1] + data[9] * mx[2] + data[13] * mx[3];
  res[2] = data[2] * mx[0] + data[6] * mx[1] + data[10] * mx[2] + data[14] * mx[3];
  res[3] = data[3] * mx[0] + data[7] * mx[1] + data[11] * mx[2] + data[15] * mx[3];
  // 2nd row
  res[4] = data[0] * mx[4] + data[4] * mx[5] + data[8] * mx[6] + data[12] * mx[7];
  res[5] = data[1] * mx[4] + data[5] * mx[5] + data[9] * mx[6] + data[13] * mx[7];
  res[6] = data[2] * mx[4] + data[6] * mx[5] + data[10] * mx[6] + data[14] * mx[7];
  res[7] = data[3] * mx[4] + data[7] * mx[5] + data[11] * mx[6] + data[15] * mx[7];
  // 3rd row
  res[8] = data[0] * mx[8] + data[4] * mx[9] + data[8] * mx[10] + data[12] * mx[11];
  res[9] = data[1] * mx[8] + data[5] * mx[9] + data[9] * mx[10] + data[13] * mx[11];
  res[10] = data[2] * mx[8] + data[6] * mx[9] + data[10] * mx[10] + data[14] * mx[11];
  res[11] = data[3] * mx[8] + data[7] * mx[9] + data[11] * mx[10] + data[15] * mx[11];
  // 4th row
  res[12] = data[0] * mx[12] + data[4] * mx[13] + data[8] * mx[14] + data[12] * mx[15];
  res[13] = data[1] * mx[12] + data[5] * mx[13] + data[9] * mx[14] + data[13] * mx[15];
  res[14] = data[2] * mx[12] + data[6] * mx[13] + data[10] * mx[14] + data[14] * mx[15];
  res[15] = data[3] * mx[12] + data[7] * mx[13] + data[11] * mx[14] + data[15] * mx[15];
  return res;
}



template <typename T>
requires arithmetic<T>
constexpr void Matrix<T>::operator*=(const Matrix& mx)
{
  *this = *this * mx;
}



template <typename T>
requires arithmetic<T>
constexpr Matrix<T> Matrix<T>::operator*(T value) const
{
  Matrix res;
  for (int i = 0; i < count; ++i)
  {
    res[i] = data[i] * value;
  }
  return res;
}



template <typename T>
requires arithmetic<T>
constexpr void Matrix<T>::operator*=(T value)
{
  for (int i = 0; i < count; ++i)
  {
    data[i] *= value;
  }
}



template <typename T>
requires arithmetic<T>
constexpr Matrix<T> Matrix<T>::operator/(T value) const
{
  Matrix res;
  for (int i = 0; i < count; ++i)
  {
    res[i] = data[i] / value;
  }
  return res;
}



template <typename T>
requires arithmetic<T>
constexpr void Matrix<T>::operator/=(T value)
{
  for (int i = 0; i < count; ++i)
  {
    data[i] /= value;
  }
}



template <typename T>
requires arithmetic<T>
constexpr Matrix<T> Matrix<T>::make_inverse() const
{
  Matrix inv;

  // compute cofactor 00
  inv[0] = data[5] * data[10] * data[15] + data[7] * data[9] * data[14]
         + data[6] * data[11] * data[13] - data[7] * data[10] * data[13]
         - data[6] * data[9] * data[15] - data[5] * data[11] * data[14];
  // compute cofactor 01
  inv[1] = data[3] * data[10] * data[13] + data[2] * data[9] * data[15]
         + data[1] * data[11] * data[14] - data[1] * data[10] * data[15]
         - data[2] * data[11] * data[13] - data[3] * data[9] * data[14];
  // compute cofactor 02
  inv[2] = data[1] * data[6] * data[15] + data[2] * data[7] * data[13]
         + data[3] * data[5] * data[14] - data[3] * data[6] * data[13]
         - data[2] * data[5] * data[15] - data[1] * data[7] * data[14];
  // compute cofactor 03
  inv[3] = data[3] * data[6] * data[9] + data[2] * data[5] * data[11] + data[1] * data[7] * data[10]
         - data[1] * data[6] * data[11] - data[2] * data[7] * data[9]
         - data[3] * data[5] * data[10];

  // compute cofactor 10
  inv[4] = data[7] * data[10] * data[12] + data[6] * data[8] * data[15]
         + data[4] * data[11] * data[14] - data[4] * data[10] * data[15]
         - data[6] * data[11] * data[12] - data[7] * data[8] * data[14];
  // compute cofactor 11
  inv[5] = data[0] * data[10] * data[15] + data[2] * data[11] * data[12]
         + data[3] * data[8] * data[14] - data[3] * data[10] * data[12]
         - data[2] * data[8] * data[15] - data[0] * data[11] * data[14];
  // compute cofactor 12
  inv[6] = data[3] * data[6] * data[12] + data[2] * data[4] * data[15]
         + data[0] * data[7] * data[14] - data[0] * data[6] * data[15]
         - data[2] * data[7] * data[12] - data[3] * data[4] * data[14];
  // compute cofactor 13
  inv[7] = data[0] * data[6] * data[11] + data[2] * data[7] * data[8] + data[3] * data[4] * data[10]
         - data[3] * data[6] * data[8] - data[2] * data[4] * data[11]
         - data[0] * data[7] * data[10];

  // compute cofactor 20
  inv[8] = data[4] * data[9] * data[15] + data[5] * data[11] * data[12]
         + data[7] * data[8] * data[13] - data[7] * data[9] * data[12]
         - data[5] * data[8] * data[15] - data[4] * data[11] * data[13];
  // compute cofactor 21
  inv[9] = data[3] * data[9] * data[12] + data[1] * data[8] * data[15]
         + data[0] * data[11] * data[13] - data[0] * data[9] * data[15]
         - data[1] * data[11] * data[12] - data[3] * data[8] * data[13];
  // compute cofactor 22
  inv[10] = data[0] * data[5] * data[15] + data[1] * data[7] * data[12]
          + data[3] * data[4] * data[13] - data[3] * data[5] * data[12]
          - data[1] * data[4] * data[15] - data[0] * data[7] * data[13];
  // compute cofactor 23
  inv[11] = data[3] * data[5] * data[8] + data[1] * data[4] * data[11] + data[0] * data[7] * data[9]
          - data[0] * data[5] * data[11] - data[1] * data[7] * data[8]
          - data[3] * data[4] * data[9];

  // compute cofactor 30
  inv[12] = data[6] * data[9] * data[12] + data[4] * data[10] * data[13]
          + data[5] * data[8] * data[14] - data[4] * data[9] * data[14]
          - data[5] * data[10] * data[12] - data[6] * data[8] * data[13];
  // compute cofactor 31
  inv[13] = data[0] * data[9] * data[14] + data[1] * data[10] * data[12]
          + data[2] * data[8] * data[13] - data[2] * data[9] * data[12]
          - data[1] * data[8] * data[14] - data[0] * data[10] * data[13];
  // compute cofactor 32
  inv[14] = data[2] * data[5] * data[12] + data[1] * data[4] * data[14]
          + data[0] * data[6] * data[13] - data[0] * data[5] * data[14]
          - data[1] * data[6] * data[12] - data[2] * data[4] * data[13];
  // compute cofactor 33
  inv[15] = data[0] * data[5] * data[10] + data[1] * data[6] * data[8] + data[2] * data[4] * data[9]
          - data[2] * data[5] * data[8] - data[1] * data[4] * data[10]
          - data[0] * data[6] * data[9];

  // compute determinant using allready computed cofactors
  T det = data[15] * inv[15] + data[11] * inv[14] + data[7] * inv[13] + data[3] * inv[12];
  // compute inverse matrix
  inv /= det;
  return inv;
}



template <typename T>
requires arithmetic<T>
constexpr void Matrix<T>::set_from(const Cs3<T>& cs)
{
  data[0] = cs.x_axis.x;
  data[1] = cs.x_axis.y;
  data[2] = cs.x_axis.z;
  data[3] = 0;

  data[4] = cs.y_axis.x;
  data[5] = cs.y_axis.y;
  data[6] = cs.y_axis.z;
  data[7] = 0;

  data[8] = cs.z_axis.x;
  data[9] = cs.z_axis.y;
  data[10] = cs.z_axis.z;
  data[11] = 0;

  data[12] = cs.origin.x;
  data[13] = cs.origin.y;
  data[14] = cs.origin.z;
  data[15] = 1;
}



template <typename T>
requires arithmetic<T>
constexpr void Matrix<T>::set_identity()
{
  std::ranges::copy({1, 0, 0, 0}, data);
  data[0] = 1;
  data[1] = 0;
  data[2] = 0;
  data[3] = 0;

  data[4] = 0;
  data[5] = 1;
  data[6] = 0;
  data[7] = 0;

  data[8] = 0;
  data[9] = 0;
  data[10] = 1;
  data[11] = 0;

  data[12] = 0;
  data[13] = 0;
  data[14] = 0;
  data[15] = 1;
}



template <typename T>
requires arithmetic<T>
constexpr bool Matrix<T>::is_identity() const
{
  return eq(1, data[0]) && eq(0, data[1]) && eq(0, data[2]) && eq(0, data[3])      // row 1
      && eq(0, data[4]) && eq(1, data[5]) && eq(0, data[6]) && eq(0, data[7])      // row 2
      && eq(0, data[8]) && eq(0, data[9]) && eq(1, data[10]) && eq(0, data[11])    // row 3
      && eq(0, data[12]) && eq(0, data[13]) && eq(0, data[14]) && eq(1, data[15]); // row 4
}



template <typename T>
requires arithmetic<T>
constexpr Vec3<T> Matrix<T>::transform_v(const Vec3<T>& v) const
{
  return {.x = data[0] * v.x + data[4] * v.y + data[8] * v.z,
    .y = data[1] * v.x + data[5] * v.y + data[9] * v.z,
    .z = data[2] * v.x + data[6] * v.y + data[10] * v.z};
}



template <typename T>
requires arithmetic<T>
constexpr Vec3<T> Matrix<T>::transform_p(const Vec3<T>& p) const
{
  return {.x = data[0] * p.x + data[4] * p.y + data[8] * p.z + data[12],
    .y = data[1] * p.x + data[5] * p.y + data[9] * p.z + data[13],
    .z = data[2] * p.x + data[6] * p.y + data[10] * p.z + data[14]};
}

} // namespace ares

#endif //__ARES_MATRIX_H__
