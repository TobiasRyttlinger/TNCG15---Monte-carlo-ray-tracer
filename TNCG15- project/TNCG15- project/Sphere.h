#pragma once

#include <glm/glm.hpp>
#include "Ray.h"
#include "Vertex.h"
#include "Direction.h"
#include "ColorDbl.h"
#include <iostream>
struct Sphere {
	Sphere(){}

	Sphere(double rIn, glm::vec3 centerP) {
		rSq = rIn*rIn;
		center = centerP;
		material = Material(ColorDbl(1, 0, 0),glm::vec3(1, 0, 0),1);
	}

	bool rayIntersection(Ray& arg, float &t) {

		float a = 1;
		glm::vec3 o = arg.StartingPoint.pos;
		glm::vec3 l = glm::normalize(center-o);
		//std::cout << center.x << std::endl;
		float tca = glm::dot(l, arg.direction.Vec);
		
		if (tca < 0) return false;
		
		float d2 = 1 - tca * tca;
		
		if (d2 > sqrt(rSq)) return false;
		
		float thc = sqrt(sqrt(rSq) - d2);
		float D0, D1;
		D0 = tca - thc;
		D1 = tca + thc;

		if (D0 <= 0 && D1 <= 0) {
			return false;
		}
		else if (D1 < D0) {
			t = D1;
			this->Ip = Vertex(glm::vec3(o + D1 * arg.direction.Vec), 0);
			return true;
		}
		else if (D0 < D1) {
			t = D0;
			this->Ip = Vertex(glm::vec3(o + D0 * arg.direction.Vec), 0);
			return true;
		}
		else {
			t = D0;
			this->Ip = Vertex(glm::vec3(o + D0 * arg.direction.Vec), 0);
			return true;
		}

		return false;
	}

	glm::vec3  get_normal(glm::vec3 pIn) {
		return glm::normalize(pIn-center) ;
	}
	Material material;
	Vertex Ip;
	float t;

	double rSq;
	glm::vec3 center;
};