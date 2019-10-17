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
	//Tetrahedron tetra(-5, 0, 0.0, ColorDbl(0, 1, 1));
	//S.addSphere(0.1, glm::vec3(8,0, 1));
	//S.AddTethra(tetra);
	S.AddLight(L);
	Camera C;

	C.SwapCamera(1);
	C.render(S);
	C.CreateImage();

   return 0;
}