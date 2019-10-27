// Ray tracer engine, using the olcGameEngine, from One Lone Coder

#include <iostream>
#include <vector>
#include <cmath>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "v3d.h"


//Mirrored Sphere

class Sphere {
public:
	v3d center;
	float radius;
	Sphere(v3d center, float radius) : center(center), radius(radius) {}

	bool intersect(const v3d& rayorigin, const v3d& rayDirection, v3d& intersection, v3d& normal) const{
		// Based on the code in medium.com/farouk-ounanes-home-on-the-internet/ray-tracer-in-c-from-scratch-e013269884b6
		v3d v = rayorigin - center;
		const float b = 2 * v.dot(rayDirection);
		const float c = v.norm2() - radius*radius;
		const float delta = b*b - 4 * c;

		if (delta < 0) return false; // If delta is negative, the ray doesn`t intersect 

		const float t = (-b - sqrt(delta)) / 2;

		if (t<0) return false; // If t is negative, the ray intersects before the ray origin

		intersection = rayorigin + t*rayDirection;

		normal = (intersection - center) / radius; // Normal vector to the surface in the intersection

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
	v3d cameraOrigin = v3d(0,0,0);    //    Origin of the rays of the camera
	v3d cameraDirection = v3d(1,0,0); //X - Direction the camera is pointing
	v3d cameraParallel;               //Y - Normal to the other vectors and parallel to the image plane
	v3d cameraUp = v3d(0,0,1);        //Z - Defines the upside of the camera

	std::vector<Sphere> sceneObjects = std::vector<Sphere>({Sphere(v3d(10,6,0), 1) , Sphere(v3d(10,6,0), 1) , Sphere(v3d(10,0,0), 3)}); // Objects in the scene

	//float FOV = 90.;
	const float unitsPerPixel = 0.0025; //Defines the FOV, TODO: stop making it pixel dependent

	bool OnUserCreate() override {
		return true;
	}

	float totalTime = 0;

	bool OnUserUpdate(float fElapsedTime) override {
		totalTime += fElapsedTime;
		sceneObjects[0].center.x = 10 + 8 *cos(1 * totalTime) + 2 * sin(3*totalTime);
		sceneObjects[0].center.y = 8 * sin(1 * totalTime) + 2 * cos(3*totalTime);
		sceneObjects[1].center.x = 10 + 8 *cos(1 * totalTime) + 2 * cos(3*totalTime);
		sceneObjects[1].center.y = 8 * sin(1 * totalTime) - 2 * sin(3*totalTime);
		int32_t width = ScreenWidth();
		int32_t height = ScreenHeight();
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++){
				Draw(x, y, inicialTrace(x - width/2, y - height / 2));
			}
		return true;
	}

	olc::Pixel inicialTrace(int32_t planeX, int32_t planeY) {
		v3d rayDirection = cameraDirection + (cameraParallel * (planeX * unitsPerPixel)) + (cameraUp * (planeY * unitsPerPixel));
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
