#pragma once
#include "ColorDbl.h"
#include <glm/glm.hpp>
#include "glm/gtx/vector_angle.hpp"
struct Material {

	Material(){}

	Material(ColorDbl ColorIn, glm::vec3 RhoIn) {
		color = ColorIn;
		rhoOPi = glm::one_over_pi<float>() * RhoIn;

	}
	Material operator = (Material& Min) {
		this->color = Min.color;
		this->rho = Min.rho;
		this->rhoOPi = Min.rhoOPi;
		this->color = Min.color;
		return *this;
	}

	Material operator = (const Material& Min) {
		this->color = Min.color;
		this->rho = Min.rho;
		this->rhoOPi = Min.rhoOPi;
		this->color = Min.color;
		return *this;
	}

	glm::vec3 GetBRDF(Vertex IntersectinPoint,int type, Direction In, Direction Out ) {
		if (type = Lambertian) {
			return rhoOPi;
		}
		return glm::vec3(0,0,0);
	}
	int Lambertian = 0;
	ColorDbl color;
	glm::vec3 rho;
	glm::vec3 rhoOPi;




};