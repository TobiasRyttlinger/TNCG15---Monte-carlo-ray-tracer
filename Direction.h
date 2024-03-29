#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
#include  <cmath>
#include <iostream>
struct Direction {

	Direction(): Vec(0.0){}

	Direction(float x_, float y_, float z_) {
		Vec = glm::normalize(glm::vec3(x_, y_, z_));

	}
	Direction(glm::vec3 inVec) {
		Vec = glm::normalize(inVec);
		

	}

	 double CalcLength() {
		 return sqrt(pow(Vec.x, 2) + pow(Vec.y, 2) + pow(Vec.z, 2));
	 }

	 Direction operator + (glm::vec3 in) {
		 this->Vec.x += in.x;
		 this->Vec.y += in.y;
		 this->Vec.z += in.z;
		 return this->Vec;
	 }

	 Direction operator * (const float in) {
		 this->Vec.x *= in;
		 this->Vec.y *= in;
		 this->Vec.z *= in;
		 return *this;
	 }

	 friend std::ostream& operator<<(std::ostream& os, Direction dt)
	 {
		 os << dt.Vec.x << "," << dt.Vec.y << "," << dt.Vec.z << std::endl;
		 return os;
	 }
	 glm::vec3 Vec;
};