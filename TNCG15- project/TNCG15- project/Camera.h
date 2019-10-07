#pragma once
#include <glm/glm.hpp>
#include "Pixel.h"
#include "Ray.h"
#include "ColorDbl.h"
#include <random>
#include <cmath>
#include <random>
#include <glm/gtc/constants.hpp>
#include "Tetrahedron.h"
#include "Light.h"
struct Camera {

	Camera() {

		CameraSwap = 1;
		for (int i = 0; i < WIDTH; i++) {
			pixels[i] = new Pixel[WIDTH];
			for (int j = 0; j < HEIGHT; j++) {
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

	ColorDbl CastRay(Ray r, Scene& scene, int depth, ColorDbl importance){
		
		Triangle tri = scene.DetectTriangel(r).Tri;
		ColorDbl s = ColorDbl();
		Direction normal;
		Vertex LightPoint;
		double Tlenght = tri.IntersectionPoint.Distance(r.StartingPoint);

		if (scene.LightIntersection(r,LightPoint)) {
		
		}

		//If first intersection is with a triangle: if hitTriangle exists
		if (tri.rayIntersection(r,tri.IntersectionPoint))
		{
			normal = tri.normal;
			s = tri.color;
			return s;
		}
		return  s;
	}

	void render(Scene& scene) { //WHat tha fuck is this

		Ray r;
		ColorDbl Color;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(-0.5, 0.5);
		float param_y = 0, param_z = 0;
		int Samples = 1;

		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				param_y = dis(gen);
				param_z = dis(gen);
	
				Vertex px = Vertex(0.0f, -1.0f + ((double)i) * pixelSize, -1.0f + ( (double)j) * pixelSize, 1.0f);

				for (int k = 0; k < Samples; k++) {
					px.pos.y += param_y * pixelSize;
					px.pos.z += param_z * pixelSize;

			
					Vertex ps = Eyes[CameraSwap];
					glm::vec3 D = glm::normalize(px - ps);
		
					Vertex pe = ps + D;

					Ray ray = Ray(ps, Direction(pe - ps));

					Color = CastRay(ray, scene, 0, ColorDbl());

					pixels[j][i].GetNewColor(Color);


				}
				
			}
			
			std::cout << (double)i / HEIGHT * 100.0 << "%" << std::endl;
		}
		
	}



	Scene* scene;
	const double Trunc = 255.99;
	const int HEIGHT = 800;
	const int WIDTH = 800;

	Pixel** pixels = new Pixel * [HEIGHT];
	const double pixelSize = 0.0025;
	Light LightSource;
	glm::vec3 pos;
	double max = 0.0;
	int CameraSwap = 0;




	Vertex Eyes[2]{
		Vertex(-1.5, 0, 0, 0),
		Vertex(-1, 0, 0, 0)
	};
		
	Vertex c1 = Vertex(0, -1, -1, 0);
	Vertex c2 = Vertex(0, 1, -1, 0);
	Vertex c3 = Vertex(0, 1, 1, 0);
	Vertex c4 = Vertex(0,- 1, 1, 0);
};