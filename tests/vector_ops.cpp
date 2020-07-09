#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../math/constants.hpp"
#include "../math/vector.hpp"

TEST_CASE ("Vector Construction: Single Value")
{
   vec2i       v_2 = vec2i (42);
   vec3i       v_3 = vec3i (42);
   vec4i       v_4 = vec4i (42);
   vec<int, 5> v_n = vec<int, 5> (42);

   CHECK (v_2.x == 42);
   CHECK (v_2.y == 42);

   CHECK (v_3.x == 42);
   CHECK (v_3.y == 42);
   CHECK (v_3.z == 42);

   CHECK (v_4.x == 42);
   CHECK (v_4.y == 42);
   CHECK (v_4.z == 42);
   CHECK (v_4.w == 42);

   CHECK (v_n[0] == 42);
   CHECK (v_n[1] == 42);
   CHECK (v_n[2] == 42);
   CHECK (v_n[3] == 42);
}

TEST_CASE ("Vector Construction: Multiple Values")
{
   vec2i       v_2 = vec2i (1, 2);
   vec3i       v_3 = vec3i (1, 2, 3);
   vec4i       v_4 = vec4i (1, 2, 3, 4);
   vec<int, 5> v_n = vec<int, 5> ({ 1, 2, 3, 4, 5 });

   CHECK (v_2.x == 1);
   CHECK (v_2.y == 2);

   CHECK (v_3.x == 1);
   CHECK (v_3.y == 2);
   CHECK (v_3.z == 3);

   CHECK (v_4.x == 1);
   CHECK (v_4.y == 2);
   CHECK (v_4.z == 3);
   CHECK (v_4.w == 4);

   CHECK (v_n[0] == 1);
   CHECK (v_n[1] == 2);
   CHECK (v_n[2] == 3);
   CHECK (v_n[3] == 4);
   CHECK (v_n[4] == 5);
}

TEST_CASE ("Vector Index Operator")
{
   vec2b v_2 = vec2b (1, 0);
   vec3b v_3 = vec3b (1, 0, 1);
   vec4b v_4 = vec4b (1, 0, 1, 0);

   CHECK (v_2[0] == 1);
   CHECK (v_2[1] == 0);

   CHECK (v_3[0] == 1);
   CHECK (v_3[1] == 0);
   CHECK (v_3[2] == 1);

   CHECK (v_4[0] == 1);
   CHECK (v_4[1] == 0);
   CHECK (v_4[2] == 1);
   CHECK (v_4[3] == 0);
}

TEST_CASE ("Vector Index Operator Custom Struct")
{
   struct intchar
   {
      int  a;
      char b;
   };

   struct intchar x1 = { 1024, 'A' };
   struct intchar x2 = { 50000, 'B' };
   struct intchar x3 = { 12345, 'C' };
   struct intchar x4 = { 1000000, 'D' };

   vec<intchar, 4> v = { x1, x2, x3, x4 };

   CHECK (v[2].a == 12345);
   CHECK (v[1].b == 'B');
}

TEST_CASE ("Partial vector access")
{
   SUBCASE ("3-dimensional vector")
   {
      vec3 v1 = vec3 (1, 2, 3);

      SUBCASE ("xy-access")
      {
         vec2 v2 = vec2 (v1.xy);

         CHECK (v2.x == 1);
         CHECK (v2.y == 2);
      }

      SUBCASE ("uv-access")
      {
         vec2 v2 = vec2 (v1.xy);

         CHECK (v2.u == 1);
         CHECK (v2.v == 2);
      }
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v1 = vec4 (1, 2, 3, 4);

      SUBCASE ("xy-access")
      {
         vec2 v2 = vec2 (v1.xy);

         CHECK (v2.x == 1);
         CHECK (v2.y == 2);
      }

      SUBCASE ("xyz-access")
      {
         vec3 v2 = vec3 (v1.xyz);

         CHECK (v2.x == 1);
         CHECK (v2.y == 2);
         CHECK (v2.z == 3);
      }

      SUBCASE ("rgb-access")
      {
         vec3 v2 = vec3 (v1.rgb);

         CHECK (v2.r == 1);
         CHECK (v2.g == 2);
         CHECK (v2.b == 3);
      }

      SUBCASE ("stu-access")
      {
         vec3 v2 = vec3 (v1.stu);

         CHECK (v2.s == 1);
         CHECK (v2.t == 2);
         CHECK (v2.u == 3);
      }
   }
}

TEST_CASE ("Basic arithmetic instructions with compound-assignment")
{
   SUBCASE ("2-dimensional vector")
   {
      vec2 v1 = { 1, 2 };
      vec2 v2 = { -5, 10 };

      SUBCASE ("Addition")
      {
         v1 += v2;

         CHECK (v1.x == -4);
         CHECK (v1.y == 12);
      }

      SUBCASE ("Subtraction")
      {
         v1 -= v2;
         CHECK (v1.x == 6);
         CHECK (v1.y == -8);
      }

      SUBCASE ("Multiplication")
      {
         v1 *= v2;
         CHECK (v1.x == -5);
         CHECK (v1.y == 20);
      }

      SUBCASE ("Division")
      {
         v1 /= v2;
         CHECK (v1.x == doctest::Approx (-0.2));
         CHECK (v1.y == doctest::Approx (0.2));
      }
   }

   SUBCASE ("3-dimensional vector")
   {
      vec3 v1 = { 1, 2, 3 };
      vec3 v2 = { -5, 10, 3 };

      SUBCASE ("Addition")
      {
         v1 += v2;
         CHECK (v1.x == -4);
         CHECK (v1.y == 12);
         CHECK (v1.z == 6);
      }

      SUBCASE ("Subtraction")
      {
         v1 -= v2;
         CHECK (v1.x == 6);
         CHECK (v1.y == -8);
         CHECK (v1.z == 0);
      }

      SUBCASE ("Multiplication")
      {
         v1 *= v2;
         CHECK (v1.x == -5);
         CHECK (v1.y == 20);
         CHECK (v1.z == 9);
      }

      SUBCASE ("Division")
      {
         v1 /= v2;
         CHECK (v1.x == doctest::Approx (-0.2));
         CHECK (v1.y == doctest::Approx (0.2));
         CHECK (v1.z == doctest::Approx (1.0));
      }
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v1 = { 1, 2, 3, 4 };
      vec4 v2 = { -5, 10, 3, 1000 };

      SUBCASE ("Addition")
      {
         v1 += v2;
         CHECK (v1.x == -4);
         CHECK (v1.y == 12);
         CHECK (v1.z == 6);
         CHECK (v1.w == 1004);
      }

      SUBCASE ("Subtraction")
      {
         v1 -= v2;
         CHECK (v1.x == 6);
         CHECK (v1.y == -8);
         CHECK (v1.z == 0);
         CHECK (v1.w == -996);
      }

      SUBCASE ("Multiplication")
      {
         v1 *= v2;
         CHECK (v1.x == -5);
         CHECK (v1.y == 20);
         CHECK (v1.z == 9);
         CHECK (v1.w == 4000);
      }

      SUBCASE ("Division")
      {
         v1 /= v2;
         CHECK (v1.x == doctest::Approx (-0.2));
         CHECK (v1.y == doctest::Approx (0.2));
         CHECK (v1.z == doctest::Approx (1.0));
         CHECK (v1.w == doctest::Approx (0.004));
      }
   }

   SUBCASE ("N-dimensional vector")
   {
      vec<float, 6> v1 = { 1, 2, 3, 4, 5, 6 };
      vec<float, 6> v2 = { -5, 10, 3, 1000, -1000, 0 };

      SUBCASE ("Addition")
      {
         v1 += v2;

         CHECK (v1[0] == -4);
         CHECK (v1[1] == 12);
         CHECK (v1[2] == 6);
         CHECK (v1[3] == 1004);
         CHECK (v1[4] == -995);
         CHECK (v1[5] == 6);
      }

      SUBCASE ("Subtraction")
      {
         v1 -= v2;

         CHECK (v1[0] == 6);
         CHECK (v1[1] == -8);
         CHECK (v1[2] == 0);
         CHECK (v1[3] == -996);
         CHECK (v1[4] == 1005);
         CHECK (v1[5] == 6);
      }

      SUBCASE ("Multiplication")
      {
         v1 *= v2;

         CHECK (v1[0] == -5);
         CHECK (v1[1] == 20);
         CHECK (v1[2] == 9);
         CHECK (v1[3] == 4000);
         CHECK (v1[4] == -5000);
         CHECK (v1[5] == 0);
      }

      SUBCASE ("Division")
      {
         v1 /= v2;

         CHECK (v1[0] == doctest::Approx (-0.2));
         CHECK (v1[1] == doctest::Approx (0.2));
         CHECK (v1[2] == doctest::Approx (1.0));
         CHECK (v1[3] == doctest::Approx (0.004));
         CHECK (v1[4] == doctest::Approx (-0.005));
         CHECK (std::isinf (v1[5]));
      }
   }
}
TEST_CASE ("Basic arithmetic instructions")
{
   SUBCASE ("2-dimensional vector")
   {
      vec2 v1 = { 1, 2 };
      vec2 v2 = { -5, 10 };
      vec2 result;

      SUBCASE ("Addition")
      {
         result = v1 + v2;

         CHECK (result.x == -4);
         CHECK (result.y == 12);
      }
      SUBCASE ("Substraction")
      {
         result = v1 - v2;

         CHECK (result.x == 6);
         CHECK (result.y == -8);
      }
      SUBCASE ("Multiplication")
      {
         result = v1 * v2;

         CHECK (result.x == -5);
         CHECK (result.y == 20);
      }
      SUBCASE ("Division")
      {
         result = v1 / v2;

         CHECK (result.x == doctest::Approx (-0.2));
         CHECK (result.y == doctest::Approx (0.2));
      }
   }

   SUBCASE ("3-dimensional vector")
   {
      vec3 v1 = { 1, 2, 3 };
      vec3 v2 = { -5, 10, 3 };
      vec3 result;

      SUBCASE ("Addition")
      {
         result = v1 + v2;

         CHECK (result.x == -4);
         CHECK (result.y == 12);
         CHECK (result.z == 6);
      }
      SUBCASE ("Substraction")
      {
         result = v1 - v2;

         CHECK (result.x == 6);
         CHECK (result.y == -8);
         CHECK (result.z == 0);
      }
      SUBCASE ("Multiplication")
      {
         result = v1 * v2;

         CHECK (result.x == -5);
         CHECK (result.y == 20);
         CHECK (result.z == 9);
      }
      SUBCASE ("Divison")
      {
         result = v1 / v2;

         CHECK (result.x == doctest::Approx (-0.2));
         CHECK (result.y == doctest::Approx (0.2));
         CHECK (result.z == doctest::Approx (1.0));
      }
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v1 = { 1, 2, 3, 4 };
      vec4 v2 = { -5, 10, 3, 1000 };
      vec4 result;

      SUBCASE ("Addition")
      {
         result = v1 + v2;

         CHECK (result.x == -4);
         CHECK (result.y == 12);
         CHECK (result.z == 6);
         CHECK (result.w == 1004);
      }
      SUBCASE ("Subtraction")
      {
         result = v1 - v2;

         CHECK (result.x == 6);
         CHECK (result.y == -8);
         CHECK (result.z == 0);
         CHECK (result.w == -996);
      }

      SUBCASE ("Multiplication")
      {
         result = v1 * v2;

         CHECK (result.x == -5);
         CHECK (result.y == 20);
         CHECK (result.z == 9);
         CHECK (result.w == 4000);
      }

      SUBCASE ("Division")
      {
         result = v1 / v2;

         CHECK (result.x == doctest::Approx (-0.2));
         CHECK (result.y == doctest::Approx (0.2));
         CHECK (result.z == doctest::Approx (1.0));
         CHECK (result.w == doctest::Approx (0.004));
      }
   }

   SUBCASE ("N-dimensional vector")
   {
      vec<float, 6> v1 = { 1, 2, 3, 4, 5, 6 };
      vec<float, 6> v2 = { -5, 10, 3, 1000, -1000, 0 };
      vec<float, 6> result;

      SUBCASE ("Addition")
      {
         result = v1 + v2;

         CHECK (result[0] == -4);
         CHECK (result[1] == 12);
         CHECK (result[2] == 6);
         CHECK (result[3] == 1004);
         CHECK (result[4] == -995);
         CHECK (result[5] == 6);
      }

      SUBCASE ("Subtraction")
      {
         result = v1 - v2;

         CHECK (result[0] == 6);
         CHECK (result[1] == -8);
         CHECK (result[2] == 0);
         CHECK (result[3] == -996);
         CHECK (result[4] == 1005);
         CHECK (result[5] == 6);
      }

      SUBCASE ("Multiplication")
      {
         result = v1 * v2;

         CHECK (result[0] == -5);
         CHECK (result[1] == 20);
         CHECK (result[2] == 9);
         CHECK (result[3] == 4000);
         CHECK (result[4] == -5000);
         CHECK (result[5] == 0);
      }

      SUBCASE ("Division")
      {
         result = v1 / v2;

         CHECK (result[0] == doctest::Approx (-0.2));
         CHECK (result[1] == doctest::Approx (0.2));
         CHECK (result[2] == doctest::Approx (1.0));
         CHECK (result[3] == doctest::Approx (0.004));
         CHECK (result[4] == doctest::Approx (-0.005));
         CHECK (std::isinf (result[5]));
      }
   }
}

TEST_CASE ("Vector length")
{
   SUBCASE ("2-dimensional vector")
   {
      vec2 v = vec2 (3, 4);
      CHECK (len (v) == doctest::Approx (5.0));
   }

   SUBCASE ("3-dimensional vector")
   {
      vec3 v = vec3 (3, 4, 5);
      CHECK (len (v) == doctest::Approx (7.071));
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v = vec4 (3, 4, 5, 6);
      CHECK (len (v) == doctest::Approx (9.2736));
   }

   SUBCASE ("N-dimensional vector")
   {
      vec<float, 5> v = vec<float, 5> ({ 3, 4, 5, 6, 7 });
      CHECK (len (v) == doctest::Approx (11.6189));
   }
}

TEST_CASE ("Vector distance")
{
   SUBCASE ("2-dimensional vector")
   {
      vec2 v1 = vec2 (3, 4);
      vec2 v2 = vec2 (9, 12);
      CHECK (dist (v1, v2) == doctest::Approx (10.0));
   }

   SUBCASE ("3-dimensional vector")
   {
      vec3 v1 = vec3 (3, 4, 5);
      vec3 v2 = vec3 (-3, 6, 10);
      CHECK (dist (v1, v2) == doctest::Approx (8.0622));
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v1 = vec4 (3, 4, 5, 6);
      vec4 v2 = vec4 (5, 0, 1, -10);
      CHECK (dist (v1, v2) == doctest::Approx (17.088));
   }

   SUBCASE ("N-dimensional vector")
   {
      vec<float, 5> v1 = vec<float, 5> ({ 3, 4, 5, 6, 7 });
      vec<float, 5> v2 = vec<float, 5> ({ 0, 1, -5, 3, 8 });
      CHECK (dist (v1, v2) == doctest::Approx (11.3137));
   }
}

TEST_CASE ("Vector dot-product")
{
   SUBCASE ("2-dimensional vector")
   {
      vec2 v1 = vec2 (3, 4);
      vec2 v2 = vec2 (9, 12);
      CHECK (dot (v1, v2) == 75.0);
   }

   SUBCASE ("3-dimensional vector")
   {
      vec3 v1 = vec3 (3, 4, 5);
      vec3 v2 = vec3 (-3, 6, 10);
      CHECK (dot (v1, v2) == 65.0);
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v1 = vec4 (3, 4, 5, 6);
      vec4 v2 = vec4 (5, 0, 1, -10);
      CHECK (dot (v1, v2) == -40.0);
   }

   SUBCASE ("N-dimensional vector")
   {
      vec<float, 5> v1 = vec<float, 5> ({ 3, 4, 5, 6, 7 });
      vec<float, 5> v2 = vec<float, 5> ({ 0, 1, -5, 3, 8 });
      CHECK (dot (v1, v2) == 53.0);
   }
}

TEST_CASE ("Vector cross-product")
{
   SUBCASE ("3-dimensional vector")
   {
      vec3 v1     = vec3 (3, 4, 5);
      vec3 v2     = vec3 (-3, 6, 10);
      vec3 result = cross (v1, v2);

      CHECK (result.x == 10);
      CHECK (result.y == -45);
      CHECK (result.z == 30);
   }
}

TEST_CASE ("Vector normalization")
{
   SUBCASE ("2-dimensional vector")
   {
      vec2 v = vec2 (-34.2, 15.8);
      CHECK (len (norm (v)) == doctest::Approx (1.0));
   }

   SUBCASE ("3-dimensional vector")
   {
      vec3 v = vec3 (-34.2, 15.8, 13.37);
      CHECK (len (norm (v)) == doctest::Approx (1.0));
   }

   SUBCASE ("4-dimensional vector")
   {
      vec4 v = vec4 (-34.2, 15.8, 3.1, 3.37);
      CHECK (len (norm (v)) == doctest::Approx (1.0));
   }

   SUBCASE ("N-dimensional vector")
   {
      vec<float, 6> v = vec<float, 6> ({ -34.2, 15.8, 23.5, 42.1337, -5.0, 0.0 });
      CHECK (len (norm (v)) == doctest::Approx (1.0));
   }
}

TEST_CASE ("Vector perpendicular")
{
   vec2 v1 = vec2 (13, 37);
   vec2 v2 = perpendicular (v1);

   CHECK (std::acos (dot (v1, v2)) == pi_2);
}
