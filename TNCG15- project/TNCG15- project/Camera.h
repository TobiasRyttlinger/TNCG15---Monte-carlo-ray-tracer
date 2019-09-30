#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "Pixel.h"
#include <vector>
#include <new>
#include <algorithm>
#include <fstream>  
#include "Ray.h"
#include "ColorDbl.h"
struct Camera {

	Camera() : pos(glm::vec3(0.0, 0.0, 0.0)) {}

	Camera(float xIn, float yIn, float zIn) {
		pos.x = xIn;
		pos.y = yIn;
		pos.z = zIn;

		for (int i = 0; i < WIDTH; i++) {
			pixels[i] = new Pixel[WIDTH];
			for (int j = 0; j < HEIGHT; j++) {
				pixels[i][j] = Pixel();

			}
		}

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



	void render(Scene& scene) {
		Ray r;
		const int SubPixels = 2;

		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				ColorDbl NewColor;
				double Y = pixelSize/2+i*pixelSize;
				double Z = pixelSize/2+j*pixelSize;

				for (int k = 0; k < SubPixels; ++k) {
					for (int m = 0; m < SubPixels; ++m) {
						Vertex SubpixArray = Vertex(0.0, Y - (m * pixelSize), Z - (k * pixelSize), 0.0);
						r = Ray(Eyes[CameraSwap], SubpixArray);
						//NewColor += CastRay(temp, scene, 0, ColorDbl(1.0, 1.0, 1.0));
					}
				}


					pixels[i][j].color = NewColor;	

			}
		}

	}


	const double Trunc = 255.99;
	const int HEIGHT = 800;
	const int WIDTH = 800;
	Pixel** pixels = new Pixel * [HEIGHT];
	const double pixelSize = 0.0025;
	glm::vec3 pos;
	double max = 0.0;
	int CameraSwap = 0;
	Vertex Eyes[2]{
		Vertex(-2, 0, 0, 0),
		Vertex(-1, 0, 0, 0) };
		
	Vertex c1 = Vertex(0, -1, -1, 0);
	Vertex c2 = Vertex(0, 1, -1, 0);
	Vertex c3 = Vertex(0, 1, 1, 0);
	Vertex c4 = Vertex(0,- 1, 1, 0);
		

};