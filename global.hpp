#pragma once
#include"lodepng.h"

#include"global.hpp"
#include"rasterizer.hpp"
#include"screen.hpp"
#include"triangle.hpp"
#include"objLoader.hpp"

#define MY_PI 3.14159265358979323846f

namespace Vertex_process {
Matrix4f get_model_matrix(const Vector3f&, const float, const float);

Matrix4f get_view_matrix(const Vector3f& view_pos, const Vector3f&, const Vector3f&);

Matrix4f get_projection_matrix(const float, const float, const float, const float);
}
