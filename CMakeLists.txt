cmake_minimum_required(VERSION 3.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

project(NanoRasterizer)

add_subdirectory("include")

# add the excutable
add_executable(NanoRasterizer "main.cpp" "rasterizer.cpp" "triangle.cpp" "screen.cpp")

target_link_libraries(NanoRasterizer PUBLIC Lodepng Algebra)
target_include_directories(NanoRasterizer PUBLIC
							"${PROJECT_SOURCE_DIR}/include"
							)
