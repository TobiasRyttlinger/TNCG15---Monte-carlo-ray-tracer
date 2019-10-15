#pragma once

#include "ColorDbl.h"
#include <glm/glm.hpp>
#include "Direction.h"
#include"Ray.h"



struct Surface {

	Surface(){}

	Surface(ColorDbl& color, const int model){
		if (model == LightSorce) {
			color = ColorDbl(1000, 1000, 1000);
		}
		else {
			col = color;
			reflModel = model;
		}
	}

	Ray SurfaceBounce(Ray& ray, glm::vec3& p, const Direction& normal) {
		if (reflModel == Lambertian) {

		}

		else if (reflModel == Specular) {

		}

		else {

		}



	}


	ColorDbl col;
	Ray r;
	glm::vec3 point;
	Direction N;
	int reflModel;
	const int Lambertian = 0;
	const int Specular = 1;
	const int LightSorce = 2;
};