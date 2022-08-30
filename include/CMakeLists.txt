# add the library that runs
add_library(Lodepng lodepng.cpp)
add_library(Algebra Vector.cpp Matrix.cpp)
# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(Lodepng
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
target_include_directories(Algebra
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )