#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
#include <iostream>
#include "Direction.h"
struct Triangle {

	Triangle(Vertex p1In, Vertex p2In, Vertex p3In, ColorDbl colorIn) {
		edge1 = p2In.pos - p1In.pos;
		edge2 = p3In.pos - p1In.pos;
		color = colorIn;
		Area = 0.5 * glm::length(cross(edge1, edge2));
		std::cout << Area << std::endl;
	}
	
	Direction NormalizeTriangle() {
		Direction one = ;
		Direction two = ;

	}



	Vertex p1,p2,p3;
	ColorDbl color;
	double Area;
	glm::vec3 edge1, edge2;
	
};