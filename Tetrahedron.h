#pragma once

#include "Vertex.h"
#include "ColorDbl.h"
#include "Triangle.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include <cmath>
#include "math.h"
struct Tetrahedron {

	Tetrahedron() { } //Default shit

	Tetrahedron(double p0, double p1, double p2, ColorDbl L) {
		Vertex v = Vertex(p0, p1, p2, 1);
		CreateTeth(v, L);
	}

	void CreateTeth(Vertex &V, ColorDbl ColorIn) {

		Vertex v0 = Vertex(glm::vec3(0.0f, 0.0f, 0.0f) + V.pos, 1);
		Vertex v1 = Vertex(glm::vec3(2.0f, -2.0f, 0.0f) + V.pos,1);
		Vertex v2 = Vertex(glm::vec3(2.0f, 2.0f, 0.0f) + V.pos,1);
		Vertex v3 = Vertex(glm::vec3(1.0f, 0.0f, -4.0f) + V.pos,1);

		triangle[0] = Triangle(v0, v3, v1, mat); // Red
		triangle[1] = Triangle(v1, v3, v2, mat); // Green
		triangle[2] = Triangle(v0, v2, v3, mat); //Blue
		triangle[3] = Triangle(v1, v2, v0, mat); // Yellow
	}
	
	Material mat = Material(ColorDbl(1.0, 0,0), glm::vec3(1.0, 0, 0),3);
	Material mat1 = Material(ColorDbl(0, 1.0, 0), glm::vec3(1.0, .50, 1.0),3);
	Material mat2 = Material(ColorDbl(0, 0, 1.0), glm::vec3(1.0, .50, 1.0), 3);
	Material mat3 = Material(ColorDbl(0, 1.0, 1.0), glm::vec3(1.0, .50, 1.0),3);
	Triangle triangle[4];
	Vertex Vert[4];
};