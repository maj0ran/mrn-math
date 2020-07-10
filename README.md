My little math-library for graphics-related work. Designed to be practicable when working with
GLSL. Mostly linear algebra- and geometry-related stuff. Matrices are column-major, i.e. in a
4x4 Matrix, the first 4 for elements are the first column.

May grow whenever I need new things.

##Implemented:

### Vectors

**Operators:**
[] (element-index)
* +=, + (with vector)
* +=, + (with scalar)
* -=, - (with vector)
* -=, - (with scaler)
* *=, * (with vector)
* *=, * (with scalar)
* /=, / (with vector)
* /=, / (with scalar)

**Other functions**
* length(v)
* length_squared(v)
* distance(v)
* distance_squared(v)
* dot(v1, v2)
* cross(v1, v2) // only for 3-D vector
* perpendicular(v) // only for 2-D vector

### Matrix
**Operators**
* [] (column-index)
* +=, + (with matrix)
* -=, - (with matrix)
* *=, * (with matrix)
* /=, / (with matrix)

**Other functions**
* generate translation-matrix
* generate scale-matrix
* generate rotation-matrix

