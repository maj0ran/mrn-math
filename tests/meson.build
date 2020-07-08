incdir = include_directories('../math')

vector_tests_exe = executable('vector_tests',
			      'vector_ops.cpp',
			      include_directories: incdir)

matrix_tests_exe = executable('matrix_tests',
			      'matrix_ops.cpp',
			      include_directories: incdir)

test('vector operations', vector_tests_exe)
test('matrix operations', matrix_tests_exe)
