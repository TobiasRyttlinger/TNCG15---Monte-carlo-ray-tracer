#pragma once
#define _USE_MATH_DEFINES
#include "Vertex.h"
#include "Direction.h"
#include "ColorDbl.h"
#include <glm/glm.hpp>
#include "math.h"
#include <cmath>
#include "Material.h"
struct Ray {
	Ray(){}
	Ray( Vertex sP, Vertex eP, Direction Din) {
		StartingPoint = sP;
		direction = Din;
	}

	Ray(Vertex sP, Direction Din) {
		StartingPoint = sP;
		direction = Din;
		EndPoint = Vertex(0, 0, 0, 0);
		color = ColorDbl(1.0, 1.0, 1.0);
	}

	Ray(Vertex sP, Vertex eP) {
		StartingPoint = sP;
		EndPoint = eP;
		color = ColorDbl(1.0,1.0,1.0);
		direction = (EndPoint - StartingPoint);
	}

	glm::vec3 CalcLambertian(Ray &r, Direction& normal, glm::vec3& point) {

		//float IclinationAngle = ((double)rand() / RAND_MAX)* (M_PI / 2);
		//float azimut = ((double)rand() / RAND_MAX) * (M_PI * 2);
	 //   
		//r.direction
			glm::vec3 brdf;
		return brdf;

	}

	Direction direction;
	Vertex StartingPoint;
	Vertex EndPoint;
	ColorDbl color;
	float t = INT32_MAX;
};