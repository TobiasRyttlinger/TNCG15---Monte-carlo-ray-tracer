#pragma once
#include <glm/glm.hpp>


struct Vertex {

	Vertex(): pos(glm::vec3(0.0, 0.0, 0.0)), w( 1.0){ } //Default constructor

	Vertex(double xIn, double yIn, double zIn, double wIn) //Conversion constructor
		:pos(glm::vec3(xIn, yIn, zIn)), w(wIn){}

	Vertex(glm::vec3 Vin, double wIn) //Conversion constructor
		:pos(glm::vec3(Vin.x, Vin.y, Vin.z)), w(wIn) {}


	glm::vec3 operator - (Vertex const& obj) {
		glm::vec3 res;

		res.x = pos.x - obj.pos.x;
		res.y = pos.y - obj.pos.y;
		res.z = pos.z - obj.pos.z;
		return res;
	}

	Vertex operator + (glm::vec3 obj) {
		this->pos.x += obj.x;
		this->pos.y += obj.y;
		this->pos.z += obj.z;
		return *this;
	}

	float Distance(Vertex &in) {

		return sqrt(pow(this->pos.x - in.pos.x, 2.0) + pow(this->pos.y - in.pos.y, 2.0) + pow(this->pos.z - in.pos.z, 2.0));
	}


	friend std::ostream& operator<<(std::ostream& os, Vertex& dt)
	{
		os << dt.pos.x << "," << dt.pos.y << "," << dt.pos.z << std::endl;
		return os;
	}

	glm::vec3 pos;
	double w;
};