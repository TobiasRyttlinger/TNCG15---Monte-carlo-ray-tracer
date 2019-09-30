#pragma once
#include <glm/glm.hpp>


struct Vertex {

	Vertex(): pos(glm::vec4(0.0, 0.0, 0.0, 0.0)){ } //Default constructor

	Vertex(double xIn, double yIn, double zIn, double wIn) //Conversion constructor
		:pos(glm::vec4(xIn, yIn, zIn, wIn)){}

	glm::vec3 operator - (Vertex const& obj) {
		glm::vec3 res;

		res.x = pos.x - obj.pos.x;
		res.y = pos.y - obj.pos.y;
		res.z = pos.z - obj.pos.z;
		return res;
	}



	glm::vec4 pos;
};