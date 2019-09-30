#pragma once
#include"Ray.h"
#include"Triangle.h"
#include "Vertex.h"
struct Scene {

 //Default constructor
	Scene() {}
		Vertex Vertices[14]{
			Vertex(-3.0, 0.0, -5.0, 1.0),//p1Floor
			Vertex(-3.0, 0.0, 5.0, 1.0),//p1Roof

			Vertex(0.0, 6.0, -5.0, 1.0),//p2Floor
			Vertex(0.0, 6.0, 5.0, 1.0),//p2Roof

			Vertex(10.0, 6.0, -5.0, 1.0),//p3Floor
			Vertex(10.0, 6.0, 5.0, 1.0),//p3Roof

			Vertex(13.0, 0.0, -5.0, 1.0),//p4Floor
			Vertex(13.0, 0.0, 5.0, 1.0),//p4Roof

			Vertex(10.0, -6.0, -5.0, 1.0),//p5Floor
			Vertex(10.0, -6.0, 5.0, 1.0),//p5Roof

			Vertex(0.0, -6.0, -5.0, 1.0),//p6Floor
			Vertex(0.0, -6.0, 5.0, 1.0),//p6Roof

			Vertex(5.0, 0.0, -5.0, 1.0),//midFloor
			Vertex(5.0, 0.0, 5.0, 1.0)//midRoof
		};


		ColorDbl White = glm::vec3(1.0, 1.0, 1.0);
		ColorDbl Red = glm::vec3(1.0, 0.0, 0.0);
		ColorDbl Blue = glm::vec3(0.0, 0.0, 1.0);
		ColorDbl Green = glm::vec3(0.0, 1.0, 0.0);
		ColorDbl Purple = glm::vec3(0.5, 0.0, 0.5);
		ColorDbl Gray = glm::vec3(0.8, 0.8, 0.8);
		ColorDbl Yellow = glm::vec3(1.0, 1.0, 0.0);

		Triangle triangles[20]{
		Triangle(Vertices[2], Vertices[0], Vertices[1], White),
		Triangle(Vertices[0], Vertices[10], Vertices[12], White),// T1Floor
		Triangle(Vertices[0], Vertices[2],  Vertices[12], White),//T2Floor
		Triangle(Vertices[2], Vertices[4],  Vertices[12], White),//T3Floor
		Triangle(Vertices[4], Vertices[6],  Vertices[12], White),//T4Floor
		Triangle(Vertices[6], Vertices[8],  Vertices[12], White),//T5Floor
		Triangle(Vertices[8], Vertices[10], Vertices[12], White),//T6Floor

		Triangle(Vertices[0], Vertices[1],  Vertices[2], Green),//T1Wall
		Triangle(Vertices[1], Vertices[3],  Vertices[2], Purple),//T2Wall

		Triangle(Vertices[3], Vertices[2],  Vertices[5], Red),//T3Wall
		Triangle(Vertices[2], Vertices[5],  Vertices[4], Gray),//T4Wall

		Triangle(Vertices[5], Vertices[2],  Vertices[4], Blue),//T5Wall
		Triangle(Vertices[5], Vertices[7],  Vertices[6], Yellow),//T6Wall
		};

		void getIntersection(Ray& arg) {

			//Create more intersections here
			for (int i = 0; i < 12; i++) {
				if (triangles[i].rayIntersection(arg)) break;
			}
		}

};