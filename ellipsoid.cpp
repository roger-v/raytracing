#include "common.h"

Vector3 ellipsoid::normalAt(const Pt3D & p) const {
	float dX = 2 * (p.x - c.x) / (d.x*d.x);
	float dY = 2 * (p.y - c.y) / (d.y*d.y);
	float dZ = 2 * (p.z - c.z) / (d.z*d.z);
	return normalize(Vector3(dX, dY, dZ));
}

float ellipsoid::intersect(const ray & ray) const {
	float a = ((ray.v.x*ray.v.x) / (d.x*d.x)) + ((ray.v.y*ray.v.y) / (d.y*d.y)) + ((ray.v.z*ray.v.z) / (d.z*d.z));
	float b = 2 * (((ray.v.x*(ray.p.x - c.x)) / (d.x*d.x)) + ((ray.v.y*(ray.p.y - c.y)) / (d.y*d.y)) + ((ray.v.z*(ray.p.z - c.z)) / (d.z*d.z)));
	float c0 = (((ray.p.x - c.x)*(ray.p.x - c.x)) / (d.x*d.x)) + (((ray.p.y - c.y)*(ray.p.y - c.y)) / (d.y*d.y)) + (((ray.p.z - c.z)*(ray.p.z - c.z)) / (d.z*d.z)) - 1;
	float root = b*b - 4 * a*c0;
	if (root < 0)
		return -1;
	else if (root > 0)
		return min((-b - sqrt(root)) / (2 * a), (-b + sqrt(root)) / (2 * a));
	return -b / (2 * a);
}