#include "common.h"

Vector3 plane::normalAt(const Pt3D & p) const {
	return n;
}
float plane::intersect(const ray & ray) const {
	if (dot(ray.v, n) == 0) return -1;
	float t = dot(n, c - ray.p) / dot(n, ray.v);
	if (t < 0) return -1;
	return t;
}