#pragma once
#define _USE_MATH_DEFINES
#include "Vertex.h"
#include "Direction.h"
#include "ColorDbl.h"
#include <glm/glm.hpp>
#include "math.h"
#include <cmath>
#include "Material.h"
#include <random>
struct Ray {


	Ray(){}

	Ray(glm::vec3 sP, Direction Din) {
		StartingPoint.pos = sP;
		direction = Din;
	}

	Ray(glm::vec3 sP, glm::vec3 Din) {
		StartingPoint.pos = sP;
		direction = Din;
	}


	Ray(Vertex sP, glm::vec3 eP) {
		StartingPoint = sP;
		EndPoint.pos = eP;
		direction = glm::normalize(EndPoint - StartingPoint);
	}

	Ray GetReflectedRay(Ray &r, glm::vec3& normal, glm::vec3& point) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1

		double rand1 = dis(gen);
		double rand2 = dis(gen);

		double inclanation_angle = (double)acos(sqrt(rand1));
		double azzimut_angle = (2.0 * (double)M_PI * rand2);

		glm::dvec3 X = glm::vec3(direction.Vec.x, direction.Vec.y, direction.Vec.z);
		glm::dvec3 Z = glm::normalize(glm::vec3(normal.x, normal.y, normal.z));
		glm::dvec3 Y = glm::normalize((glm::cross(X, Z)));
		glm::dvec3 _out = Z;

		_out = glm::normalize(glm::rotate(_out, inclanation_angle,Y));
		_out = glm::normalize(glm::rotate(_out, azzimut_angle, Z));

		Direction output = Direction(_out.x, _out.y, _out.z);

		return Ray(point, output);
	}

	Direction direction;
	Vertex StartingPoint;
	Vertex EndPoint;
	ColorDbl color;
};