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


		Material Lambertian_White = Material(ColorDbl(1.0, 1.0, 1.0),glm::vec3(1.0,1.0,1.0),0);
		Material Lambertian_Red = Material(ColorDbl(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), 0);
		Material Lambertian_Blue = Material(ColorDbl(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 0);
		Material Lambertian_Green = Material(ColorDbl(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), 0);
		Material Lambertian_Purple = Material(ColorDbl(0.5, 0.0, 0.5), glm::vec3(0.5, 0.0, 0.5), 0);
		Material Lambertian_Gray = Material(ColorDbl(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8), 0);
		Material Lambertian_Yellow = Material(ColorDbl(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0), 0);
	
		Triangle triangles[50]{
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

		Triangle(Vertices[0], Vertices[5],  Vertices[7], Lambertian_Yellow),//T1Wall
		Triangle(Vertices[5], Vertices[12],  Vertices[7], Lambertian_Yellow),

		Triangle(Vertices[12], Vertices[5],  Vertices[4], Lambertian_Red),//T2Wall
		Triangle(Vertices[11], Vertices[12],  Vertices[4], Lambertian_Red),

		Triangle(Vertices[11], Vertices[4],  Vertices[3], Lambertian_Yellow),//T3Wall
		Triangle(Vertices[10], Vertices[11],  Vertices[3], Lambertian_Yellow),

		Triangle(Vertices[0], Vertices[7],  Vertices[8], Lambertian_Purple),//T4Wall
		Triangle(Vertices[0], Vertices[8],  Vertices[1], Lambertian_Purple),

		Triangle(Vertices[1], Vertices[8],  Vertices[9], Lambertian_Blue),//T5Wall
		Triangle(Vertices[1], Vertices[9],  Vertices[2], Lambertian_Blue),

		Triangle(Vertices[2], Vertices[9],  Vertices[10], Lambertian_Purple),//T6Wall
		Triangle(Vertices[2], Vertices[10],  Vertices[3], Lambertian_Purple)
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
				glm::vec3 tempPoint;
				
				IntersectionPointTri tempIntersect;
				//Check if the ray intersect the tringle, if true add the triangle to the returning vector		
				if (triangle.rayIntersection(r, tempPoint))
				{
					tempIntersect.Tri = triangle;
					tempIntersect.point.pos = tempPoint;
					
					//Check for closest triangle
					double dist = r.StartingPoint.Distance(tempIntersect.point);
					if (dist < disttriangel) {
						disttriangel = dist;
						ClosestTringle = tempIntersect;
					}
				}
			}
			r.EndPoint = ClosestTringle.point;
			return ClosestTringle;
		}


		bool SendShadowRays(Light Light, Ray& r, Vertex Ip, Direction normal) {
			Vertex LightPoint = light.Vertices[2];
			Direction D = normal;
			Vertex StartingPoint = Vertex(Ip.pos + D.Vec, 0);
			float  t;
			Ray ShadowRay = Ray(StartingPoint, LightPoint);

			
			if (sphere.rayIntersection(ShadowRay, t)) return false;

			for (int i = 24; i <= 27; i++) {

				if (!triangles[i].rayIntersection(ShadowRay, Ip.pos)) {
					r = ShadowRay;
					return true;
					
				}
				return false;
			}
		
			
		}

		void addSphere(double radius, glm::vec3 position) {
			 sphere = Sphere(radius, position);

		}
		const double Epsilon = 0.0000000000001;
		Sphere sphere;

		Light light;
};