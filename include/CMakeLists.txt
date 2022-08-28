# add the library that runs
add_library(Lodepng lodepng.h lodepng.cpp)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(Lodepng
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )