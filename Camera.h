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

	ColorDbl CastRay(Ray r, Scene& scene, int depth,int Bounces) {

	
		int Max_Depth = 3;
		std::list<IntersectionPointTri> intersections = scene.DetectTriangel(r);
		std::list<IntersectionPointSphere> intersectionsS = scene.DetectSphere(r);

		ColorDbl s = ColorDbl();
		double TriangleDist = 100;
		double SphereDist = 100;

		glm::vec3 SphereHit = scene.sphere.rayIntersection(r, scene.sphere.t);
		
		if (Bounces > 3) {
			return ColorDbl(1,1,1);
		}

		//direction = target - currentLocation
		if (intersections.size() > 0){
			TriangleDist = glm::distance(intersections.front().point, r.StartingPoint.pos);
		}

		SphereDist = scene.sphere.t;

		if (SphereDist < TriangleDist && SphereDist >Epsilon) {
			if (scene.sphere.material.Id == Specular) {

				glm::vec3 normal = scene.sphere.get_normal(SphereHit);
				glm::vec3 Point = SphereHit + glm::vec3(normal.x * 0.01, normal.y * 0.01, normal.z * 0.01);

				Ray L = Ray(glm::vec3(5, 0, -4.9),Point);

				Direction Dirout = GetPerfectReflection(L, normal);
				
				Ray Out = Ray(Point, Dirout);
			
				//return CastRay(Out, scene, depth, Bounces+1);
				

			}
			if (scene.sphere.material.Id == Lambertian) {
				return scene.sphere.material.color;

			}
			if (scene.sphere.material.Id == 4) {
				glm::vec3 normal = scene.sphere.get_normal(SphereHit);
				glm::vec3 Point = SphereHit + glm::vec3(normal.x * 0.01, normal.y * 0.01, normal.z * 0.01);

				Ray L = Ray(glm::vec3(5, 0, -4.9), Point);

				Direction Dirout = GetPerfectReflection(L, normal);

				Ray Out = Ray(Point, Dirout);

				Direction Dout = Direction(scene.sphere.material.GetBRDF(Point, 4, L.direction.Vec, Out.direction.Vec, normal));
				//std::cout << Dout << std::endl;
				Out = Ray(Point, Dout);
				if (depth < Max_Depth) {
					return CastRay(Out, scene, depth, Bounces + 1) * 0.8;
					//std::cout << s << std::endl;
				}
			}
		}
		

		
		else {
			for (auto& intersection : intersections) {

				Triangle tri = intersection.Tri;
				
				
				if (tri.material.Id == 2) {

					s = scene.light.GetEmission();

				}
				else if (tri.material.Id == 1) {

					glm::vec3 normal = tri.normal.Vec;
					glm::vec3 Point = tri.IntersectionPoint.pos + glm::vec3(normal.x * 0.001, normal.y * 0.001, normal.z * 0.001);

					Ray L = Ray(glm::vec3(5,0,-4.9), Point);
			
					Direction Dirout = GetPerfectReflection(L,normal);

					Ray Out = Ray(Point, Dirout);

					if (depth < Max_Depth) {

						s += CastRay(Out, scene, depth, Bounces);

					}
					
				}
				else if(tri.material.Id == 0) {
					
					glm::vec3 normal = tri.normal.Vec;
					glm::vec3 Point = tri.IntersectionPoint.pos + glm::vec3(normal.x * 0.001, normal.y * 0.001, normal.z * 0.001);


					Ray L = Ray(glm::vec3(5, 0, -4.9), Point);

					Ray out = L.GetReflectedRay(L, normal, Point);

					ColorDbl lightContribution = scene.light.GetEmission();
					ColorDbl Lambertian = tri.material.GetBRDF(Point, 0, L.direction.Vec, out.direction.Vec, normal);

					double random = ((double) rand() / (RAND_MAX));
					double rrTop = std::max(std::max(Lambertian.r, Lambertian.g), Lambertian.b);

					s = tri.material.color;
					if (depth < Max_Depth|| random < rrTop) {

						s = CastRay(out, scene, depth + 1, Bounces);
					}

					s = s / Max_Depth;
				
					ColorDbl Color = Lambertian * lightContribution * std::max(0.0f, glm::dot(-L.direction.Vec, normal));

					ColorDbl DirectLight = SendShadowRays(scene, L, Point);

					s = s+ Color* DirectLight;
					
				}
				else if (tri.material.Id == 3) {
					glm::vec3 normal = tri.normal.Vec;
					glm::vec3 Point = tri.IntersectionPoint.pos + glm::vec3(normal.x * 0.001, normal.y * 0.001, normal.z * 0.001);


					Ray L = Ray(glm::vec3(5, 0, -4.9), Point);

					Ray out = L.GetReflectedRay(L, normal, Point);

					ColorDbl Oren = tri.material.GetBRDF(Point, tri.material.Id, L.direction.Vec, out.direction.Vec, normal);
				
					s = tri.material.color;
					if (depth < Max_Depth) {

						s += CastRay(out, scene, depth + 1, Bounces);
					}

					s = s / Max_Depth;

					glm::vec3 DirectLight = SendShadowRays(scene, L, Point);
					
					s = s+  Oren * scene.light.GetEmission()*DirectLight;
					
				}

			}
		}
		return  s;
	}

	Direction GetPerfectReflection(Ray& r, glm::vec3& normal) {
		glm::vec3 Reflection = r.direction.Vec - 2 * (glm::dot(r.direction.Vec, normal)) * normal;
		Direction R = Direction(Reflection);
		return R;
	}

	glm::vec3 SendShadowRays(Scene &scene,Ray &RayOut, glm::vec3& point) {

		Ray light = Ray(point, glm::vec3(-5, 0, -4.9));
		glm::vec3 Color = glm::vec3(1,1,1);
	//	RayOut.direction.Vec = -RayOut.direction.Vec;
		glm::vec3 SphereHit = scene.sphere.rayIntersection(light, scene.sphere.t);
		
		std::list<IntersectionPointTri> intersections = scene.DetectTriangel(light);
		std::list<IntersectionPointSphere> intersectionsS = scene.DetectSphere(light);

		Triangle tri = intersections.front().Tri;
		Sphere sph = intersectionsS.front().sphere;
		float distToLight = glm::distance(glm::vec3(-5, 0, -4.9), point);

		for (auto& intersection : intersections) {
			if (intersection.Tri.rayIntersection(light,intersection.point) && intersections.size() > 2) {
				
				Color = glm::vec3(0, 0, 0);
			}
		}
		for (auto& intersection : intersectionsS) {
			double SDist = glm::distance(intersection.sphere.Ip.pos, point);
			if (SDist < distToLight) {
			
			//	Color = glm::vec3(0, 0, 0);
			}
		}
		


		return Color;
	}



	void render(Scene& scene) { //WHat tha fuck is this

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-0.5, 0.5);

		Ray r;
		ColorDbl Color;
		int Samples =2;																				//SAMPLES!!!!!!!!!!!!!!!!!!!!!!!!!!
		float p_y = 0, p_z = 0;
		Vertex StartPoint = Eyes[CameraSwap];
		glm::vec3 v;
		double c1StartY = c1.pos.y + pixelSize / 2;
		double c1StartZ = c1.pos.z + pixelSize / 2;

		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {

				glm::vec3 CameraPlane = glm::vec3(0.0f, c1StartY + ((double)i) * pixelSize, c1StartZ + ((double)j) * pixelSize);

				for (int k = 0; k < Samples; k++) {
					p_y = dis(gen);
					p_z = dis(gen);
					v = CameraPlane;
					v.y += p_y * pixelSize;
					v.z += p_z * pixelSize;

					Ray ray = Ray(StartPoint, CameraPlane);
					Color += CastRay(ray, scene, 0, 0);
				}
				Color = Color / (double)pow(Samples, 2);
				pixels[j][i].GetNewColor(Color);
			}

			std::cout << (double)i / HEIGHT * 100 << "%" << std::endl;
		}

	}

	double Epsilon = 0.8;
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