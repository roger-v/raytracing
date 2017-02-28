#pragma once

class ellipsoid : public surface {
public:
	const Pt3D c;
	const Pt3D d;
	ellipsoid() : c(Pt3D(0, 0, 0)), d(Pt3D(1, 1, 1)) {}

	ellipsoid(Pt3D c, Pt3D d) : c(c), d(d) {}

	Vector3 normalAt(const Pt3D & p) const;

	float intersect(const ray & ray) const;
};