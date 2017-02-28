#pragma once

class plane : public surface {
public:
	const Vector3 n;
	const Pt3D c;
	plane() : n(Vector3(0, 0, 0)), c(Pt3D(0, 0, 0)) {}
	plane(Vector3 n, Pt3D o) : n(n), c(o) {}
	Vector3 normalAt(const Pt3D & p) const;
	float intersect(const ray & ray) const;
};