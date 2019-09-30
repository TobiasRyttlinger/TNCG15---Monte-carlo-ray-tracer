#include <iostream>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Camera.h"
#include "Ray.h"
#include "Direction.h"


int main() {

	Scene S;

	Camera C = Camera(1, 2, 5);

   C.render(S);
   C.CreateImage();

   return 0;
}