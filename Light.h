#pragma once
#define _USE_MATH_DEFINES
#include"Triangle.h"
#include"ColorDbl.h"
#include"Vertex.h"
#include"Direction.h"

struct Light {

	Light(){}

	Light(double p0, double p1, double p2, ColorDbl L) {
		p = Vertex(p0, p1, p2, 1);
		LightMat = Material(L, glm::vec3(1, 1, 1), 2);
		createLight(p,LightMat);
	}

	void createLight(Vertex& Vin, Material& Cin) {
		
		Vertices[0] = Vertex(4, 1, 0, 1)+Vin.pos;
		Vertices[1] = Vertex(6, 1, 0, 1) + Vin.pos;
		Vertices[2] = Vertex(4, -1, 0, 1) + Vin.pos;
		Vertices[3] = Vertex(6, -1, 0, 1) + Vin.pos;

		Triangles[0] = Triangle(Vertices[0], Vertices[1], Vertices[3], Cin);
		Triangles[1] = Triangle(Vertices[2], Vertices[0], Vertices[3], Cin);

		L0 = 1000;

	}

	glm::vec3 getRandomPointOnLight() {
		float random = glm::clamp((float)std::rand() / RAND_MAX, 0.01f, 0.99f);
		float randomU = random / ((std::rand() % 8) + 2.0);
		float randomV = random - randomU;
		float randomW = 1 - randomU - randomV;
		int r  = (double)rand() / RAND_MAX;
		return Triangles[r].getPointOnTriangle(randomU, randomV, randomW);
	}


	ColorDbl GetEmission() {

		return ColorDbl(1.0, 1.0, 1.0) * L0;

	}
	Material LightMat;
	std::vector<Triangle> triangle;
	Direction Ldirection;
	Vertex p;
	double L0;
	Vertex Vertices[4];
	Triangle Triangles[2];
};