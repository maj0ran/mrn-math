#pragma once

#include "vector.hpp"

template <typename T, std::size_t _cols, std::size_t _rows>
class mat
{
 private:
   /* We make our Matrix column-major, because that's what OpenGL
    * does.
    * That is, we should think of our matrix as a concatenation of
    * columns-vectors
    */
   union
   {
      T data[_cols][_rows];
      struct
      {
         vec<T, _rows> cols[_cols];
      };
   };

 public:
   /* Default-Constructor generates the identity-matrix
    */
   mat ()
   {
      for (std::size_t x = 0; x < _cols; x++) {
         for (std::size_t y = 0; y < _rows; y++) {
            (*this)[x][y] = (x == y ? 1 : 0);
         }
      }
   }

   /* Element-wise constructor, pass a list of vectors.
    * note that we have to pass column-vectors
    */
   mat (const std::initializer_list<std::initializer_list<T>> &vals)
   {
      std::size_t x = 0;
      std::size_t y = 0;
      for (const auto &it_x : vals) {
         for (const auto &it_y : it_x) {
            data[x][y++] = it_y;
         }
         y = 0;
         x++;
      }
   }

   /* Get a column with the []-operator, then use the []-operator
    * at the vector, so we can use [][] to get a single cell
    */
   inline auto operator[] (std::size_t col) -> vec<T, _rows> &
   {
      return this->cols[col];
   }

   /* Get cell via XY-vector, if you want
    */
   inline auto operator[] (vec2i idx) -> T &
   {
      return data[idx.x][idx.y];
   }

   /* Matrix + Matrix
    */
   inline auto operator+= (mat<T, _cols, _rows> &m) -> mat<T, _cols, _rows> &
   {
      for (std::size_t i = 0; i < _rows; i++) {
         for (std::size_t j = 0; j < _cols; j++) {
            (*this)[j][i] += m[j][i];
         }
      }
      return *this;
   }

   inline auto operator+ (mat<T, _cols, _rows> &m) -> mat<T, _cols, _rows>
   {
      return mat (*this) += m;
   }

   /* Matrix - Matrix
    */
   inline auto operator-= (mat<T, _cols, _rows> &m) -> mat<T, _cols, _rows> &
   {
      for (std::size_t i = 0; i < _rows; i++) {
         for (std::size_t j = 0; j < _cols; j++) {
            (*this)[j][i] -= m[j][i];
         }
      }
      return *this;
   }

   inline auto operator- (mat<T, _cols, _rows> &m) -> mat<T, _cols, _rows>
   {
      return mat (*this) -= m;
   }

   /* Matrix * Vector
    */
   inline auto operator* (vec<T, _rows> v) -> vec<T, _rows>
   {
      vec<T, _rows> result = {};
      for (std::size_t i = 0; i < _rows; i++) {
         for (std::size_t j = 0; j < _cols; j++) {
            result[i] += (*this)[j][i] * v[j];
         }
      }
      return result;
   }

   /* Matrix * Matrix
    */
   template <std::size_t _o>
   inline auto operator* (mat<T, _cols, _o> m) -> mat<T, _rows, _o>
   {
      mat<T, _o, _rows> result;
      for (std::size_t i = 0; i < _rows; i++) {
         for (std::size_t j = 0; j < _cols; j++) {
            T value = {};
            for (std::size_t k = 0; k < _cols; k++) {
               value += (*this)[k][i] * m[j][k];
            }
            result[j][i] = value;
         }
      }
      return result;
   }

   static inline auto translate (const T x, const T y, const T z) -> mat<T, 4, 4>
   {
      return mat ({ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { x, y, z, 1 } });
   }

   static inline auto translate (const vec<T, 3> &v) -> mat<T, 4, 4>
   {
      return translate (v.x, v.y, v.z);
   }

   static inline auto translate (const T x, const T y) -> mat<T, 3, 3>
   {
      return mat<T, 3, 3> ({ { 1, 0, 0 }, { 0, 1, 0 }, { x, y, 1 } });
   }

   static inline auto translate (const vec<T, 2> &v) -> mat<T, 3, 3>
   {
      return translate (v.x, v.y);
   }

   static inline auto scale (const T x, const T y, const T z) -> mat<T, 4, 4>
   {
      return mat ({ { x, 0, 0, 0 }, { 0, y, 0, 0 }, { 0, 0, z, 0 }, { 0, 0, 0, 1 } });
   }

   static inline auto scale (vec<T, 3> &v) -> mat<T, 3, 3>
   {
      return scale (v.x, v.y, v.z);
   }

   static inline auto rotate (const vec<T, 3> axis, T rad) -> mat<T, 4, 4>
   {
      const float c  = cos (rad);
      const float s  = sin (rad);
      const float ic = 1.0 - c;
      const T &   x  = axis.x;
      const T &   y  = axis.y;
      const T &   z  = axis.z;

      return mat ({ { x * x * ic + c, y * x * ic + z * s, z * x * ic - y * s, 0 },
                    { x * y * ic - z * s, y * y * ic + c, z * y * ic + x * s, 0 },
                    { x * z * ic + y * s, y * z * ic - x * s, z * z * ic + c, 0 },
                    { 0, 0, 0, 1 } });
   }
};

typedef mat<float, 4, 4> mat4;
typedef mat<float, 3, 3> mat3;
typedef mat<float, 2, 2> mat2;

typedef mat<float, 4, 2> mat4x2;
typedef mat<float, 4, 3> mat4x3;
typedef mat<float, 2, 4> mat2x4;
typedef mat<float, 2, 3> mat2x3;

typedef mat<int, 4, 4> mat4i;
typedef mat<int, 3, 3> mat3i;
typedef mat<int, 2, 2> mat2i;

typedef mat<int, 4, 2> mat4x2i;
typedef mat<int, 4, 3> mat4x3i;
typedef mat<int, 2, 4> mat2x4i;
typedef mat<int, 2, 3> mat2x3i;

typedef mat<double, 4, 4> mat4d;
typedef mat<double, 3, 3> mat3d;
typedef mat<double, 2, 2> mat2d;

typedef mat<double, 4, 2> mat4x2d;
typedef mat<double, 4, 3> mat4x3d;
typedef mat<double, 2, 4> mat2x4d;
typedef mat<double, 2, 3> mat2x3d;

typedef mat<bool, 4, 4> mat4b;
typedef mat<bool, 3, 3> mat3b;
typedef mat<bool, 2, 2> mat2b;

typedef mat<bool, 4, 2> mat4x2b;
typedef mat<bool, 4, 3> mat4x3b;
typedef mat<bool, 2, 4> mat2x4b;
typedef mat<bool, 2, 3> mat2x3b;
