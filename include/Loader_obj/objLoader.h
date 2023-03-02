#pragma once
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>

#include<Math/Vector.h>

struct objLoader {
	void read(std::string& s);
public:
	std::string ifile;

	std::vector<Vector3d> vPosition;
	std::vector<Vector2d> vTexture;
	std::vector<Vector3d> vNormal;

	std::vector<std::vector<int>> indPosition;
	std::vector<std::vector<int>> indTexture;
	std::vector<std::vector<int>> indNormal;
};