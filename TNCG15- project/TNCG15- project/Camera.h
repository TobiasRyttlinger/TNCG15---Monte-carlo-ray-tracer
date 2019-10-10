#pragma once
#include <glm/glm.hpp>
#include "Pixel.h"
#include "Ray.h"
#include "ColorDbl.h"
#include <cmath>
#include <random>
#include <glm/gtc/constants.hpp>
#include "Tetrahedron.h"
#include "Scene.h"
#include "Material.h"
struct Camera {

	Camera() {

		CameraSwap = 0;
		for (int i = 0; i < HEIGHT; i++) {
			pixels[i] = new Pixel[HEIGHT];
			for (int j = 0; j < WIDTH; j++) {
				pixels[i][j] = Pixel();

			}
		}

	}

	~Camera()
	{
		for (int i = 0; i < HEIGHT; ++i) {
			delete[] pixels[i];
		}
		delete[] pixels;
	}

	void CreateImage() {

		FILE* Output = fopen("Output.ppm", "wb");

		fprintf(Output, "P6\n%i %i 255\n", WIDTH, HEIGHT);

		double iMax = Imax();
		double Factor = Trunc / iMax;

		std::cout << "Writing to file Output.ppm!!" << std::endl;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {

				fputc((int)(pixels[i][j].color.r * Factor), Output);
				fputc((int)(pixels[i][j].color.g * Factor), Output);
				fputc((int)(pixels[i][j].color.b * Factor), Output);

			}
		}
		fclose(Output);
		std::cout << "Done!!" << std::endl;
	}

	double Imax() {
		double iMax = 0.0;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {

				if (pixels[i][j].color.r > iMax) iMax = pixels[i][j].color.r;
				if (pixels[i][j].color.g > iMax) iMax = pixels[i][j].color.g;
				if (pixels[i][j].color.b > iMax) iMax = pixels[i][j].color.b;

			}
		}
		return iMax;
	}

	void SwapCamera(int choice) {
		if (choice <= 0) {
			CameraSwap = 0;
		}
		else if (choice >= 1) {
			CameraSwap = 1;
		}
	}

	ColorDbl CastRay(Ray r, Scene& scene, int depth, ColorDbl importance) {

		Triangle tri = scene.DetectTriangel(r).Tri;
		ColorDbl s = ColorDbl();
		//std::cout << tri.IntersectionPoint << std::endl;
		
			if (tri.rayIntersection(r, tri.IntersectionPoint))
			{	
				
				double Tlenght = tri.Tout;

				if (scene.sphere.rayIntersection(r, scene.sphere.t)) {

					if (scene.sphere.t < Tlenght) {

						Direction D = (scene.sphere.Ip-scene.light.getRandomPointOnLight());
						Ray newR = Ray(scene.sphere.Ip, D);
						//return scene.light.GetEmission() * (0.8 / M_PI) * std::max(0.0f, glm::dot(scene.sphere.get_normal(scene.sphere.Ip.pos), D.Vec));
						return CastRay(newR, scene, 0, ColorDbl(1, 1, 1));
					}
				}
				//std::cout << PL << std::endl;
				if (scene.SendShadowRays(scene.light, r, tri.IntersectionPoint, tri.normal)) {

					Direction DirOut = (scene.light.getRandomPointOnLight() - tri.IntersectionPoint);

						glm::vec3 Brdf = tri.material.GetBRDF(tri.IntersectionPoint, 0, tri.normal, DirOut);
						return scene.light.GetEmission()*tri.material.color/M_PI *std::max(0.0f,glm::dot(tri.normal.Vec, DirOut.Vec));
				}



				return ColorDbl(0, 0, 0);
			

		}
		
		return  s;
	}


	

	glm::vec3& operator *(const double &Din) {
		glm::vec3 X;
		X.x *= Din;
		X.y *= Din;
		X.z *= Din;
		return X;
	}

	void render(Scene& scene) { //WHat tha fuck is this

		Ray r;
		ColorDbl Color;
		int Samples = 1;
		Vertex StartPoint = Eyes[CameraSwap];
		
		double c1StartY = c1.pos.y + pixelSize/2;
		double c1StartZ = c1.pos.z + pixelSize/2;

		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {

				Vertex CameraPlane = Vertex(0.0f, c1StartY + ((double)i) * pixelSize, c1StartZ + ((double)j) * pixelSize, 1.0f);

				for (int k = 0; k < Samples; k++) {
					Ray ray = Ray(StartPoint,CameraPlane);
					Color = CastRay(ray, scene, 0, ColorDbl(1,1,1));

					pixels[j][i].GetNewColor(Color);
				}

			}

			std::cout << (double)i/HEIGHT*100 << "%" << std::endl;
		}

	}


	const double Epsilon = 0.00001;
	Scene* scene;
	const double Trunc = 255.99;
	const int HEIGHT = 800;
	const int WIDTH = 800;
	float t;
	Pixel** pixels = new Pixel * [HEIGHT];
	const double pixelSize = 0.0025;
	Light LightSource;
	glm::vec3 pos;
	double max = 0.0;
	int CameraSwap = 0;

	void RotMat(glm::mat4& m, Direction X, Direction Y, Direction Z)
	{
		m[0][0] = X.Vec.x;
		m[0][1] = X.Vec.y;
		m[0][2] = X.Vec.z;
		m[1][0] = Y.Vec.x;
		m[1][1] = Y.Vec.y;
		m[1][2] = Y.Vec.z;
		m[2][0] = Z.Vec.x;
		m[2][1] = Z.Vec.y;
		m[2][2] = Z.Vec.z;
		m[3][3] = 1.0;
	}

	//Vertex PointLight = Vertex(5, 0, 5, 0);

	Vertex Eyes[2]{
		Vertex(-2, 0, 0, 0),
		Vertex(-1, 0, 0, 0)
	};

	Vertex c1 = Vertex(0, -1, -1, 0);
	Vertex c2 = Vertex(0, 1, -1, 0);
	Vertex c3 = Vertex(0, 1, 1, 0);
	Vertex c4 = Vertex(0, -1, 1, 0);
};