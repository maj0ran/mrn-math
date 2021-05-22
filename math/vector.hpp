#pragma once

#include <cassert>
#include <initializer_list>
#include <math.h>

/* generic n-dimensional vector class.
 * the vector class can have arbitrary size.
 * We also write special classes for size 2,3,4
 * to allow component-names
 */

#define vec_n vec<T, n>
template <typename T, std::size_t n>
class vec
{
 public:
   /* default constructor has no initialization
    */
   vec () = default;

   /* single value constructor gives all elements
    * the same value
    */
   vec (const T &val)
   {
      for (std::size_t i = 0; i < n; i++) {
         _data[i] = val;
      }
   }

   vec (const std::initializer_list<T> &vals)
   {
      std::size_t i = 0;
      for (auto it = vals.begin (); it != vals.end (); ++it) {
         _data[i++] = *it;
      }
   }

   ~vec () = default;

   inline auto operator[] (std::size_t idx) -> T &
   {
      return this->_data[idx];
   }

   inline auto operator+= (vec_n &v) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] += v[i];
      return *this;
   }

   inline auto operator-= (vec_n &v) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] -= v[i];
      return *this;
   }

   inline auto operator*= (vec_n &v) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] *= v[i];
      return *this;
   }

   inline auto operator/= (vec_n &v) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] /= v[i];
      return *this;
   }

   inline auto operator+= (T scalar) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] += scalar;
      return *this;
   }

   inline auto operator-= (T scalar) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] -= scalar;
      return *this;
   }
   inline auto operator*= (T scalar) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] *= scalar;
      return *this;
   }

   inline auto operator/= (T scalar) -> vec_n &
   {
      for (std::size_t i = 0; i < n; i++)
         (*this)[i] /= scalar;
      return *this;
   }

 private:
   T _data[n];
};

/* specialized classes for dimensions 2,3,4.
 * so we can have component-names like x,y,z
 * and r,g,b,a
 */

#define vec_2 vec<T, 2>
template <typename T>
class vec_2
{
 public:
   vec () = default;

   vec (const T &val)
   {
      x = y = val;
   }

   // give the specialized case its own constructor
   // so we don't have to use initializer_list-syntax
   vec (const T &n1, const T &n2)
   {
      x = n1;
      y = n2;
   }
   // hack this to avoid a visible _data[] field.
   // because we can't have private member inside the union
   inline auto operator[] (std::size_t idx) -> T &
   {
      assert (("Index out of range\n" && idx < 2));
      return *(reinterpret_cast<T *> (this) + idx);
   }

   inline auto operator+= (vec_2 &v) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] += v[i];
      return *this;
   }

   inline auto operator-= (vec_2 &v) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] -= v[i];
      return *this;
   }

   inline auto operator*= (vec_2 &v) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] *= v[i];
      return *this;
   }

   inline auto operator/= (vec_2 &v) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] /= v[i];
      return *this;
   }

   inline auto operator+= (T scalar) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] += scalar;
      return *this;
   }

   inline auto operator-= (T scalar) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] -= scalar;
      return *this;
   }
   inline auto operator*= (T scalar) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] *= scalar;
      return *this;
   }

   inline auto operator/= (T scalar) -> vec_2 &
   {
      for (std::size_t i = 0; i < 2; i++)
         (*this)[i] /= scalar;
      return *this;
   }

   union
   {
      struct
      {
         T x;
         T y;
      };
      struct
      {
         T u;
         T v;
      };
   };
};

#define vec_3 vec<T, 3>
template <typename T>
class vec<T, 3>
{
 public:
   vec () = default;

   vec (const T &val)
   {
      x = y = z = val;
   }

   vec (const T &n1, const T &n2, const T &n3)
   {
      x = n1;
      y = n2;
      z = n3;
   }

   auto operator[] (std::size_t idx) -> T &
   {
      assert (("Index out of range\n" && idx < 3));
      return *(reinterpret_cast<T *> (this) + idx);
   }

   inline auto operator+= (vec_3 &v) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] += v[i];
      return *this;
   }

   inline auto operator-= (vec_3 &v) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] -= v[i];
      return *this;
   }

   inline auto operator*= (vec_3 &v) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] *= v[i];
      return *this;
   }

   inline auto operator/= (vec_3 &v) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] /= v[i];
      return *this;
   }

   inline auto operator+= (T scalar) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] += scalar;
      return *this;
   }

   inline auto operator-= (T scalar) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] -= scalar;
      return *this;
   }
   inline auto operator*= (T scalar) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] *= scalar;
      return *this;
   }

   inline auto operator/= (T scalar) -> vec_3 &
   {
      for (std::size_t i = 0; i < 3; i++)
         (*this)[i] /= scalar;
      return *this;
   }

   union
   {
      struct
      {
         T x;
         T y;
         T z;
      };
      struct
      {
         T r;
         T g;
         T b;
      };
      struct
      {
         T s;
         T t;
         T u;
      };
      struct
      {
         vec<T, 2> xy;
      };
      struct
      {
         vec<T, 2> uv;
      };
   };

   static const vec_3 UP;
   static const vec_3 DOWN;
   static const vec_3 LEFT;
   static const vec_3 RIGHT;
   static const vec_3 FORWARD;
   static const vec_3 BACK;
};

template <typename T>
const vec_3 vec_3::UP = vec_3 (0.0, 1.0, 0.0);
template <typename T>
const vec_3 vec_3::DOWN = vec_3 (0.0, -1.0, 0.0);
template <typename T>
const vec_3 vec_3::LEFT = vec_3 (-1.0, 0.0, 0.0);
template <typename T>
const vec_3 vec_3::RIGHT = vec_3 (1.0, 0.0, 0.0);
template <typename T>
const vec_3 vec_3::FORWARD = vec_3 (0.0, 0.0, -1.0);
template <typename T>
const vec_3 vec_3::BACK = vec_3 (0.0, 0.0, 1.0);

#define vec_4 vec<T, 4>
template <typename T>
class vec<T, 4>
{
 public:
   vec () = default;

   vec (const T &val)
   {
      x = y = z = w = val;
   }

   vec (const T &n1, const T &n2, const T &n3, const T &n4)
   {
      x = n1;
      y = n2;
      z = n3;
      w = n4;
   }

   inline auto operator[] (const std::size_t idx) -> T &
   {
      assert (("Index out of range\n" && idx < 4));
      return *(reinterpret_cast<T *> (this) + idx);
   }

   inline auto operator+= (vec_4 &v) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] += v[i];
      return *this;
   }

   inline auto operator-= (vec_4 &v) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] -= v[i];
      return *this;
   }

   inline auto operator*= (vec_4 &v) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] *= v[i];
      return *this;
   }

   inline auto operator/= (vec_4 &v) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] /= v[i];
      return *this;
   }

   inline auto operator+= (T scalar) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] += scalar;
      return *this;
   }

   inline auto operator-= (T scalar) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] -= scalar;
      return *this;
   }
   inline auto operator*= (T scalar) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] *= scalar;
      return *this;
   }

   inline auto operator/= (T scalar) -> vec_4 &
   {
      for (std::size_t i = 0; i < 4; i++)
         (*this)[i] /= scalar;
      return *this;
   }

   union
   {
      struct
      {
         T x;
         T y;
         T z;
         T w;
      };
      struct
      {
         T r;
         T g;
         T b;
         T a;
      };
      struct
      {
         T s;
         T t;
         T u;
      };
      struct
      {
         vec<T, 2> xy;
      };
      struct
      {
         vec<T, 2> uv;
      };
      struct
      {
         vec<T, 3> xyz;
      };
      struct
      {
         vec<T, 3> rgb;
      };
      struct
      {
         vec<T, 3> stu;
      };
   };
};

typedef vec<float, 2> vec2;
typedef vec<float, 3> vec3;
typedef vec<float, 4> vec4;

typedef vec<int, 2> vec2i;
typedef vec<int, 3> vec3i;
typedef vec<int, 4> vec4i;

typedef vec<double, 2> vec2d;
typedef vec<double, 3> vec3d;
typedef vec<double, 4> vec4d;

typedef vec<bool, 2> vec2b;
typedef vec<bool, 3> vec3b;
typedef vec<bool, 4> vec4b;

/* Vector Operations
 * -----------------
 * We can safely assume that the compiler loop-unrolls at
 * least for the specialized cases so we don't have to
 * re-write the operators for them for optimal performance
 */

/* Negate Vector
 */
template <typename T, std::size_t n>
inline auto operator- (vec_n v) -> vec_n
{
   vec_n result;
   for (std::size_t i = 0; i < n; i++) {
      result = -v[i];
   }
   return result;
}

/* Vector x Vector
 */
template <typename T, std::size_t n>
inline auto operator+ (vec_n &v1, vec_n &v2) -> vec_n
{
   return vec_n (v1) += v2;
}

template <typename T, std::size_t n>
inline auto operator- (vec_n v1, vec_n v2) -> vec_n
{
   return vec_n (v1) -= v2;
}

template <typename T, std::size_t n>
inline auto operator* (vec_n v1, vec_n v2) -> vec_n
{
   return vec_n (v1) *= v2; // Hadamard Product
}

template <typename T, std::size_t n>
inline auto operator/ (vec_n v1, vec_n v2) -> vec_n
{
   return vec_n (v1) /= v2;
}

/* Vector x Scalar
 */
template <typename T, std::size_t n>
inline auto operator+ (vec_n v, int scalar) -> vec_n
{
   return vec_n (v) += scalar;
}

template <typename T, std::size_t n>
inline auto operator- (vec_n v, int scalar) -> vec_n
{
   return vec_n (v) -= scalar;
}

template <typename T, std::size_t n>
inline auto operator* (vec_n v, int scalar) -> vec_n
{
   return vec_n (v) *= scalar;
}

template <typename T, std::size_t n>
inline auto operator/ (vec_n v, int scalar) -> vec_n
{
   return vec_n (v) /= scalar;
}

/* Other Functions for vectors
 */
template <typename T, std::size_t n>
inline auto len (vec_n v) -> T
{
   T result = {};
   for (std::size_t i = 0; i < n; i++) {
      result += v[i] * v[i];
   }
   return sqrt (result);
}

/* in many scenarios, only the relative length between 2 vectors is needed.
 * since sqrt() is expensive, we should use this function instead in these
 * cases
 */
template <typename T, std::size_t n>
inline auto len2 (vec_n v) -> T
{
   T result = {};
   for (std::size_t i = 0; i < n; i++) {
      result += v[i] * v[i];
   }
   return result;
}

template <typename T, std::size_t n>
inline auto dist (vec_n v1, vec_n v2) -> T
{
   return len (v1 - v2);
}

template <typename T, std::size_t n>
inline auto dist2 (vec_n v1, vec_n v2) -> T
{
   return len2 (v1 - v2);
}

template <typename T, std::size_t n>
inline auto dot (vec_n v1, vec_n v2) -> T
{
   T result = {};
   for (std::size_t i = 0; i < n; i++) {
      result += v1[i] * v2[i];
   }
   return result;
}

template <typename T, std::size_t n>
inline auto norm (vec_n v) -> vec_n
{
   vec_n result;
   T     length = len (v);
   for (std::size_t i = 0; i < n; i++) {
      result[i] = v[i] / length;
   }
   return result;
}

/* cross product is only relevant for 3-dimensional vectors
 */
template <typename T>
inline auto cross (vec_3 v1, vec_3 v2)
{
   vec_3 result;
   result.x = v1.y * v2.z - v1.z * v2.y;
   result.y = v1.z * v2.x - v1.x * v2.z;
   result.z = v1.x * v2.y - v1.y * v2.x;
   return result;
}

/* perpendicular is only defined for 2-D vector
 */
template <typename T>
inline auto perpendicular (vec_2 v)
{
   return vec_2 (-v.y, v.x);
}

#undef vec_n
#undef vec_2
#undef vec_3
#undef vec_4
