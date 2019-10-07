#pragma once
#include"Ray.h"
#include"Triangle.h"
#include "Vertex.h"
#include <iostream>
#include <vector>
#include "IntersectionPointTri.h"
#include "Tetrahedron.h"
#include "Light.h"

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


		ColorDbl White = ColorDbl(1.0, 1.0, 1.0);
		ColorDbl Red = ColorDbl(1.0, 0.0, 0.0);
		ColorDbl Blue = ColorDbl(0.0, 0.0, 1.0);
		ColorDbl Green = ColorDbl(0.0, 1.0, 0.0);
		ColorDbl Purple = ColorDbl(0.5, 0.0, 0.5);
		ColorDbl Gray = ColorDbl(0.8, 0.8, 0.8);
		ColorDbl Yellow = ColorDbl(1.0, 1.0, 0.0);
	
		Triangle triangles[50]{
			//ROof
		Triangle(Vertices[0], Vertices[1], Vertices[6], Gray),// T1Floor
		Triangle(Vertices[1], Vertices[2],  Vertices[6], Gray),//T2Floor
		Triangle(Vertices[2], Vertices[3],  Vertices[6], Gray),//T3Floor
		Triangle(Vertices[3], Vertices[4],  Vertices[6], Gray),//T4Floor
		Triangle(Vertices[4], Vertices[5],  Vertices[6], Gray),//T5Floor
		Triangle(Vertices[5], Vertices[0], Vertices[6], Gray),//T6Floor
			//FloOR
		Triangle(Vertices[8], Vertices[7], Vertices[13], Gray),// T1Floor
		Triangle(Vertices[9], Vertices[8],  Vertices[13], Gray),//T2Floor
		Triangle(Vertices[10], Vertices[9],  Vertices[13], Gray),//T3Floor
		Triangle(Vertices[11], Vertices[10],  Vertices[13], Gray),//T4Floor
		Triangle(Vertices[12], Vertices[11],  Vertices[13], Gray),//T5Floor
		Triangle(Vertices[7], Vertices[12], Vertices[13], Gray),//T6Floor

		Triangle(Vertices[0], Vertices[5],  Vertices[7], Green),//T1Wall
		Triangle(Vertices[5], Vertices[12],  Vertices[7], Green),

		Triangle(Vertices[12], Vertices[5],  Vertices[4], Blue),//T2Wall
		Triangle(Vertices[11], Vertices[12],  Vertices[4], Blue),

		Triangle(Vertices[11], Vertices[4],  Vertices[3], Red),//T3Wall
		Triangle(Vertices[10], Vertices[11],  Vertices[3], Red),

		Triangle(Vertices[0], Vertices[7],  Vertices[8], Gray),//T4Wall
		Triangle(Vertices[0], Vertices[8],  Vertices[1], Gray),

		Triangle(Vertices[1], Vertices[8],  Vertices[9], Yellow),//T5Wall
		Triangle(Vertices[1], Vertices[9],  Vertices[2], Yellow),

		Triangle(Vertices[2], Vertices[9],  Vertices[10], Purple),//T6Wall
		Triangle(Vertices[2], Vertices[10],  Vertices[3], Purple)
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

		bool LightIntersection(Ray& arg, Vertex& Point) {
			for (auto& t : triangles)
			{
				Vertex tempPoint;
				//Check if the ray intersect the tringle, if true add the triangle to the returning vector		
				if (t.rayIntersection(arg, tempPoint))
				{
					//std::cout << tempPoint.x << "  x  " << tempPoint.y << "  y  " << tempPoint.z << "  z   " << std::endl;
					Point = tempPoint;
					return true;
				}
			}
			return false;

		}
		
		Light light;
};