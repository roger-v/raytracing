#pragma once

class ray {
public:
	const Pt3D p;
	const Vector3 v;
	ray(Pt3D start, Vector3 dir) : p(start), v(dir) {}
	Pt3D L(float t) const {
		return p + v*t;
	}

};