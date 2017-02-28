#pragma once

class sphere : public surface {
public:
	const Pt3D c;
	const float r;

	sphere(void) : c(Pt3D(0, 0, 0)), r(1) {}

	sphere(Pt3D c, float r) : c(c), r(r) {}

	Vector3 normalAt(const Pt3D & p) const;

	float intersect(const ray & ray) const;


};