#pragma once
#include <glm/glm.hpp>

struct ColorDbl {

	ColorDbl(): r(0), g(0), b(0){}

	ColorDbl(double inR, double inG, double inB) {
		r = inR;
		g = inG;
		b = inB;
	}

	ColorDbl(glm::vec3 color): r(color.r), g(color.g), b(color.b){}

	

	//Implement overladed operators

	double r, g, b;
};