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



int main() {

	Scene S;
	Light L(5,0,5,ColorDbl(1,1,1));
	Tetrahedron tetra(0.0, 0, -1.0,ColorDbl(0,1,1));
	S.AddTethra(tetra);
	S.AddLight(L);
	Camera C;

	C.SwapCamera(0);
	C.render(S);
	C.CreateImage();

   return 0;
}