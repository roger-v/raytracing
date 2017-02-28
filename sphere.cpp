#include "common.h"

Vector3 sphere::normalAt(const Pt3D & p) const {
	return normalize(p - c);
}

float sphere::intersect(const ray & ray) const {
	float a = dot(ray.v, ray.v);
	float b = dot(2 * ray.v, ray.p - c);
	float c0 = dot(ray.p - c, ray.p - c) - r*r;
	float root = b*b - 4 * a*c0;
	if (root < 0)
		return -1;
	else if (root > 0)
		return min((-b - sqrt(root)) / (2 * a), (-b + sqrt(root)) / (2 * a));
	return -b / (2 * a);
}