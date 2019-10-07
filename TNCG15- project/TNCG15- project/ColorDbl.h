#pragma once
#include <glm/glm.hpp>

struct ColorDbl {

	ColorDbl() {
		r = 0.0;
		g = 0.0;
		b = 0.0;
	}

	ColorDbl(double inR, double inG, double inB) {
		r = inR;
		g = inG;
		b = inB;
	}

	ColorDbl(glm::vec3 color){
		r = color.x; 
		g = color.y;
		b = color.z;
	}

	

	friend std::ostream& operator<<(std::ostream& os, ColorDbl dt)
	{
		os << dt.r << "," << dt.g << "," << dt.b << std::endl;
		return os;
	}

	ColorDbl operator * (double Res) {
		this->r * Res;
		this->g * Res;
		this->b * Res;
		return *this;
	}

	ColorDbl operator * (ColorDbl Res) {
		this->r* Res.r;
		this->g* Res.g;
		this->b* Res.b;
		return *this;
	}

	ColorDbl operator / (double Res) {
		this->r/ Res;
		this->g/ Res;
		this->b/ Res;
		return *this;
	}



	ColorDbl operator +=(ColorDbl const &Res) {
		r += Res.r;
		g += Res.g;
		b += Res.b;
		return *this;
	}

	ColorDbl operator = (ColorDbl const &Res) {
		this->r = Res.r;
		this->g = Res.g;
		this->b = Res.b;
		return *this;
	}






	 double r, g, b;
};