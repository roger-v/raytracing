#include "common.h"

Vector3 cylinder::normalAt(const Pt3D & p) const {
	Vector3 N = (p - c - (dot(p - c, A)*A)) * (1 / r);
	return N;
}

float cylinder::intersect(const ray & r0) const {
	ray r1(Pt3D(r0.p.x, c.y, r0.p.z), Vector3(r0.v.x, 0, r0.v.z));
	float a = dot(r1.v, r1.v);
	float b = dot(2 * r1.v, r1.p - c);
	float c0 = dot(r1.p - c, r1.p - c) - r*r;
	float root = b*b - 4 * a*c0;
	if (root < 0)
		return -1;
	else if (root > 0)
		return min((-b - sqrt(root)) / (2 * a), (-b + sqrt(root)) / (2 * a));
	return -b / (2 * a);

}