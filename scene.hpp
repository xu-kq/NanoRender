#pragma once
#include"Triangle.hpp"

class Scene {
public:
	void add(Triangle* t) {
		object.emplace_back(t);
	}
	std::vector<Triangle*> object;
};