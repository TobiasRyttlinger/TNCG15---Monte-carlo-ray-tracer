#pragma once
#include "Vertex.h"
#include "Direction.h"
#include "ColorDbl.h"
#include <glm/glm.hpp>

struct Ray {
	Ray(){}
	Ray( Vertex sP, Vertex eP, Direction Din) {
		StartingPoint = sP;

		direction = Din;
	}

	Ray(Vertex sP, Vertex eP) {
		StartingPoint = sP;
		EndPoint = eP;
		direction = glm::cross(glm::vec3(sP.pos.x, sP.pos.y, sP.pos.z), glm::vec3(eP.pos.x, eP.pos.y, eP.pos.z));
	}

	Direction direction;
	Vertex StartingPoint;
	Vertex EndPoint;
	ColorDbl color;
};