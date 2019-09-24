#pragma once
#include <glm/glm.hpp>


struct Vertex {

	Vertex(): pos(glm::vec3(0.0, 0.0, 0.0)){ } //Default constructor

	~Vertex(); // Destructor

	Vertex(double xIn, double yIn, double zIn) //Conversion constructor
		:pos(glm::vec3(xIn, yIn, zIn)){}


	glm::vec3 pos;
};