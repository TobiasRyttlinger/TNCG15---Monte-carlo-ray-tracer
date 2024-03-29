#pragma once

#include"Ray.h"
#include"Triangle.h"
#include "Vertex.h"
#include <iostream>
#include <vector>
#include "IntersectionPointTri.h"
#include "Tetrahedron.h"
#include "Light.h"
#include "Sphere.h"
#include "IntersectionPointSphere.h"
#include <list>
struct Scene {

 //Default constructor
	Scene() {}
		

		Vertex Vertices[14]{

			Vertex(-3.0, 0.0, 5.0, 1.0),//p0Roof
			Vertex(0.0, 6.0, 5.0, 1.0),//p1Roof
			Vertex(10.0, 6.0, 5.0, 1.0),//p2Roof
			Vertex(13.0, 0.0, 5.0, 1.0),//p3Roof
			Vertex(10.0, -6.0, 5.0, 1.0),//p4Roof
			Vertex(0.0, -6.0, 5.0, 1.0),//p5Roof
			Vertex(5.0, 0.0, 5.0, 1.0),//6midRoof

			Vertex(-3.0, 0.0, -5.0, 1.0),//p7Floor
			Vertex(0.0, 6.0, -5.0, 1.0),//p8Floor
			Vertex(10.0, 6.0, -5.0, 1.0),//p9Floor
			Vertex(13.0, 0.0, -5.0, 1.0),//p1f0loor
			Vertex(10.0, -6.0, -5.0, 1.0),//p11Floor
			Vertex(0.0, -6.0, -5.0, 1.0),//p12Floor
			Vertex(5.0, 0.0, -5.0, 1.0)//13midFloor
		};


		Material Lambertian_White = Material(ColorDbl(1.0, 1.0, 1.0),glm::vec3(1.0,1.0,1.0),3);
		Material Lambertian_Red = Material(ColorDbl(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),3);
		Material Lambertian_Blue = Material(ColorDbl(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0),3);
		Material Lambertian_Green = Material(ColorDbl(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0),3);
		Material Lambertian_Purple = Material(ColorDbl(0.5, 0.0, 0.5), glm::vec3(0.5, 0.0, 0.5),3);
		Material Lambertian_Gray = Material(ColorDbl(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8),3);
		Material Lambertian_Yellow = Material(ColorDbl(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0),3);
	
		Triangle triangles[30]{
			//Floor
		Triangle(Vertices[0], Vertices[1], Vertices[6], Lambertian_Gray),// T1Floor
		Triangle(Vertices[1], Vertices[2],  Vertices[6], Lambertian_Gray),//T2Floor
		Triangle(Vertices[2], Vertices[3],  Vertices[6], Lambertian_Gray),//T3Floor
		Triangle(Vertices[3], Vertices[4],  Vertices[6], Lambertian_Gray),//T4Floor
		Triangle(Vertices[4], Vertices[5],  Vertices[6], Lambertian_Gray),//T5Floor
		Triangle(Vertices[5], Vertices[0], Vertices[6], Lambertian_Gray),//T6Floor
			//Roof
		Triangle(Vertices[8], Vertices[7], Vertices[13], Lambertian_Gray),// T1Floor
		Triangle(Vertices[9], Vertices[8],  Vertices[13],Lambertian_Gray),//T2Floor
		Triangle(Vertices[10], Vertices[9],  Vertices[13], Lambertian_Gray),//T3Floor
		Triangle(Vertices[11], Vertices[10],  Vertices[13], Lambertian_Gray),//T4Floor
		Triangle(Vertices[12], Vertices[11],  Vertices[13], Lambertian_Gray),//T5Floor
		Triangle(Vertices[7], Vertices[12], Vertices[13], Lambertian_Gray),//T6Floor

		Triangle(Vertices[0], Vertices[5],  Vertices[7], Lambertian_Green),//T1Wall
		Triangle(Vertices[5], Vertices[12],  Vertices[7], Lambertian_Green),

		Triangle(Vertices[12], Vertices[5],  Vertices[4], Lambertian_Red),//T2Wall
		Triangle(Vertices[11], Vertices[12],  Vertices[4], Lambertian_Red),

		Triangle(Vertices[11], Vertices[4],  Vertices[3], Lambertian_Green),//T3Wall
		Triangle(Vertices[10], Vertices[11],  Vertices[3], Lambertian_Green),

		Triangle(Vertices[0], Vertices[7],  Vertices[8], Lambertian_Purple),//T4Wall
		Triangle(Vertices[0], Vertices[8],  Vertices[1], Lambertian_Purple),

		Triangle(Vertices[1], Vertices[8],  Vertices[9], Lambertian_Blue),//T5Wall
		Triangle(Vertices[1], Vertices[9],  Vertices[2], Lambertian_Blue),

		Triangle(Vertices[2], Vertices[9],  Vertices[10], Lambertian_Yellow),//T6Wall
		Triangle(Vertices[2], Vertices[10],  Vertices[3], Lambertian_Yellow)
		};

		void AddTethra(Tetrahedron& Tin) {
			triangles[24] = Tin.triangle[0];
			triangles[25] = Tin.triangle[1];
			triangles[26] = Tin.triangle[2];
			triangles[27] = Tin.triangle[3];
			Tet = Tin;
		}

		void AddLight(Light& Lin) {
			triangles[28] = Lin.Triangles[0];
			triangles[29] = Lin.Triangles[1];
			light = Lin;
		}

		std::list<IntersectionPointTri> Find_Triangle(Ray r)
		{
			std::list<IntersectionPointTri> Triangle_intersections = {};
			
			double disttriangel = 1000000;
			IntersectionPointTri ClosestTringle;

			for (auto& triangle : triangles)
			{
				glm::vec3 tempPoint;
				IntersectionPointTri tempIntersect;
				
				if (triangle.rayIntersection(r, tempPoint))
				{
					tempIntersect.Tri = triangle;
					tempIntersect.Tri.IntersectionPoint.pos = tempPoint + triangle.normal.Vec * 0.001f;
					tempIntersect.point = tempPoint;
				
					Triangle_intersections.push_back(tempIntersect);
					
				}
			}
		
			glm::vec3 Raystart = r.StartingPoint.pos;
	
			Triangle_intersections.sort([&Raystart](const auto &a, const auto &b) {
				return glm::length(a.point - Raystart) > glm::length(b.point - Raystart);
			});
			return Triangle_intersections;
		}

		std::list<IntersectionPointSphere> Find_sphere(Ray r)
		{
			std::list<IntersectionPointSphere> Sphere_intersections = {};
		
				glm::vec3 intersection;
				IntersectionPointSphere sph;
	
				intersection = sphere.rayIntersection(r, sphere.t);
					if (intersection != glm::vec3(0,0,0)) {
						sph.sphere = sphere;
						sph.P = intersection + sphere.get_normal(intersection)*0.0001f;
						Sphere_intersections.push_back(sph);
					}
				return Sphere_intersections;
		}

		void addSphere(double radius, glm::vec3 position) {
			 sphere = Sphere(radius, position);
		}
		int Lambertian = 0;
		int OrenNayar = 3;
		int Mirror = 1;
		const double Epsilon = 0.0000000000001;
		Sphere sphere;
		Tetrahedron Tet;
		Light light;
};