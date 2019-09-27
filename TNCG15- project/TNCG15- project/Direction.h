#pragma once
#include <glm/glm.hpp>
#include "Triangle.h"
#include "Vertex.h"
#include  <cmath>
struct Direction {

	Direction(): Vec(0.0){}

	Direction(double x_, double y_, double z_) {
		Vec = glm::normalize(glm::vec3(x_, y_, z_));
	}
	Direction(glm::vec3 inVec) {
		Vec = glm::normalize(inVec);
	}

	 glm::vec3 Cross(Direction& DirectkionIn) {

		 return glm::vec3(.0);
	}

	 double Scalar() {

		 return .0;
	 }
	 double CalcLength() {
		 return sqrt(pow(Vec.x, 2) + pow(Vec.y, 2) + pow(Vec.z, 2));
	 }

	 glm::vec3 Vec;


};