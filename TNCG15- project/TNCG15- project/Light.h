#pragma once
#include"Triangle.h"
#include"ColorDbl.h"
#include"Vertex.h"

struct Light {

	Light(){}

	Light(double p0, double p1, double p2, ColorDbl L) {
		Vertex v = Vertex(p0, p1, p2, 1);
		createLight(v, L);
	}

	void createLight(Vertex& Vin, ColorDbl Cin) {

		Vertices[0] = Vertex(glm::vec3(-1, 1, 0) + Vin.pos, 1) ;
		Vertices[1] = Vertex(glm::vec3(1, 1, 0) + Vin.pos, 1) ;
		Vertices[2] = Vertex(glm::vec3(-1, -1, 0) + Vin.pos, 1) ;
		Vertices[3] = Vertex(glm::vec3(1, -1, 0) + Vin.pos, 1) ;

		Triangles[0] = Triangle(Vertices[2], Vertices[3], Vertices[1], ColorDbl(0, 0, 0));
		Triangles[1] = Triangle(Vertices[1], Vertices[1], Vertices[2], ColorDbl());

		L0 = 1000 / 3.14;

	}

	ColorDbl GetEmission() {

		return ColorDbl(1.0, 1.0, 1.0) * L0;

	}


	Vertex p;
	double L0;
	Vertex Vertices[4];
	Triangle Triangles[2];
};