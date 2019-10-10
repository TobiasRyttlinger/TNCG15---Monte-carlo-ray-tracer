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
struct Scene {

 //Default constructor
	Scene() {}
		

		Vertex Vertices[14]{

			Vertex(-3.0, 0.0, 5.0, 1.0),//p1Roof
			Vertex(0.0, 6.0, 5.0, 1.0),//p2Roof
			Vertex(10.0, 6.0, 5.0, 1.0),//p3Roof
			Vertex(13.0, 0.0, 5.0, 1.0),//p4Roof
			Vertex(10.0, -6.0, 5.0, 1.0),//p5Roof
			Vertex(0.0, -6.0, 5.0, 1.0),//p6Roof
			Vertex(5.0, 0.0, 5.0, 1.0),//midRoof

			Vertex(-3.0, 0.0, -5.0, 1.0),//p1Floor
			Vertex(0.0, 6.0, -5.0, 1.0),//p2Floor
			Vertex(10.0, 6.0, -5.0, 1.0),//p3Floor
			Vertex(13.0, 0.0, -5.0, 1.0),//p4Floor
			Vertex(10.0, -6.0, -5.0, 1.0),//p5Floor
			Vertex(0.0, -6.0, -5.0, 1.0),//p6Floor
			Vertex(5.0, 0.0, -5.0, 1.0)//midFloor
		};


		Material Lambertian_White = Material(ColorDbl(1.0, 1.0, 1.0),glm::vec3(1.0,1.0,1.0));
		Material Lambertian_Red = Material(ColorDbl(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
		Material Lambertian_Blue = Material(ColorDbl(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0));
		Material Lambertian_Green = Material(ColorDbl(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		Material Lambertian_Purple = Material(ColorDbl(0.5, 0.0, 0.5), glm::vec3(0.5, 0.0, 0.5));
		Material Lambertian_Gray = Material(ColorDbl(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8));
		Material Lambertian_Yellow = Material(ColorDbl(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0));
	
		Triangle triangles[50]{
			//ROof
		Triangle(Vertices[0], Vertices[1], Vertices[6], Lambertian_Gray),// T1Floor
		Triangle(Vertices[1], Vertices[2],  Vertices[6], Lambertian_Gray),//T2Floor
		Triangle(Vertices[2], Vertices[3],  Vertices[6], Lambertian_Gray),//T3Floor
		Triangle(Vertices[3], Vertices[4],  Vertices[6], Lambertian_Gray),//T4Floor
		Triangle(Vertices[4], Vertices[5],  Vertices[6], Lambertian_Gray),//T5Floor
		Triangle(Vertices[5], Vertices[0], Vertices[6], Lambertian_Gray),//T6Floor
			//FloOR
		Triangle(Vertices[8], Vertices[7], Vertices[13], Lambertian_Gray),// T1Floor
		Triangle(Vertices[9], Vertices[8],  Vertices[13],Lambertian_Gray),//T2Floor
		Triangle(Vertices[10], Vertices[9],  Vertices[13], Lambertian_Gray),//T3Floor
		Triangle(Vertices[11], Vertices[10],  Vertices[13], Lambertian_Gray),//T4Floor
		Triangle(Vertices[12], Vertices[11],  Vertices[13], Lambertian_Gray),//T5Floor
		Triangle(Vertices[7], Vertices[12], Vertices[13], Lambertian_Gray),//T6Floor

		Triangle(Vertices[0], Vertices[5],  Vertices[7], Lambertian_Green),//T1Wall
		Triangle(Vertices[5], Vertices[12],  Vertices[7], Lambertian_Green),

		Triangle(Vertices[12], Vertices[5],  Vertices[4], Lambertian_Green),//T2Wall
		Triangle(Vertices[11], Vertices[12],  Vertices[4], Lambertian_Green),

		Triangle(Vertices[11], Vertices[4],  Vertices[3], Lambertian_Purple),//T3Wall
		Triangle(Vertices[10], Vertices[11],  Vertices[3], Lambertian_Purple),

		Triangle(Vertices[0], Vertices[7],  Vertices[8], Lambertian_Gray),//T4Wall
		Triangle(Vertices[0], Vertices[8],  Vertices[1], Lambertian_Gray),

		Triangle(Vertices[1], Vertices[8],  Vertices[9], Lambertian_Red),//T5Wall
		Triangle(Vertices[1], Vertices[9],  Vertices[2], Lambertian_Red),

		Triangle(Vertices[2], Vertices[9],  Vertices[10], Lambertian_Blue),//T6Wall
		Triangle(Vertices[2], Vertices[10],  Vertices[3], Lambertian_Blue)
		};

		void AddTethra(Tetrahedron& Tin) {
			triangles[24] = Tin.triangle[0];
			triangles[25] = Tin.triangle[1];
			triangles[26] = Tin.triangle[2];
			triangles[27] = Tin.triangle[3];
		}

		void AddLight(Light& Lin) {
			triangles[28] = Lin.Triangles[0];
			triangles[29] = Lin.Triangles[1];
			light = Lin;
		}

		IntersectionPointTri DetectTriangel(Ray& r)
		{
			std::vector<IntersectionPointTri> intersections = {};
			//Loop over all triangles in the vector
			float disttriangel = 1000000.0f;
			IntersectionPointTri ClosestTringle;

			for (auto& triangle : triangles)
			{
				Vertex tempPoint;
				
				IntersectionPointTri tempIntersect;
				//Check if the ray intersect the tringle, if true add the triangle to the returning vector		
				if (triangle.rayIntersection(r, tempPoint))
				{
					tempIntersect.Tri = triangle;
					tempIntersect.point = tempPoint;
					
					//Check for closest triangle
					float dist = r.StartingPoint.Distance(tempIntersect.point);
					if (dist < disttriangel) {
						disttriangel = dist;
						ClosestTringle = tempIntersect;
					}
				}
			}
			return ClosestTringle;
		}


		bool SendShadowRays(Light Light, Ray& r, Vertex Ip, Direction normal) {
			Vertex LightPoint = Light.getRandomPointOnLight();
			Vertex StartingPoint = Vertex(Ip.pos + glm::vec3(normal.Vec.x * Epsilon, normal.Vec.y * Epsilon, normal.Vec.z * Epsilon), 0);
			float  t;
			Ray ShadowRay = Ray(StartingPoint, LightPoint);
			Vertex p;
			
			if (sphere.rayIntersection(ShadowRay, t)) {
			//	std::cout << t << std::endl;
				return false;
			}
			for (int i = 24; i <= 27; i++) {

				if (triangles[i].rayIntersection(ShadowRay,p)) {
					return false;
				}

			}
			

			

				return true;
		}

		void addSphere(double radius, glm::vec3 position) {
			 sphere = Sphere(radius, position);

		}
		const double Epsilon = 0.001;
		Sphere sphere;

		Light light;
};