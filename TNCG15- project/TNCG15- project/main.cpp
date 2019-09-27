#include <iostream>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Camera.h"

int main(int argc, char** argv) {

	Scene S;
	//S.createScene();
	Camera C = Camera(1, 2, 5);
	C.CreateImage();






	return 0;
}