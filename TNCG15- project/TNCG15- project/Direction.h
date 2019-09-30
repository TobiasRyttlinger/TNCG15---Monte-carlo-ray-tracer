#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
#include  <cmath>
#include <iostream>
struct Direction {

	Direction(): Vec(0.0){}

	Direction(double x_, double y_, double z_) {
		Vec = glm::normalize(glm::vec3(x_, y_, z_));
	}
	Direction(glm::vec3 inVec) {
		Vec = glm::normalize(inVec);

	}

	 double CalcLength() {
		 return sqrt(pow(Vec.x, 2) + pow(Vec.y, 2) + pow(Vec.z, 2));
	 }

	 Direction operator + (glm::vec3 inVec) {
		 Direction newDir;
		 newDir = glm::vec3(Vec.x + inVec.x, Vec.y + inVec.y, Vec.z + inVec.z);
		 return newDir;
	 }

	 glm::vec3 Vec;


};