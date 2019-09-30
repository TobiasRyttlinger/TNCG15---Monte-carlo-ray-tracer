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
	//ColorDbl operator *(double &Res) {
	//	ColorDbl New(r * Res, g * Res, b * Res);
	//	return New;
	//}

	ColorDbl operator *(double Res) {
		ColorDbl New(r * Res, g * Res, b * Res);
		return New;
	}

	ColorDbl operator =(ColorDbl  Res) {
		ColorDbl New( Res.r,  Res.g, Res.b);
		return New;
	}


	double r, g, b;
};