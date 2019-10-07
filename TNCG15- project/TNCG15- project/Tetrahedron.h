#pragma once

#include "Vertex.h"
#include "ColorDbl.h"
#include "Triangle.h"
#include "Ray.h"
#include <glm/glm.hpp>
struct Tetrahedron {

	Tetrahedron() { } //Default shit

	Tetrahedron(double p0, double p1, double p2, ColorDbl L) {
		Vertex v = Vertex(p0, p1, p2, 1);
		CreateTeth(v, L);
	}

	void CreateTeth(Vertex &V, ColorDbl ColorIn) {

		Vertex v0 = Vertex(glm::vec3(9.0f, 0.0f, -3.0f) + V.pos, 1);
		Vertex v1 = Vertex(glm::vec3(10.0f, 0.0f, -3.0f) + V.pos,1);
		Vertex v2 = Vertex(glm::vec3(9.0f, 1.0f, -3.0f) + V.pos,1);
		Vertex v3 = Vertex(glm::vec3(9.0f, 0.0f, -2.0f) + V.pos,1);

		triangle[0] = Triangle(v0, v2, v1, ColorIn); // Not sure if normal is correct
		triangle[1] = Triangle(v0, v1, v3, ColorIn); // Not sure if normal is correct
		triangle[2] = Triangle(v0, v3, v2, ColorIn); // Normal ok
		triangle[3] = Triangle(v3, v1, v2, ColorIn); // Normal ok
	}
	
	Triangle triangle[4];
	Vertex Vert[4];
};