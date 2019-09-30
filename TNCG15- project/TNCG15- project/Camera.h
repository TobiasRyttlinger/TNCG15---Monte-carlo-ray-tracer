#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "Pixel.h"
#include <vector>
#include <new>
#include <algorithm>


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
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				std::cout << pixels[i][j].color.r << std::endl;
			}
		}
		std::cout << "Done!!"<< std::endl;
	}


	void SwapCamera(int choice) {
		if (choice <= 0) {
			CameraSwap = 0;
		}
		else if (choice >= 1) {
			CameraSwap = 1;
		}
	}



	void render() {

	}


	void createImage() {


	}

	const int HEIGHT = 800;
	const int WIDTH = 800;
	Pixel** pixels = new Pixel * [HEIGHT];
	const double pixelSize = 0.0025;
	glm::vec3 pos;
	double max = 0.0;
	int CameraSwap = 0;
	Vertex Eye1 = Vertex(-2, 0, 0);
	Vertex Eye2 = Vertex(-1, 0, 0);

};