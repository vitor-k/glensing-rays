// Ray tracer engine, using the olcGameEngine, from One Lone Coder

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "v3d.h"
#include "Sphere.h"
#include "GravitationalEntity.h"

const int nThreads=8;

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
															  //new MirroredSphere(v3d(10,0,0), 3) ,
															  new GravitationalEntity(v3d(10,0,0), 0.1, 3) /*,
															  new AtmoSphere(v3d(10,-6,0), 2, 100,50,10, 200,200,255)*/}); // Objects in the scene

	//float FOV = 90.;
	const float unitsPerPixel = 0.0025; //Defines the FOV, TODO: stop making it pixel amount dependent

	bool OnUserCreate() override {
		return true;
	}

	float totalTime = 0;

	void drawingThread(const int start, const int end, const int32_t width, const int32_t height, olc::Pixel* tela) const {
		for (int i = start; i < end; i++) {
			tela[i] = inicialTrace(i%width - width / 2, i/width - height / 2);
		}
	}
	void drawingThread2(const int offset, const int32_t width, const int32_t height, olc::Pixel* tela) const {
		for (int i = 0; i * nThreads + offset < width * height; i++) {
			tela[i*nThreads + offset] = inicialTrace((i * nThreads + offset) % width - width / 2, (i * nThreads + offset) / width - height / 2);
		}
	}
	bool OnUserUpdate(float fElapsedTime) override {
		totalTime += 0.1f;
		sceneObjects[0]->center.x = 10 + 8 *cos(1 * totalTime) + 2 * sin(3*totalTime);
		sceneObjects[0]->center.y = 8 * sin(1 * totalTime) + 2 * cos(3*totalTime);
		sceneObjects[1]->center.x = 10 + 8 *cos(1 * totalTime) + 2 * cos(3*totalTime);
		sceneObjects[1]->center.y = 8 * sin(1 * totalTime) - 2 * sin(3*totalTime);
		/*sceneObjects[3]->center.x = 10 - 8 *cos(1 * totalTime);
		sceneObjects[3]->center.y =-8 * sin(1 * totalTime);*/
		const int32_t width = ScreenWidth();
		const int32_t height = ScreenHeight();

		olc::Pixel *tela = new olc::Pixel[width * height];

		std::thread threads[nThreads];

		for (int i = 0; i < nThreads; i++) {
			threads[i] = std::thread(&RayTracerEngine::drawingThread2, this, i, width, height, tela);
		}

		for (int i = 0; i < nThreads; i++) {
			threads[i].join();
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				Draw(x, y, tela[y * width + x]);
			}
		}
		delete[] tela;

		return true;
	}

	olc::Pixel inicialTrace(const int32_t planeX, const int32_t planeY) const {
		v3d rayDirection = cameraDirection + (cameraParallel * (planeX * unitsPerPixel)) + (cameraUp * (planeY * unitsPerPixel));
		rayDirection.normalize();

		return nTrace(cameraOrigin, rayDirection);
	}

	olc::Pixel nTrace(const v3d& rayOrigin, const v3d& rayDirection) const {
		int rayNumber = 0;

		v3d origin = rayOrigin;
		v3d direction = rayDirection;

		v3d intersection;
		v3d normal;

		float distanceOfIntersection;
		v3d closestIntersection = rayOrigin;
		v3d intersectionNormal;
		Sphere* intersectedObject = NULL;

		bool intersects = false;
		olc::Pixel pix;

		for(rayNumber=0; rayNumber < 6; rayNumber++){
			origin = closestIntersection;
			intersects = false;

			for (size_t i = 0; i < sceneObjects.size(); i++) {
				if ((sceneObjects[i])->intersect(origin, direction, intersection, normal)) {
					if (!intersects || (origin - intersection).norm() < distanceOfIntersection) {
						distanceOfIntersection = (origin - intersection).norm();
						closestIntersection = intersection;
						intersectionNormal = normal;
						intersectedObject = sceneObjects[i];
						intersects = true;
					}
				}
			}
			if (!intersects) {
				return background(direction);
			}
			else if (intersectedObject->response(direction, closestIntersection, intersectionNormal, pix)) {
				return pix;
			}
		}
		return background(direction);
	}

	inline olc::Pixel background(v3d direction) const{
		return olc::Pixel(125 + 125*direction.x, 125 + 125*direction.y, 125 + 125*direction.z);
	}
};

int main()
{
	std::cout << asin(0) << std::endl;
	std::cout << asin(0.99) << std::endl;
	std::cout << asin(-0.99) << std::endl;
	RayTracerEngine demo;
	if (demo.Construct(800,800,1,1)) demo.Start();
}
