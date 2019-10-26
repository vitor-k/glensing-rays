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
	bool intersect(const v3d& origin, const v3d& rayDirection, v3d& intersection, v3d& normal) const{
		v3d v = origin - center;
		const float b = 2 * v.dot(rayDirection);
		const float c = v.norm2() - radius*radius;
		const float delta = b*b - 4 * c;
		if (delta < 0) return false;

		const float t1 = (-b - sqrt(delta)) / 2;

		if (t1<0) return false;

		intersection = origin + t1*rayDirection;

		normal = intersection - center;
		normal.normalize();

		return true;
	}
};


class RayTracerEngine : public olc::PixelGameEngine {
public:
	RayTracerEngine() {
		sAppName = "Ray Caster";
		cameraParallel = cameraUp.cross(cameraDirection);
	}
public:
	v3d cameraOrigin = v3d(0,0,0);
	v3d cameraDirection = v3d(1,0,0); //X
	v3d cameraParallel;               //Y
	v3d cameraUp = v3d(0,0,1);        //Z

	std::vector<Sphere> sceneObjects = std::vector<Sphere>({Sphere(v3d(10,6,0), 1) , Sphere(v3d(10,0,0), 3)});

	//float FOV = 90.;
	const float unitsPerPixel = 0.002;

	bool OnUserCreate() override {
		return true;
	}
	float totalTime = 0;
	bool OnUserUpdate(float fElapsedTime) override {
		totalTime += fElapsedTime;
		sceneObjects[0].center.x = 10 + 6 *cos(1 * totalTime);
		sceneObjects[0].center.y = 6 * sin(1 * totalTime);
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
		rayDirection.normalize();

		return nTrace(cameraOrigin, rayDirection, 0);
	}

	olc::Pixel nTrace(v3d& rayOrigin, v3d& rayDirection, int rayNumber) {
		if (rayNumber > 6) return background(rayDirection);//olc::Pixel(0,0,0);

		bool intersects = false;

		v3d intersection;
		v3d normal;

		float distanceOfIntersection;
		v3d newRayOrigin;
		v3d reflectionNormal;

		for (std::vector<Sphere>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
			if ((*it).intersect(rayOrigin, rayDirection, intersection, normal)) {
				if (!intersects) {
					distanceOfIntersection = (rayOrigin-intersection).norm();
					newRayOrigin = intersection;
					reflectionNormal = normal;
					intersects = true;
				}
				else {
					float temDistance = (rayOrigin-intersection).norm();
					if (temDistance < distanceOfIntersection) {
						distanceOfIntersection = (rayOrigin-intersection).norm();
						newRayOrigin = intersection;
						reflectionNormal = normal;
					}
				}
			}
		
		}
		
		if (intersects) {
			//float normalCorrection = sqrt(abs(rayDirection.dot(reflectionNormal)));

			rayDirection = rayDirection - 2 * dot(rayDirection, reflectionNormal) * reflectionNormal;

			olc::Pixel pix = nTrace(newRayOrigin, rayDirection, rayNumber+1);

			//pix.r *= normalCorrection;
			//pix.g *= normalCorrection;
			//pix.b *= normalCorrection;

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
}
