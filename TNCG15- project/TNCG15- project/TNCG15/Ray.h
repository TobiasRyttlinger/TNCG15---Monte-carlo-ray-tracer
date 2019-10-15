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
	Ray( Vertex sP, Vertex eP, Direction Din) {
		StartingPoint = sP;
		direction = Din;
		
	}

	Ray(Vertex sP, Direction Din) {
		StartingPoint = sP;
		direction = Din.Vec;
		EndPoint.pos = sP.pos + (float)Din.CalcLength();
		color = ColorDbl(1.0, 1.0, 1.0);
	}

	Ray(Vertex sP, Vertex eP) {
		StartingPoint = sP;
		EndPoint = eP;
		color = ColorDbl(1.0,1.0,1.0);
		direction = glm::normalize(EndPoint - StartingPoint);
	}

	Ray GetPerfectReflection(Ray& r, glm::vec3& normal, glm::vec3& point) {

		Direction R = Direction(glm::reflect(r.direction.Vec, normal));
		return Ray(Vertex(point,0), R);
	}

	Ray GetReflectedRay(Ray &r, Direction& normal, glm::vec3& point) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0,1);
	
		double rand1 = dis(gen);
		double rand2 = dis(gen);

		double inclanation = (double)acos(sqrt(rand1));
		double azzimut = (2.f * (double)M_PI * rand2);

		glm::dvec3 _in = glm::vec3(direction.Vec.x,direction.Vec.y,direction.Vec.z);
		glm::dvec3 _normal = glm::normalize(glm::vec3(normal.Vec.x, normal.Vec.y, normal.Vec.z));
		glm::dvec3 _tangent = glm::normalize((glm::cross(_in, _normal)));
		glm::dvec3 _out = _normal;



		_out = glm::normalize(glm::rotate(_out, inclanation, _tangent));
		_out = glm::normalize(glm::rotate(_out, azzimut, _normal));


		Direction output = Direction(_out.x, _out.y, _out.z);

		return Ray(Vertex(point,0), output);


	}

	




	Direction direction;
	Vertex StartingPoint;
	Vertex EndPoint;
	ColorDbl color;
	int t = INT32_MAX;
};