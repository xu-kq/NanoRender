#pragma once
#include <Math/Vector.h>

Vector3d fragment_shader_BlinnPhong(const Vector3d &, const Vector3d &);
Vector3d fragment_shader_Texture(const Vector3d &point, const Vector3d &texCol, const Vector3d &normal);