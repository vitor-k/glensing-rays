#include "Sphere.h"
#include "olcPixelGameEngine.h"

bool MirroredSphere::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
    rayDirection = rayDirection - 2 * dot(rayDirection, intersectionNormal) * intersectionNormal;
    return false;
}

bool OpaqueSphere::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
    float normalMultiplier = sqrt(abs(rayDirection.dot(intersectionNormal)));
    pix = olc::Pixel(R*normalMultiplier, G*normalMultiplier, B*normalMultiplier);
    return true;
}

bool CoolSphere::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
    v3d cool = cross(rayDirection, intersectionNormal) ;
    pix = olc::Pixel(125 + 125*cool.x, 125 + 125*cool.y, 125 + 125*cool.z);
    return true;
}

bool AtmoSphere::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
    float normalMultiplier = sqrt(abs(rayDirection.dot(intersectionNormal)));
    pix = olc::Pixel(normalMultiplier*R + (1-normalMultiplier)*atmosR, normalMultiplier*G + (1-normalMultiplier)*atmosG, normalMultiplier*B + (1-normalMultiplier)*atmosB);
    return true;
}