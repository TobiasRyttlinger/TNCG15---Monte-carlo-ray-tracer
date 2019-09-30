#pragma once
#include "Triangle.h"
#include <glm/glm.hpp>
struct Mesh {

	Mesh() :Mesh(4){}

	Mesh(int NumberOfTrianglesIn) : NumberOfTriangles(NumberOfTrianglesIn) {
		NumberOfTriangles = NumberOfTrianglesIn;
		
	}

	int NumberOfTriangles;
};