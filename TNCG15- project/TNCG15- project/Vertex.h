#pragma once
#include <glm/glm.hpp>


struct Vertex {

	Vertex(): pos(glm::vec4(0.0, 0.0, 0.0, 0.0)){ } //Default constructor

	Vertex(double xIn, double yIn, double zIn, double wIn) //Conversion constructor
		:pos(glm::vec4(xIn, yIn, zIn, wIn)){}


	glm::vec4 pos;
};