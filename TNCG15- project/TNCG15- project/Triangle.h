#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
struct Triangle {

	Triangle() : p1(Vertex()), p2(Vertex()), p3(Vertex()) {

		edge1 = p2.pos - p1.pos;
		edge2 = p3.pos - p1.pos;
	}
	~Triangle();

	Triangle(Vertex p1In, Vertex p2In, Vertex p3In) {
		edge1 = p2In.pos - p1In.pos;
		edge2 = p3In.pos - p1In.pos;
		Area = 0.5 * glm::length(cross(edge1, edge2));
	}



	Vertex p1,p2,p3;
	double Area;
	glm::vec3 edge1, edge2;
	
};