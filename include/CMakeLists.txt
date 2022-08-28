# add the library that runs
add_library(Lodepng lodepng.h)
# set_target_properties cxx or add_library(lib_name xxx.cpp)
set_target_properties(Lodepng PROPERTIES LINKER_LANGUAGE CXX)
# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(Lodepng
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_library(Algebra Vector.hpp Matrix.hpp)
set_target_properties(Algebra PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Algebra
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )