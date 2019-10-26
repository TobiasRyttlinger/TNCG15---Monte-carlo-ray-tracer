#pragma once
#include "ColorDbl.h"
#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>
#include <iomanip>
#include "glm/gtx/vector_angle.hpp"
#include <random>

struct Material {

	Material(){}

	Material(ColorDbl ColorIn, glm::vec3 RhoIn, int type) {
		color = ColorIn;
		rhoOPi = RhoIn/(float)M_PI;
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
			float theta = glm::acos(thetaOut);
			float Sigma = 0.3f*0.3f;
			
			float Beta = std::min(theta, thetaIn);
			float alpha = std::max(theta, thetaIn);

			float A = 1 - 0.5 * Sigma /( Sigma +0.33 );
			float B = 0.45 * Sigma /( Sigma + 0.09 );

			float phiIn_Out = glm::dot(In,Out);
			return rhoOPi * (A + (B * std::max(0.0f, cos(phiIn_Out))) * glm::sin(alpha) * glm::tan(Beta));
		}
		if (this->Id == Glass) {

			float Cos_In = glm::clamp(-1.0f, 1.0f, glm::dot(In, normal));
			float n1 = 1;
			float n2 = 1.5;
			glm::vec3 n = normal;

			if (Cos_In < 0) {
				Cos_In = -Cos_In; 
			}
			else { 
				std::swap(n1, n2);
				n = -normal; 
			}

			float N = n1 / n2;
			float k = 1 - N * N * (1 - Cos_In * Cos_In);
			if (k < 0) {
				return glm::vec3(0,0,0);
			}
			return N * In + (float)(N * Cos_In - sqrtf(k)) * n;
		}


		return glm::vec3(0.0,0.0,0.0);
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