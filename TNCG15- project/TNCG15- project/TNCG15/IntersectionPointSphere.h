#pragma once
#include "Sphere.h"

struct IntersectionPointSphere {

	Sphere sphere;
	Vertex P;
	Direction normal;
	bool Found = false;

};