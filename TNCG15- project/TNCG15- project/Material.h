#pragma once
#include "ColorDbl.h"
#include <glm/glm.hpp>
#include "glm/gtx/vector_angle.hpp"
struct Material {

	Material(){}

	Material(ColorDbl ColorIn, glm::vec3 RhoIn, int type) {
		color = ColorIn;
		rhoOPi = glm::one_over_pi<float>() * RhoIn;
		Id = type;
	}
	Material operator = (Material& Min) {
		this->color = Min.color;
		this->rho = Min.rho;
		this->rhoOPi = Min.rhoOPi;
		this->color = Min.color;
		this->Id = Min.Id;
		return *this;
	}

	Material operator = (const Material& Min) {
		this->color = Min.color;
		this->rho = Min.rho;
		this->rhoOPi = Min.rhoOPi;
		this->color = Min.color;
		this->Id = Min.Id;
		return *this;
	}

	glm::vec3 GetBRDF(Vertex IntersectinPoint,int type, Direction In, Direction Out ) {
		if (this->Id == 0) {
			return rhoOPi;
		}
		return glm::vec3(0.0);
		
	}

	ColorDbl color;
	glm::vec3 rho;
	glm::vec3 rhoOPi;
	int Id;
	int Lambertian = 0;
	int Specular = 1;
	int Lightsource = 2;



};