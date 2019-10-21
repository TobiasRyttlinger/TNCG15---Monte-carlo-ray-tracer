
#include "Sphere.h"

struct IntersectionPointSphere {

	Sphere sphere;
	glm::vec3 P;
	Direction normal;
	bool Found = false;

};