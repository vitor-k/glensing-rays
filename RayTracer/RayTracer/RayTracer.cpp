// Ray tracer engine, using the olcGameEngine, from One Lone Coder

#include <iostream>
#include <vector>
#include <cmath>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "v3d.h"
#include "Sphere.h"
#include "GravitationalEntity.h"


class RayTracerEngine : public olc::PixelGameEngine {
public:
	RayTracerEngine() {
		sAppName = "Ray Caster";
		cameraParallel = cameraUp.cross(cameraDirection);
	}
public:
	v3d cameraOrigin = v3d(-3,0,0);    //    Origin of the rays of the camera
	v3d cameraDirection = v3d(1,0,0); //X - Direction the camera is pointing
	v3d cameraParallel;               //Y - Normal to the other vectors and parallel to the image plane
	v3d cameraUp = v3d(0,0,1);        //Z - Defines the upside of the camera #3db7ef

	std::vector<Sphere*> sceneObjects = std::vector<Sphere*>({new CoolSphere(v3d(10,6,0), 1) ,
															  new OpaqueSphere(v3d(10,6,0), 1, 60,190,240) ,
															  new MirroredSphere(v3d(10,0,0), 3) ,
															  new AtmoSphere(v3d(10,-6,0), 2, 100,50,10, 200,200,255)}); // Objects in the scene

	//float FOV = 90.;
	const float unitsPerPixel = 0.0025; //Defines the FOV, TODO: stop making it pixel amount dependent

	bool OnUserCreate() override {
		return true;
	}

	float totalTime = 0;

	bool OnUserUpdate(float fElapsedTime) override {
		totalTime += fElapsedTime;
		sceneObjects[0]->center.x = 10 + 8 *cos(1 * totalTime) + 2 * sin(3*totalTime);
		sceneObjects[0]->center.y = 8 * sin(1 * totalTime) + 2 * cos(3*totalTime);
		sceneObjects[1]->center.x = 10 + 8 *cos(1 * totalTime) + 2 * cos(3*totalTime);
		sceneObjects[1]->center.y = 8 * sin(1 * totalTime) - 2 * sin(3*totalTime);
		sceneObjects[3]->center.x = 10 - 8 *cos(1 * totalTime);
		sceneObjects[3]->center.y =-8 * sin(1 * totalTime);
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
		v3d closestIntersection;
		v3d intersectionNormal;
		Sphere *intersectedObject = NULL;

		for (std::vector<Sphere*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
			if ((*it)->intersect(rayOrigin, rayDirection, intersection, normal)) {
				if (!intersects) {
					distanceOfIntersection = (rayOrigin-intersection).norm();
					closestIntersection = intersection;
					intersectionNormal = normal;
					intersectedObject = *it;
					intersects = true;
				}
				else {
					float temDistance = (rayOrigin-intersection).norm();
					if (temDistance < distanceOfIntersection) {
						distanceOfIntersection = (rayOrigin-intersection).norm();
						closestIntersection = intersection;
						intersectionNormal = normal;
						intersectedObject = *it;
					}
				}
			}
		
		}
		if (intersects) {
			olc::Pixel pix;

			if (intersectedObject->response(rayDirection, closestIntersection, intersectionNormal, pix)) {
				return pix;
			} else {
				return nTrace(closestIntersection, rayDirection, rayNumber+1);
			}
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
