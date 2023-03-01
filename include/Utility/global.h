#pragma once
#include <Loader_png/lodepng.h>
#include <Loader_obj/objLoader.h>
#include <Triangle/triangle.h>
#include <Screen/screen.h>
#include <Rasterizer/rasterizer.h>

#define MY_PI 3.14159265358979323846

namespace Vertex_process {
Matrix4d get_model_matrix(const Vector3d&, const double, const double);

Matrix4d get_view_matrix(const Vector3d& view_pos, const Vector3d&, const Vector3d&);

Matrix4d get_projection_matrix(const double, const double, const double, const double);
}
