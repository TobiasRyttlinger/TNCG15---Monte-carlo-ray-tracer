#pragma once
#include "Direction.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "ColorDbl.h"
#include "Material.h"
#include "Ray.h"



struct Triangle {

	Triangle(){} //Default shit

	Triangle(Vertex p0In, Vertex p1In, Vertex p2In, Material matIn){

		p0 = p0In; p1 = p1In; p2 = p2In;

		edge1 = p1In.pos - p0In.pos;
		edge2 = p2In.pos - p0In.pos;

		material = matIn;
		Area = 0.5 * glm::length(cross(edge1, edge2));
		normal =  cross(edge1, edge2);

	}

	Vertex getPointOnTriangle(float u, float v) {
		return Vertex(p0.pos + (u * edge1 + v * edge2),0);
	}

	Vertex getPointOnTriangle(float u, float v, float w) {
		return Vertex((u * p0.pos + v * p1.pos + w * p2.pos),0);
	}


	bool rayIntersection(Ray& arg, Vertex& p) {
		
	
		glm::vec3 T = arg.StartingPoint - p0;
		glm::vec3 E1 = p1 - p0;
		glm::vec3 E2 = p2 - p0;
		glm::vec3 D = arg.EndPoint - arg.StartingPoint;
		glm::vec3 P = glm::cross(D, E2);
		glm::vec3 Q = glm::cross(T, E1);
		double Determinant = glm::dot(E1, P);
		double t = (glm::dot(Q, E2))  / (glm::dot(P, E1));
		double u = (glm::dot(P,  T))  / (glm::dot(P, E1));
		double v = (glm::dot(Q,  D))  / (glm::dot(P, E1));

		if (Determinant < EPSILON) { return false; }
		//std::cout << "broke at first" << std::endl;
		 if (fabs(Determinant) < EPSILON) { return false; }
		//std::cout << "ray is incoming from a good direction\n";
		
		 if (u < 0.0 || v < 0.0 || u + v > 1) { return false; }
		//std::cout << " Found intersection! ";

		 if (t < 1.0 ||  t <= 0.0) { return false; }
		
		else {
			// std::cout << "Returning true" << std::endl;
			arg.color = this->color;
			IntersectionPoint = GetBarycentric(u, v);
			Tout = t;
			
			p = GetBarycentric(u, v);
			return true;
		}
	}

	Vertex GetBarycentric(double u, double v)
	{
		Vertex p;
		p.pos.x = (1 - u - v) * p0.pos.x + u * p1.pos.x + v * p2.pos.x;
		p.pos.y = (1 - u - v) * p0.pos.y + u * p1.pos.y + v * p2.pos.y;
		p.pos.z = (1 - u - v) * p0.pos.z + u * p1.pos.z + v * p2.pos.z;
		if (p.pos.x < EPSILON) p.pos.x = 0;
		if (p.pos.y < EPSILON) p.pos.y = 0;
		if (p.pos.z < EPSILON) p.pos.z = 0;
		return p;
	}

	Triangle operator = (Triangle const &Tin) {
		p0 = Tin.p0;
		p1 = Tin.p1;
		p2 = Tin.p2;

		edge1 = Tin.p1.pos - Tin.p0.pos;
		edge2 = Tin.p2.pos - Tin.p0.pos;

		material = Tin.material;
		Area =Tin.Area;
		normal = Tin.normal;
		return *this;

	}

	friend std::ostream& operator<<(std::ostream& os,  Triangle dt)
	{
		os << dt.p0 << "," << dt.p1 << "," << dt.p2 <<" With the color: "<<"( "<< dt.color <<" )"<< std::endl;
		return os;
	}
	Material material;
	const double EPSILON = 0000000000.1;
	Vertex p0,p1,p2;
	ColorDbl color;
	double Area;
	Vertex IntersectionPoint;
	glm::vec3 edge1, edge2;
	Direction normal;
	double Tout;
	Triangle* hit_triangle;
};