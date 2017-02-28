#pragma once

class cylinder : public surface {
public:
	const Pt3D c;
	const Vector3 A;
	const float r;
	cylinder() : c(Pt3D(0, 0, 0)), A(Vector3(0, 1, 0)), r(0) {}

	cylinder(Pt3D C, float r) : c(C), A(Vector3(0, 1, 0)), r(r) {}

	cylinder(Pt3D C, Vector3 A, float r) : c(C), A(normalize(A)), r(r) {}

	Vector3 normalAt(const Pt3D & p) const;

	float intersect(const ray & r0) const;
};