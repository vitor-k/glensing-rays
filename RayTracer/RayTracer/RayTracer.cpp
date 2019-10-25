// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "v3d.h"


//Sphere

class Sphere {
public:
	v3d center;
	float radius;
	Sphere(v3d center, float radius) : center(center), radius(radius) {}
	bool intersect(const v3d& origin, const v3d& ray, v3d& intersection, v3d& normal) const{
		v3d v = origin - center;
		const float b = 2 * v.dot(ray);
		const float c = v.norm2() - radius*radius;
		const float delta = b*b - 4 * c;
		if (delta < 0) return false;

		const float t1 = (-b - sqrt(delta)) / 2;

		if (t1<0) return false;

		intersection = origin + t1*ray;

		normal = intersection - center;
		normal.normalize();

		return true;
	}
};


class RayTracerEngine : public olc::PixelGameEngine {
public:
	RayTracerEngine() : cameraOrigin({ 0,0,0 }), cameraDirection({ 1,0,0 }), cameraUp({ 0,0,1 }) {
		sAppName = "Ray Caster"; 
	}
public:
	const v3d cameraOrigin;
	const v3d cameraDirection;
	v3d cameraParallel = v3d(0,0,0);  //Y
	const v3d cameraUp;

	std::vector<Sphere> esferas = std::vector<Sphere>({Sphere(v3d(3,0,0), 1)});

	//float FOV = 90.;
	const float unitsPerPixel = 0.001;

	bool OnUserCreate() override {
		cameraParallel = cameraUp.cross(cameraDirection);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		int32_t width = ScreenWidth();
		int32_t height = ScreenHeight();
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++){
				Draw(x, y, inicialTrace(x - width/2, y - height / 2));
			}
		return true;
	}

	olc::Pixel inicialTrace(int32_t x, int32_t y) {
		//std::cout << fElapsedTime << std::endl;
		v3d rayDirection = cameraDirection + (cameraParallel * (x * unitsPerPixel)) + (cameraUp * (y * unitsPerPixel));
		rayDirection.normalize();

		v3d intersection = v3d(0,0,0);
		v3d normal = v3d(0,0,0);

		if (esferas[0].intersect(cameraOrigin, rayDirection, intersection, normal)) {
			float bla = sqrt(abs(rayDirection.dot(normal)));
			olc::Pixel pix = background((rayDirection - 2 * dot(rayDirection, normal) * normal).normalized());
			pix.r *= bla;
			pix.g *= bla;
			pix.b *= bla;
			return pix;
		}
		else return background(rayDirection);
	}

	inline olc::Pixel background(v3d direction) const{
		return olc::Pixel(125 + 125*direction.x, 125 + 125*direction.y, 125 + 125*direction.z);
	}
};

int main()
{
	RayTracerEngine demo;
	if (demo.Construct(800, 800, 1, 1)) demo.Start();
	//Sphere bla = Sphere(2.1, 6.8);
	//std::cout << bla.radius << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
