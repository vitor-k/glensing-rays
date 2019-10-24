// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "v3d.h"


//Sphere

class Sphere {
public:
	v3d center;
	float radius;
	Sphere(v3d center, float radius) : center(center), radius(radius) {}
	bool intersect(const v3d& origin, const v3d& ray){//, v3d& intersection) {
		v3d v = origin - center;
		const float b = 2 * v.dot(ray);
		const float c = v.dot(v) - radius*radius;
		const float delta = b*b - 4 * c;
		if (delta < 0) return false;

		//const float t1 = (-b - sqrt(delta)) / 2;
		//const float t2 = (-b - sqrt(delta)) / 2;

		//intersection = (t1 < t2) ? (center + t1*ray) : (center + t2*ray);

		return true;
	}
};


class RayTracerEngine : public olc::PixelGameEngine {
public:
	RayTracerEngine() { sAppName = "Ray Caster"; }
public:
	v3d cameraOrigin = v3d(0,0,0);
	v3d cameraDirection = v3d(1,0,0); //X
	v3d cameraParallel = v3d(0,0,0);  //Y
	v3d cameraUp = v3d(0,0,1);        //Z

	std::vector<Sphere> esferas = std::vector<Sphere>({Sphere(v3d(3,0,0), 1)});

	//float FOV = 90.;
	float unitsPerPixel = 0.004;

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
		v3d rayDirection = cameraDirection + (cameraParallel * (x * unitsPerPixel)) + (cameraUp * (y * unitsPerPixel));
		if (esferas[0].intersect(cameraOrigin, rayDirection.normalized())) return olc::Pixel(0, 255, 255);
		else return olc::Pixel(0,0,0);
	}
};

int main()
{
	RayTracerEngine demo;
	if (demo.Construct(200, 200, 4, 4)) demo.Start();
	//Sphere bla = Sphere(2.1, 6.8);
	//std::cout << bla.radius << std::endl;
	v3d bla = v3d(0.1, 0.3, 0.1);
	bla * 3.1;
	bla * 3;
	3.1 * bla;
	bla / int(3);
	std::cout << (3 * bla).norm();

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
