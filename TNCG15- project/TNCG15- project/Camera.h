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
#include "Surface.h"
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0, 1);
	float rand = dis(gen);

	Triangle tri = scene.DetectTriangel(r).Tri;

	ColorDbl s = ColorDbl();
	ColorDbl indirectLight = ColorDbl();
	//std::cout << tri.IntersectionPoint << std::endl;

	if (tri.rayIntersection(r, tri.IntersectionPoint))
	{
		
		double Tlenght = tri.Tout;

		if (scene.sphere.rayIntersection(r, scene.sphere.t)) {
			
			if (scene.sphere.t < Tlenght) {

				if (scene.sphere.material.Id == Specular) {
				
					Sphere sphere = scene.sphere;
					glm::vec3 normal = sphere.get_normal(sphere.Ip.pos);
					glm::vec3 Bias = glm::vec3(normal.x * Epsilon, normal.y * Epsilon, normal.z * Epsilon);
					glm::vec3 Point = sphere.Ip.pos + Bias;
					
					Direction LightDir = Direction(scene.light.getRandomPointOnLight().pos - Point);
					Ray Light = Ray(Eyes[CameraSwap], LightDir);
					Ray ReflectedRay = Light.GetPerfectReflection(Light, normal, Point);
					s += CastRay(ReflectedRay, scene, depth, importance) * 0.8;
					return s;

				}
				
			}
		}

		if (tri.material.Id == Lightsource) {
			return scene.light.GetEmission();
		}

		if (tri.material.Id == Specular) {
				Vertex Point = (tri.IntersectionPoint + Vertex((tri.normal * Epsilon).Vec, 0)); //Bias
	
			//	Ray ReflectedDir = r.GetPerfectReflection(r, tri.normal, Point.pos);
				//s += CastRay(ReflectedDir, scene, depth, ColorDbl(1, 1, 1)) * 0.8;
				return s;

		}

	
			if (tri.material.Id == Lambertian) {
				//if (scene.SendShadowRays(scene.light, r, tri.IntersectionPoint, tri.normal)) {
				glm::vec3 Point;
				Direction normal = tri.normal;

				if (tri.normal.Vec.x == 0 && tri.normal.Vec.y == 1 && tri.normal.Vec.z == 0) {
					tri.normal.Vec.z = 0;
					Point = tri.IntersectionPoint.pos - (normal*Epsilon).Vec;
				}
				else {
					Point = tri.IntersectionPoint.pos + (normal* Epsilon).Vec;
				}

				Ray L = Ray(scene.light.getRandomPointOnLight(), Vertex(Point, 0));

				Ray out = L.GetReflectedRay(L, tri.normal, Point);

				double angle = glm::angle(L.direction.Vec, normal.Vec);

				ColorDbl emittance = tri.material.color;
				ColorDbl lightContribution = scene.light.GetEmission();

				double rand = dis(gen);

				s += tri.material.color;
				int Max_Depth = 1;
				if (depth < Max_Depth) {

					//s += CastRay(out, scene, depth + 1, importance);
				}
				s = s / Max_Depth;
				return s + tri.material.color * (lightContribution) * std::max(0.0f, glm::dot(-L.direction.Vec, normal.Vec));
				//}

				return ColorDbl(0, 0, 0);
			}
	
		}
		
		return  s;
}

	void render(Scene& scene) { //WHat tha fuck is this

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(-0.5, 0.5);

		Ray r;
		ColorDbl Color;
		int Samples =4;
		float p_y = 0, p_z = 0;
		Vertex StartPoint = Eyes[CameraSwap];
		Vertex v;
		double c1StartY = c1.pos.y + pixelSize/2;
		double c1StartZ = c1.pos.z + pixelSize/2;

		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {

				Vertex CameraPlane = Vertex(0.0f, c1StartY + ((double)i) * pixelSize, c1StartZ + ((double)j) * pixelSize, 1.0f);

				for (int k = 0; k < Samples; k++) {
					p_y = dis(gen);
					p_z = dis(gen);
					v = CameraPlane;
					v.pos.y += p_y * pixelSize;
					v.pos.z += p_z * pixelSize;

					Ray ray = Ray(StartPoint,v);
					Color += CastRay(ray, scene, 0, ColorDbl(1,1,1));
				}
				Color = Color / (double)pow(Samples,2);
				pixels[j][i].GetNewColor(Color);
			}

			std::cout << (double)i/HEIGHT*100 << "%" << std::endl;
		}

	}

	 double Epsilon = 0.1;
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
	int Lambertian = 0;
	int Specular = 1;
	int Lightsource = 2;

	Vertex Eyes[2]{
		Vertex(-2, 0, 0, 0),
		Vertex(-1, 0, 0, 0)
	};

	Vertex c1 = Vertex(0, -1, -1, 0);
	Vertex c2 = Vertex(0, 1, -1, 0);
	Vertex c3 = Vertex(0, 1, 1, 0);
	Vertex c4 = Vertex(0, -1, 1, 0);
};