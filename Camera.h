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
		std::list<IntersectionPointTri> intersections = scene.Find_Triangle(r);
		std::list<IntersectionPointSphere> intersectionsS = scene.Find_sphere(r);

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

		if (SphereDist < TriangleDist && SphereDist >0.0000001) {
			if (scene.sphere.material.Id == Lambertian) {
				glm::vec3 normal = scene.sphere.get_normal(SphereHit);
				glm::vec3 Point = SphereHit;

				Ray L = Ray(scene.light.GetRandomPoint(), Point);

				Ray Out = L.GetReflectedRay(L, normal, Point);

				ColorDbl Lambertian = scene.sphere.material.GetBRDF(Point, scene.sphere.material.Id, L.direction.Vec, Out.direction.Vec, normal);


				double random = std::rand() / (double)(RAND_MAX);
				double RussianRoulett = std::max(std::max(Lambertian.r, Lambertian.g), Lambertian.b);
				
				if (depth < Max_Depth && random < RussianRoulett) {

					s += CastRay(Out, scene, depth + 1, Bounces);
				}

				s = s / Max_Depth;

				//		glm::vec3 DirectLight = SendShadowRays(scene, LightPoint, Point);

				s = s + Lambertian * std::max(0.0f, glm::dot(-L.direction.Vec, normal));


			}
			if (scene.sphere.material.Id == Specular) {

				glm::vec3 normal = scene.sphere.get_normal(SphereHit);
				glm::vec3 Point = SphereHit + normal * 0.000001f;

				Ray L = Ray(scene.light.GetRandomPoint(),Point);
				
				glm::vec3 Dirout = GetPerfectReflection(L, normal);
				
				Ray Out = Ray(Point, Dirout);
			
				return CastRay(Out, scene, depth, Bounces + 1)*0.8;
			}

			else if (scene.sphere.material.Id == Glass) {
				ColorDbl colorRefract = ColorDbl(0, 0, 0);
				ColorDbl colorReflect = ColorDbl(0, 0, 0);

				glm::vec3 normal = scene.sphere.get_normal(SphereHit);
				glm::vec3 Point = SphereHit;

				Ray L = Ray(scene.light.GetRandomPoint(), Point);

				glm::vec3 Dirout = GetPerfectReflection(L, normal);

				Ray Out = Ray(Point, Dirout);

				// compute fresnel
				float Fresnel;
				Get_Fresnel(L.direction.Vec, normal, Fresnel);
				bool outside = glm::dot(-L.direction.Vec,normal) < 0;
			
				glm::vec3 BIAS  =0.0001f * normal;

				if (Fresnel < 1) {

					if (outside) {
						Point = Point - BIAS;
					}
					else {
						Point = Point + BIAS;
					}

					glm::vec3 refractionDirection = scene.sphere.material.GetBRDF(Point, 4, L.direction.Vec, Out.direction.Vec, normal); 

					Ray out = Ray(Point,refractionDirection);

					colorRefract = CastRay(out, scene, depth , Bounces+1);
					
				}

				glm::vec3 reflectionDirection = GetPerfectReflection(L, normal);
				if (outside) {
					Point = Point + BIAS;
				}
				else {
					Point = Point - BIAS;
				}

				Ray out = Ray(Point, reflectionDirection);

				colorReflect = CastRay(out, scene, depth , Bounces + 1);

				s = colorReflect * Fresnel + colorRefract * (1- (double)Fresnel);
			}
			else if (scene.sphere.material.Id == 3) {

				glm::vec3 normal = scene.sphere.get_normal(SphereHit);
				glm::vec3 Point = SphereHit;

				Ray L = Ray(scene.light.GetRandomPoint(), Point);

				Ray Out = L.GetReflectedRay(L, normal, Point);

				ColorDbl Oren = scene.sphere.material.GetBRDF(Point, scene.sphere.material.Id, L.direction.Vec, Out.direction.Vec, normal);

				double random = std::rand() / (double)(RAND_MAX);
				double RussianRoulett = std::max(std::max(Oren.r, Oren.g), Oren.b);

				if (depth < Max_Depth && random < RussianRoulett) {

					s += CastRay(Out, scene, depth + 1, Bounces);
				}

				ColorDbl Color = Oren * scene.light.GetEmission() * std::max(0.0f, glm::dot(L.direction.Vec, normal));
				s = s / Max_Depth;
				s = s + Color;

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
					glm::vec3 Point = tri.IntersectionPoint.pos + normal * 0.0001f;

					Ray L = Ray(glm::vec3(5,0,-4.9), Point);
			
					Direction Dirout = GetPerfectReflection(L,normal);

					Ray Out = Ray(Point, Dirout);

					if (depth < Max_Depth) {

						s += CastRay(Out, scene, depth, Bounces);

					}
					
				}

				else if(tri.material.Id == 0) {
					
					glm::vec3 normal = tri.normal.Vec;
					glm::vec3 Point = tri.IntersectionPoint.pos + normal * 0.0001f;
					glm::vec3 LightPoint = scene.light.GetRandomPoint();

					Ray L = Ray(Vertex(LightPoint,0), Point);

					Ray out = L.GetReflectedRay(L, normal, Point);

					ColorDbl lightContribution = scene.light.GetEmission();
					ColorDbl Lambertian = tri.material.GetBRDF(Point, 0, L.direction.Vec, out.direction.Vec, normal);

					double random = std::rand() / (double)(RAND_MAX);
					double RussianRoulett = std::max(std::max(Lambertian.r, Lambertian.g), Lambertian.b);
					s = Lambertian;
					if (depth < Max_Depth && random < RussianRoulett) {

						s += CastRay(out, scene, depth + 1, Bounces);
					}

					s = s / Max_Depth;
				
					ColorDbl Color = Lambertian * lightContribution * std::max(0.0f, glm::dot(-L.direction.Vec, normal));

					ColorDbl DirectLight = SendShadowRays(scene, LightPoint, Point);

					s = s+ Color * DirectLight;
					
				}

				else if (tri.material.Id == 3) {
					glm::vec3 normal = tri.normal.Vec;
					glm::vec3 Point = tri.IntersectionPoint.pos + normal * 0.01f;
					glm::vec3 LightPoint = scene.light.GetRandomPoint();
					
					Ray L = Ray(Vertex(LightPoint,0), Point);

					Ray out = L.GetReflectedRay(L, normal, Point);

					ColorDbl Oren = tri.material.GetBRDF(Point, tri.material.Id, L.direction.Vec, out.direction.Vec, normal);
			
					double random = std::rand() / (double)(RAND_MAX);
					double RussianRoulett = std::max(std::max(Oren.r, Oren.g), Oren.b);

				
					s = Oren;
					if (depth < Max_Depth && random < RussianRoulett ) {

						s = CastRay(out, scene, depth + 1, Bounces);
					}

					s = s / Max_Depth;
					
					ColorDbl Color = Oren * scene.light.GetEmission() * std::max(0.0f,glm::dot(-L.direction.Vec, normal));
					glm::vec3 DirectLight = SendShadowRays(scene, LightPoint, Point);
					
					s = s + Color * DirectLight;
					
				}

			}
		}
		return  s;
	}

	glm::vec3 GetPerfectReflection(Ray& r, glm::vec3& normal) {
		glm::vec3 Reflection = r.direction.Vec - 2 * (glm::dot(r.direction.Vec, normal)) * normal;
		glm::vec3 R = glm::normalize(Reflection);
		return R;
	}

	glm::vec3 SendShadowRays(Scene scene, glm::vec3 LightPoint, glm::vec3 point) {
		Vertex Sp = Vertex(point, 0);
		glm::vec3 Color = glm::vec3(1, 1, 1);
		
		glm::vec3 lP = glm::vec3(-LightPoint.x+1, LightPoint.y, LightPoint.z);

		Ray ShadowRay = Ray(Sp, lP);

		std::list<IntersectionPointTri> intersections = scene.Find_Triangle(ShadowRay);
		std::list<IntersectionPointSphere> intersectionsS = scene.Find_sphere(ShadowRay);
		
		glm::vec3 SphereHit = scene.sphere.rayIntersection(ShadowRay, scene.sphere.t);
	
		double lightDistance = glm::distance(point, lP);

		for (auto& intersection : intersections) {

			double intersectionDistance = glm::distance(point, intersection.point);

			if (intersectionDistance < lightDistance && intersections.size() > 2) {
				Color = glm::vec3(0, 0, 0);
			}
			if (SphereHit != glm::vec3(0,0,0)) {
				Color = glm::vec3(0, 0, 0);
			}
		}
			
		return Color;
	}

	void Get_Fresnel(const glm::vec3& In, const glm::vec3& normal, float& Fresnel) {

		float cos1 =glm::clamp(-1.0,1.0, (double)glm::dot(In, normal));

		float n1 = 1;
		float n2 = 1.5;

		if (cos1 > 0){
			std::swap(n1, n2);
		}
	
		double T_angle = n1 / n2 * sqrt(std::max(0.0, 1.0 - (double)glm::pow(cos1,2)));

		if (T_angle >= 1) {
			
			Fresnel = 1;
		}
		else {
			float cos2 = sqrt(std::max(0.0, 1 - glm::pow(T_angle,2)));
			cos1 = fabsf(cos1);
			float Rs = ((n2 * cos1) - (n1 * cos2)) / ((n2 * cos1) + (n1 * cos2));
			float Rp = ((n1 * cos1) - (n2 * cos2)) / ((n1 * cos1) + (n2 * cos2));
			Fresnel = (glm::pow(Rs, 2) +glm::pow(Rp,2)) / 2;
		}
	}

	void render(Scene& scene) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-0.5, 0.5);

		Ray r;
		ColorDbl Color;
		int Samples =32;
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

					Ray ray = Ray(StartPoint, v);
					Color += CastRay(ray, scene, 0, 0);
				}
				Color = Color / (double)pow(Samples, 2);
				pixels[j][i].GetNewColor(Color);
			}

			std::cout << (double)i / HEIGHT * 100 << "%" << std::endl;
		}

	}

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
	int Glass=4;

	Vertex Eyes[2]{
		Vertex(-2, 0, 0, 0),
		Vertex(-1, 0, 0, 0)
	};

	Vertex c1 = Vertex(0, -1, -1, 0);
	Vertex c2 = Vertex(0, 1, -1, 0);
	Vertex c3 = Vertex(0, 1, 1, 0);
	Vertex c4 = Vertex(0, -1, 1, 0);
};