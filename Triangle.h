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
	
		normal =  glm::normalize(glm::cross(edge1, edge2));
	}

	glm::vec3 getPointOnTriangle(float u, float v) {
		return glm::vec3(p0.pos + (u * edge1 + v * edge2));
	}

	glm::vec3 getPointOnTriangle(float u, float v, float w) {
		return glm::vec3((u * p0.pos + v * p1.pos + w * p2.pos));
	}

	const glm::vec3& getNormal() const {
		return normal.Vec;
	}

	bool rayIntersection(Ray& arg, glm::vec3& p) {
		glm::vec3 rayStart = arg.StartingPoint.pos;
		glm::vec3 direction = glm::normalize(arg.direction.Vec);

		glm::vec3 edgeNormal = glm::cross(direction, edge2);
		double determinant = glm::dot(edge1, edgeNormal);
		if (fabs(determinant) < 0.0000001) return false;
	
		if (determinant > -EPSILON && determinant < EPSILON) return false;

		double inverted_determinant = 1.0 / determinant;

		glm::vec3 rayToVertex = rayStart - p0.pos;

		double U = glm::dot(rayToVertex, edgeNormal) * inverted_determinant;

		if (U < 0.0 || U > 1.0) return false;

		glm::vec3 Q = glm::cross(rayToVertex, edge1);

		double V = glm::dot(direction, Q) * inverted_determinant;

		if (V < 0.0 || U + V  > 1.0)
			return false;

		double T = glm::dot(edge2, Q) * inverted_determinant;
		if (T > EPSILON) {

			Tout = T;
			p = rayStart + direction * (float)T;
			//IntersectionPoint.pos = rayStart + direction * (float)T;
			return true;
		}
		else return false;

		
	}

	glm::vec3 getRandomPoint() {
		double triangleArea = area();
		double a = (rand() / RAND_MAX) / triangleArea;
		double b = (rand() / RAND_MAX) / triangleArea;
		if (a + b > 1.0) {
			return getRandomPoint();
		}
		return GetBarycentric((float)a, (float)b);
	}

	double area() {
		return 0.5 * glm::length(glm::cross(edge1, edge2));
	}

	glm::vec3 GetBarycentric(double u, double v)
	{
		glm::vec3 p;
		p.x = (1 - u - v) * p0.pos.x + u * p1.pos.x + v * p2.pos.x;
		p.y = (1 - u - v) * p0.pos.y + u * p1.pos.y + v * p2.pos.y;
		p.z = (1 - u - v) * p0.pos.z + u * p1.pos.z + v * p2.pos.z;
		if (p.x < EPSILON) p.x = 0;
		if (p.y < EPSILON) p.y = 0;
		if (p.z < EPSILON) p.z = 0;
		return p;
	}

	Triangle operator = (Triangle const &Tin) {
		this->p0 = Tin.p0;
		this->p1 = Tin.p1;
		this->p2 = Tin.p2;

		this->edge1 = Tin.p1.pos - Tin.p0.pos;
		this->edge2 = Tin.p2.pos - Tin.p0.pos;
		this->IntersectionPoint = Tin.IntersectionPoint;
		this->material = Tin.material;
	
		this->normal = Tin.normal;
		return *this;

	}

	friend std::ostream& operator<<(std::ostream& os,  Triangle dt)
	{
		os << dt.p0 << "," << dt.p1 << "," << dt.p2 <<" With the color: "<<"( "<< dt.material.color <<" )"<< std::endl;
		return os;
	}

	Material material;
	const double EPSILON = 0.000001;
	Vertex p0,p1,p2;
	Vertex IntersectionPoint;
	glm::vec3 edge1, edge2;
	Direction normal;
	double Tout;
	Triangle* hit_triangle;
};