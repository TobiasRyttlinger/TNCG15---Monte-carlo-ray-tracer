#pragma once

#include <glm/glm.hpp>
#include "Ray.h"
#include "Vertex.h"
#include "Direction.h"
#include "ColorDbl.h"
#include <iostream>
struct Sphere {
	Sphere() {}

	Sphere(double rIn, glm::vec3 centerP) {
		r = rIn;
		center = centerP;
		material = Material(ColorDbl(1, 0, 0), glm::vec3(1, 0, 0), 1);
	}

	glm::vec3 rayIntersection(Ray arg, float& t) {


		glm::vec3 rayDirection = glm::normalize(glm::vec3(arg.EndPoint - arg.StartingPoint));
		t = FLT_MAX;


		glm::vec3 L = center - arg.StartingPoint.pos;

		float tca = glm::dot(L, rayDirection);

		if (tca < FLT_EPSILON)
			return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

		float r2 = glm::pow(r, 2);

		float d2 = glm::dot(L, L) - glm::pow(tca, 2);

		if (d2 > r2)
			return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

		float thc = glm::sqrt(r2 - d2);

		float t0 = tca - thc;
		float t1 = tca + thc;

		if (t0 > t1)
			std::swap(t0, t1);

		if (t0 < FLT_EPSILON) {
			t0 = t1;
			if (t0 < FLT_EPSILON)
				return glm::vec3(0.0f, 0.0f, 0.0f);
		}

		t = t0;
	
		glm::vec3 hitPoint = arg.StartingPoint.pos + glm::vec3(rayDirection * t);


		//std::cout << hitPoint.x << "," << hitPoint.y << ", " << hitPoint.z << std::endl;
		get_normal(glm::vec3(hitPoint));


		return hitPoint;
	}

	Sphere operator = (Sphere In) {
		this->Ip = In.Ip;
		this->center = In.center;
		this->t = In.t;
		this->material = In.material;
		this->r = In.r;
		return *this;
	}

	glm::vec3  get_normal(glm::vec3 pIn) {
		return glm::normalize(pIn - center);
	}
	Material material;
	Vertex Ip;
	float t;

	double r;
	glm::vec3 center;
};