#pragma once
#include <Triangle/triangle.h>

class Scene {
public:
	void add(Triangle* t) {
		object.emplace_back(t);
	}
	std::vector<Triangle*> object;
};