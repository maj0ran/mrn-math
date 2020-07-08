#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../math/constants.hpp"
#include "../math/matrix.hpp"

TEST_CASE ("Matrix construction")
{
   SUBCASE ("Default-Constructor")
   {
      mat4 m = mat4 ();

      CHECK (m[0][0] == 1.0f);
      CHECK (m[0][1] == 0.0f);
      CHECK (m[0][2] == 0.0f);
      CHECK (m[0][3] == 0.0f);

      CHECK (m[1][0] == 0.0f);
      CHECK (m[1][1] == 1.0f);
      CHECK (m[1][2] == 0.0f);
      CHECK (m[1][3] == 0.0f);

      CHECK (m[2][0] == 0.0f);
      CHECK (m[2][1] == 0.0f);
      CHECK (m[2][2] == 1.0f);
      CHECK (m[2][3] == 0.0f);

      CHECK (m[3][0] == 0.0f);
      CHECK (m[3][1] == 0.0f);
      CHECK (m[3][2] == 0.0f);
      CHECK (m[3][3] == 1.0f);
   }

   SUBCASE ("Assignment-Constructor")
   {
      mat4 m = mat4 ({ { 3.0, 2.0, -2.0, 0.5 },
                       { 0.0, 1.0, 5.0, 1.0 },
                       { 5.5, 13.0, 37.0, 23.0 },
                       { 1.1, 1.2, 1.3, -1.4 } });

      CHECK (m[0][0] == 3.0f);
      CHECK (m[0][1] == 2.0f);
      CHECK (m[0][2] == -2.0f);
      CHECK (m[0][3] == 0.5f);

      CHECK (m[1][0] == 0.0f);
      CHECK (m[1][1] == 1.0f);
      CHECK (m[1][2] == 5.0f);
      CHECK (m[1][3] == 1.0f);

      CHECK (m[2][0] == 5.5f);
      CHECK (m[2][1] == 13.0f);
      CHECK (m[2][2] == 37.0f);
      CHECK (m[2][3] == 23.0f);

      CHECK (m[3][0] == 1.1f);
      CHECK (m[3][1] == 1.2f);
      CHECK (m[3][2] == 1.3f);
      CHECK (m[3][3] == -1.4f);
   }
}

TEST_CASE ("Matrix + Matrix")
{
   mat4 m1 = mat4 ({ { 3.0, 2.0, -2.0, 0.5 },
                     { 0.0, 1.0, 5.0, 1.0 },
                     { 5.5, 13.0, 37.0, 23.0 },
                     { 1.1, 1.2, 1.3, -1.4 } });

   mat4 m2 = mat4 ({ { 1.5, -3.0, 0.0, 5.0 },
                     { 42, -42, 23, 5 },
                     { 1.0, 2.0, 3.0, 4.0 },
                     { 0.0, -2.0, 1.0, 13.37 } });

   mat4 result = m1 + m2;

   CHECK (result[0][0] == doctest::Approx (4.5f));
   CHECK (result[0][1] == doctest::Approx (-1.0f));
   CHECK (result[0][2] == doctest::Approx (-2.0f));
   CHECK (result[0][3] == doctest::Approx (5.5f));

   CHECK (result[1][0] == doctest::Approx (42.0f));
   CHECK (result[1][1] == doctest::Approx (-41.0f));
   CHECK (result[1][2] == doctest::Approx (28.0f));
   CHECK (result[1][3] == doctest::Approx (6.0f));

   CHECK (result[2][0] == doctest::Approx (6.5f));
   CHECK (result[2][1] == doctest::Approx (15.0f));
   CHECK (result[2][2] == doctest::Approx (40.0f));
   CHECK (result[2][3] == doctest::Approx (27.0f));

   CHECK (result[3][0] == doctest::Approx (1.1f));
   CHECK (result[3][1] == doctest::Approx (-0.8f));
   CHECK (result[3][2] == doctest::Approx (2.3f));
   CHECK (result[3][3] == doctest::Approx (11.97f));
}

TEST_CASE ("Matrix - Matrix")
{
   mat4 m1 = mat4 ({ { 3.0, 2.0, -2.0, 0.5 },
                     { 0.0, 1.0, 5.0, 1.0 },
                     { 5.5, 13.0, 37.0, 23.0 },
                     { 1.1, 1.2, 1.3, -1.4 } });

   mat4 m2 = mat4 ({ { 1.5, -3.0, 0.0, 5.0 },
                     { 42, -42, 23, 5 },
                     { 1.0, 2.0, 3.0, 4.0 },
                     { 0.0, -2.0, 1.0, 13.37 } });

   mat4 result = m1 - m2;

   CHECK (result[0][0] == doctest::Approx (1.5f));
   CHECK (result[0][1] == doctest::Approx (5.0f));
   CHECK (result[0][2] == doctest::Approx (-2.0f));
   CHECK (result[0][3] == doctest::Approx (-4.5f));

   CHECK (result[1][0] == doctest::Approx (-42.0f));
   CHECK (result[1][1] == doctest::Approx (43.0f));
   CHECK (result[1][2] == doctest::Approx (-18.0f));
   CHECK (result[1][3] == doctest::Approx (-4.0f));

   CHECK (result[2][0] == doctest::Approx (4.5f));
   CHECK (result[2][1] == doctest::Approx (11.0f));
   CHECK (result[2][2] == doctest::Approx (34.0f));
   CHECK (result[2][3] == doctest::Approx (19.0f));

   CHECK (result[3][0] == doctest::Approx (1.1f));
   CHECK (result[3][1] == doctest::Approx (3.2f));
   CHECK (result[3][2] == doctest::Approx (0.3f));
   CHECK (result[3][3] == doctest::Approx (-14.77f));
}

TEST_CASE ("Matrix * Vector")
{
   vec4 v = vec4 (-1.0, 2.0, 4.5, 1.0);

   mat4 m = mat4 ({ { 3.0, 2.0, -2.0, 0.5 },
                    { 0.0, 1.0, 5.0, 1.0 },
                    { 5.5, 13.0, 37.0, 23.0 },
                    { 1.1, 1.2, 1.3, -1.4 } });

   vec4 result = m * v;

   CHECK (result.x == doctest::Approx (22.85));
   CHECK (result.y == doctest::Approx (59.7));
   CHECK (result.z == doctest::Approx (179.8));
   CHECK (result.w == doctest::Approx (103.6));
}

TEST_CASE ("Matrix * Matrix")
{
   mat4 m1 = mat4 ({ { 3.0, 2.0, -2.0, 0.5 },
                     { 0.0, 1.0, 5.0, 1.0 },
                     { 5.5, 13.0, 37.0, 23.0 },
                     { 1.1, 1.2, 1.3, -1.4 } });

   mat4 m2 = mat4 ({ { 1.5, -3.0, 0.0, 5.0 },
                     { 42, -42, 23, 5 },
                     { 1.0, 2.0, 3.0, 4.0 },
                     { 0.0, -2.0, 1.0, 13.37 } });

   mat4 result = m1 * m2;

   CHECK (result[0][0] == doctest::Approx (10.f));
   CHECK (result[0][1] == doctest::Approx (6.f));
   CHECK (result[0][2] == doctest::Approx (-11.5f));
   CHECK (result[0][3] == doctest::Approx (-9.25f));

   CHECK (result[1][0] == doctest::Approx (258.f));
   CHECK (result[1][1] == doctest::Approx (347.f));
   CHECK (result[1][2] == doctest::Approx (563.5f));
   CHECK (result[1][3] == doctest::Approx (501.f));

   CHECK (result[2][0] == doctest::Approx (23.9f));
   CHECK (result[2][1] == doctest::Approx (47.8f));
   CHECK (result[2][2] == doctest::Approx (124.2f));
   CHECK (result[2][3] == doctest::Approx (65.9f));

   CHECK (result[3][0] == doctest::Approx (20.207f));
   CHECK (result[3][1] == doctest::Approx (27.044f));
   CHECK (result[3][2] == doctest::Approx (44.381f));
   CHECK (result[3][3] == doctest::Approx (2.282f));
}

TEST_CASE ("Translation-Matrix")
{
   vec4 v  = vec4 (-1.0, 2.0, 4.5, 1.0);
   mat4 tr = mat4::translate (3.0, -4.5, 10.0);

   vec4 result = tr * v;

   CHECK (result.x == 2.0f);
   CHECK (result.y == -2.5f);
   CHECK (result.z == 14.5f);
   CHECK (result.w == 1.0f);
}

TEST_CASE ("Scale-Matrix")
{
   vec4 v     = vec4 (-1.0, 2.0, 4.5, 1.0);
   mat4 scale = mat4::scale (2.0, -2.0, 1.5);

   vec4 result = scale * v;

   CHECK (result.x == -2.0f);
   CHECK (result.y == -4.0f);
   CHECK (result.z == 6.75f);
   CHECK (result.w == 1.0f);
}

TEST_CASE ("Rotation-Matrix")
{
   vec4 v = vec4 (-1.0, 2.0, 4.5, 1.0);
   vec4 result;

   // Make a couple of fancy rotations

   SUBCASE ("Around Z-Axis, 45 degree")
   {
      mat4 rot = mat4::rotate (vec3::BACK, pi_4);
      result   = rot * v;

      CHECK (result.x == doctest::Approx (-2.12132f));
      CHECK (result.y == doctest::Approx (0.70711f));
      CHECK (result.z == doctest::Approx (4.5f));
      CHECK (result.w == 1.0f);
   }

   SUBCASE ("Around Y-Axis, 45 degree")
   {
      mat4 rot = mat4::rotate (vec3::UP, pi_4);
      result   = rot * v;

      CHECK (result.x == doctest::Approx (2.47487f));
      CHECK (result.y == doctest::Approx (2.0f));
      CHECK (result.z == doctest::Approx (3.88909f));
      CHECK (result.w == 1.0f);
   }

   SUBCASE ("Around X-Axis, 45 degree")
   {
      mat4 rot = mat4::rotate (vec3::RIGHT, pi_4);
      result   = rot * v;

      CHECK (result.x == doctest::Approx (-1.0f));
      CHECK (result.y == doctest::Approx (-1.76777f));
      CHECK (result.z == doctest::Approx (4.59619f));
      CHECK (result.w == 1.0f);
   }

   SUBCASE ("Around XY-Axis, 30 degree")
   {
      mat4 rot = mat4::rotate (vec3 (1, 1, 0), deg1 * 30);
      result   = rot * v;

      CHECK (result.x == doctest::Approx (1.51795f));
      CHECK (result.y == doctest::Approx (-0.383975f));
      CHECK (result.z == doctest::Approx (5.3971125f));
      CHECK (result.w == 1.0f);
   }

   SUBCASE ("Around YZ-Axis, -30 degree")
   {
      mat4 rot = mat4::rotate (vec3 (0, 1, 1), deg1 * -30);
      result   = rot * v;

      CHECK (result.x == doctest::Approx (-2.116025f));
      CHECK (result.y == doctest::Approx (3.1028875f));
      CHECK (result.z == doctest::Approx (4.26795f));
      CHECK (result.w == 1.0f);
   }
   SUBCASE ("Around XYZ-Axis, 67.35 degree")
   {
      mat4 rot = mat4::rotate (vec3 (3.2, 0.7, -1.8), deg1 * -67.35);
      result   = rot * v;

      CHECK (result.x == doctest::Approx (-26.0945085f));
      CHECK (result.y == doctest::Approx (8.1371665f));
      CHECK (result.z == doctest::Approx (6.138046f));
      CHECK (result.w == 1.0f);
   }
}
