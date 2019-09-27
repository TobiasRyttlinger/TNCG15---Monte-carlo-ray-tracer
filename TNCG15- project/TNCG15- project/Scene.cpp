
#include "Scene.h"
#include "Triangle.h"
#include "Vertex.h"
#include <glm/glm.hpp>

Scene::Scene() {
	createScene();
}

void Scene::createScene() {
	Vertex p1Floor(-3.0, 0.0, -5.0, 1.0);
	Vertex p1Roof(-3.0, 0.0, 5.0, 1.0);

	Vertex p2Floor(0.0, 6.0, -5.0, 1.0);
	Vertex p2Roof(0.0, 6.0, 5.0, 1.0);

	Vertex p3Floor(10.0, 6.0, -5.0, 1.0);
	Vertex p3Roof(10.0, 6.0, 5.0, 1.0);

	Vertex p4Floor(13.0, 0.0, -5.0, 1.0);
	Vertex p4Roof(13.0, 0.0, 5.0, 1.0);

	Vertex p5Floor(10.0, -6.0, -5.0, 1.0);
	Vertex p5Roof(10.0, -6.0, 5.0, 1.0);

	Vertex p6Floor(0.0, -6.0, -5.0, 1.0);
	Vertex p6Roof(0.0, -6.0, 5.0, 1.0);

	Vertex MidFloor(5.0, 0.0, -5.0, 1.0);
	Vertex MidRoof(5.0, 0.0, 5.0, 1.0);


	
	Triangle T1Floor(p1Floor, p6Floor, MidFloor);
	Triangle T2Floor(p1Floor, p2Floor, MidFloor);
	Triangle T3Floor(p2Floor, p3Floor, MidFloor);
	Triangle T4Floor(p3Floor, p4Floor, MidFloor);
	Triangle T5Floor(p4Floor, p5Floor, MidFloor);
	Triangle T6Floor(p5Floor, p6Floor, MidFloor);

	Triangle T1Wall(p1Floor, p1Floor, p2Floor);
	Triangle T2Wall(p1Roof, p2Roof, p2Floor);

	Triangle T3Wall(p2Roof, p2Floor, p3Roof);
	Triangle T4Wall(p2Floor, p3Roof, p3Floor);

	Triangle T5Wall(p3Roof, p2Floor, p3Floor);
	Triangle T6Wall(p3Roof, p4Roof, p4Floor);





}