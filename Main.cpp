#include <iostream>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Camera.h"
#include "Ray.h"
#include "ColorDbl.h"
#include "Direction.h"
#include "Tetrahedron.h"
#include "Sphere.h"


int main() {
	
	Scene S;
	Light L(1, 0, -4.9, ColorDbl(1, 1, 1));
	Tetrahedron tetra(8, 3,4.99, ColorDbl(0, 1, 1));
	S.addSphere(1, glm::vec3(5,-2, 0));
	S.AddTethra(tetra);
	S.AddLight(L);
	Camera C;

	C.SwapCamera(1);
	C.render(S);
	C.CreateImage();

   return 0;
}