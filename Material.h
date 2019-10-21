#pragma once
#include "ColorDbl.h"
#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>
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

	glm::vec3 GetBRDF(glm::vec3 IntersectinPoint,int type, glm::vec3 In, glm::vec3 Out ,glm::vec3 normal) {
		if (this->Id == Lambertian) {
			return rhoOPi;
		}
		

		if (this->Id == OrenNayar){
			float thetaIn = (glm::dot(In,normal));
			float thetaOut = (glm::dot(Out,normal));
			float lambda = 0.3f;
			float Beta = std::min(thetaIn,thetaOut);
			float alpha = std::max(thetaIn, thetaOut);
			float A = 1 - 0.5*((std::pow(lambda,2)) /(std::pow(lambda,2)+0.33));
			float B = 0.45*((std::pow(lambda, 2)) / (std::pow(lambda, 2) + 0.09));
			float phiIn_Out = glm::dot(In,Out);

			//std::cout << thetaIn <<", "<< thetaOut << std::endl;
			return rhoOPi * std::max(0.0f, glm::dot(-In, normal))* (float)((A + (B * std::max(0.0f, cos(phiIn_Out))) * sin(alpha) * tan(Beta)));
		}
		if (this->Id == Glass) {

			float n1 = 1.0f;
			float n2 = 1.5f;

			float c1 = glm::dot(In, normal);
	
			if (c1 < 0) {
				c1 = -c1;
			}

			else {
				normal = -normal;
				std::swap(n1, n2);
			}

			float N = n1 / n2;
			float c2 = sqrt(1 - pow(N, 2) * pow(sin(glm::angle(In, normal)), 2));
			if (c2 < 0) {
				return glm::vec3(0, 0, 0);
			}
			glm::vec3 T = N * (In + c1 * normal) - N * c2;

			return T;

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
	int OrenNayar = 3;
	int Glass = 4;


};