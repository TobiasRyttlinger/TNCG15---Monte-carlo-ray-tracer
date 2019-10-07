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

	Ray(Vertex sP, Direction Din) {
		StartingPoint = sP;
		direction = Din;
		EndPoint = Vertex();
		color = ColorDbl(1.0, 1.0, 1.0);
	}

	Ray(Vertex sP, Vertex eP) {
		StartingPoint = sP;
		EndPoint = eP;
		color = ColorDbl(1.0,1.0,1.0);
		direction = EndPoint - StartingPoint;
	}


	Direction direction;
	Vertex StartingPoint;
	Vertex EndPoint;
	ColorDbl color;
	float t = INT32_MAX;
};