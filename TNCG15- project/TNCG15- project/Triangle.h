#pragma once
#include "Direction.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "ColorDbl.h"

#include "Ray.h"


struct Triangle {

	Triangle(){} //Default shit

	Triangle(Vertex p0In, Vertex p1In, Vertex p2In, ColorDbl colorIn){

		p0 = p0In; p1 = p1In; p2 = p2In;

		edge1 = p1In.pos - p0In.pos;
		edge2 = p2In.pos - p0In.pos;

		color = colorIn;
		Area = 0.5 * glm::length(cross(edge1, edge2));
		normal =  cross(edge1, edge2);
	}

	bool rayIntersection(Ray& arg) {
		const double EPSILON = 0.000000001;
		glm::vec3 T = arg.StartingPoint - p0;
		glm::vec3 E1 = p1 - p0;
		glm::vec3 E2 = p2 - p0;
		glm::vec3 D = arg.EndPoint - arg.StartingPoint;
		glm::vec3 P = glm::cross(D, E2);
		glm::vec3 Q = glm::cross(T, E1);
		double Determinant = glm::dot(E1, P);
		double t = (glm::dot(Q, E2)) / (glm::dot(P, E1));
		double u = (glm::dot(P, T)) / (glm::dot(P, E1));
		double v = (glm::dot(Q, D)) / (glm::dot(P, E1));

		if (Determinant < EPSILON) return false;

		if (fabs(Determinant) < EPSILON) return false;
		std::cout << "ray is incoming from a good direction\n";
		
		if (u < 0.0 || v > 1.0) return false;
		std::cout << " Found intersection! ";

		if(t < 1.0 ||  t <= 0.0)return false;
		
		else {
			glm::vec3 NewD = glm::vec3(D.x * t, D.y * t, D.z * t);
			Direction EyeIp = Direction(T.x, T.y, T.z)+NewD;
			Vertex Ip = Vertex(EyeIp.Vec.x, EyeIp.Vec.y, EyeIp.Vec.z, 1.0);

			arg.EndPoint = Ip;
			arg.color = color * double(glm::dot(glm::vec3(normal.Vec.x, normal.Vec.y, normal.Vec.z ), glm::normalize(-D)));

			return true;
		}
	}


	Vertex p0,p1,p2;
	ColorDbl color;
	double Area;
	glm::vec3 edge1, edge2;
	Direction normal;

};