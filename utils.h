#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Pt2D
{
public:
	int x, y;

	Pt2D(void)
	{
		x = y = 0;
	}

	Pt2D(int nX, int nY)
	{
		x = nX;
		y = nY;
	}
};

class Pt3D {
public:
	float x, y, z;

	Pt3D(void) {
		x = y = z = 0;
	}

	Pt3D(float nX, float nY, float nZ) {
		x = nX;
		y = nY;
		z = nZ;
	}

	Pt3D(float p[3]) {
		x = p[0];
		y = p[1];
		z = p[2];
	}
};

typedef Pt3D Vector3;

typedef Pt3D Color;

Vector3 operator+(const Vector3 & v, float n) {
	return Vector3(v.x + n, v.y + n, v.z + n);
}
Vector3 operator+(float n, const Vector3 & v) {
	return Vector3(v.x + n, v.y + n, v.z + n);
}

Vector3 operator+ (const Vector3 & v1, const Vector3 & v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator- (const Vector3 & v1, const Vector3 & v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator* (float f, const Vector3 & v) {
	return Vector3(f*v.x, f*v.y, f*v.z);
}

Vector3 operator* (const Vector3 & v, float f) {
	return f*v;
}

Vector3 operator*(const Vector3 & v1, const Vector3 & v2) {
	return Vector3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

float dot(const Vector3 & v1, const Vector3 & v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3 normalize(const Vector3 & v) {
	return Vector3(v.x, v.y, v.z)*(1/(sqrt(v.x*v.x + v.y*v.y + v.z*v.z)));
}

float magnitude(const Vector3 & v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

class ray {
public:
	const Pt3D p;
	const Vector3 v;
	ray(Pt3D start, Vector3 dir) : p(start), v(dir) {}
	Pt3D L(float t) const {
		return p + v*t;
	}

};

class light {
public:
	const float * C;
	const Pt3D position;
	const float attenuationRadius;
	light(float intensity[3]) : position(Pt3D(0,0,0)), C(intensity), attenuationRadius(0) {}
	light(Pt3D position, float intensity[3], float attenuationRadius) : position(position), C(intensity), attenuationRadius(attenuationRadius) {}
};

class surface {
public:
	virtual float intersect(const ray & ray) const = 0;
	virtual Vector3 normalAt(const Pt3D & p) const = 0;
	Color getAmbientCoefficient() { return ambientCoefficient; }
	Color getDiffuseCoefficient() { return diffuseCoefficient; }
	float getReflectionCoefficient() { return reflectionCoefficient; }
	float getSpecularExponent() { return specularExponent; }
	
	void setAmbientCoefficient(float a, float b, float c) { 
		ambientCoefficient.x = a;
		ambientCoefficient.y = b;
		ambientCoefficient.z = c;
	}
	void setDiffuseCoefficient(float a, float b, float c) {
		diffuseCoefficient.x = a;
		diffuseCoefficient.y = b;
		diffuseCoefficient.z = c;
	}
	void setReflectionCoefficient(float a) { 
		reflectionCoefficient = a;
	}

	void setSpecularExponent(float n) {
		specularExponent = n;
	}
protected:
	Color ambientCoefficient = *new Color(0.0f, 0.0f, 0.0f);
	Color diffuseCoefficient = *new Color(0.0f, 0.0f, 0.0f);
	float reflectionCoefficient = 0.0;
	float specularExponent = 0.0;
};

class sphere : public surface {
public:
	const Pt3D c;
	const float r;
	
	sphere(void) : c(Pt3D(0, 0, 0)), r(1) {}

	sphere(Pt3D c, float r) : c(c), r(r) {}

	Vector3 normalAt(const Pt3D & p) const {
		return normalize(p - c);
	}

	float intersect(const ray & ray) const {
		float a = dot(ray.v, ray.v);
		float b = dot(2 * ray.v, ray.p - c);
		float c0 = dot(ray.p - c, ray.p - c) - r*r;
		float root = b*b - 4 * a*c0;
		if (root < 0)
			return -1;
		else if (root > 0)
			return min((-b - sqrt(root)) / (2 * a), (-b + sqrt(root)) / (2 * a));
		return -b / (2*a);
	}


};

class ellipsoid : public surface {
public:
	const Pt3D c;
	const Pt3D d;
	ellipsoid() : c(Pt3D(0,0,0)), d(Pt3D(1,1,1)) {}

	ellipsoid(Pt3D c, Pt3D d) : c(c), d(d) {}

	Vector3 normalAt(const Pt3D & p) const {
		float dX = 2 * (p.x - c.x) / (d.x*d.x);
		float dY = 2 * (p.y - c.y) / (d.y*d.y);
		float dZ = 2 * (p.z - c.z) / (d.z*d.z);
		return normalize(Vector3(dX, dY, dZ));
	}

	float intersect(const ray & ray) const {
		float a = ((ray.v.x*ray.v.x) / (d.x*d.x)) + ((ray.v.y*ray.v.y) / (d.y*d.y)) + ((ray.v.z*ray.v.z) / (d.z*d.z));
		float b = 2 * (((ray.v.x*(ray.p.x - c.x))/(d.x*d.x)) + ((ray.v.y*(ray.p.y - c.y)) / (d.y*d.y)) + ((ray.v.z*(ray.p.z - c.z)) / (d.z*d.z)));
		float c0 = (((ray.p.x - c.x)*(ray.p.x - c.x))/(d.x*d.x)) + (((ray.p.y - c.y)*(ray.p.y - c.y)) / (d.y*d.y)) + (((ray.p.z - c.z)*(ray.p.z - c.z)) / (d.z*d.z)) - 1;
		float root = b*b - 4 * a*c0;
		if (root < 0)
			return -1;
		else if (root > 0)
			return min((-b - sqrt(root)) / (2 * a), (-b + sqrt(root)) / (2 * a));
		return -b / (2 * a);
	}
};

class plane : public surface {
public:
	const Vector3 n;
	const Pt3D c;
	plane() : n(Vector3(0, 0, 0)), c(Pt3D(0, 0, 0)) {}
	plane(Vector3 n, Pt3D o) : n(n), c(o) {}
	Vector3 normalAt(const Pt3D & p) const {
		return n;
	}
	float intersect(const ray & ray) const {
		if (dot(ray.v, n) == 0) return -1;
		float t = dot(n, c - ray.p) / dot(n, ray.v);
		if (t < 0) return -1;
		return t;
	}
};

class cylinder : public surface {
public:
	const Pt3D c;
	const Vector3 A;
	const float r;
	cylinder() : c(Pt3D(0, 0, 0)), A(Vector3(0, 1, 0)), r(0) {}

	cylinder(Pt3D C, float r) : c(C), A(Vector3(0, 1, 0)), r(r) {}

	cylinder(Pt3D C, Vector3 A, float r) : c(C), A(normalize(A)), r(r) {}
	
	Vector3 normalAt(const Pt3D & p) const {
		Vector3 N = (p - c - (dot(p - c, A)*A)) * (1/r);
		return N;
	}

	float intersect(const ray & r0) const {
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
};

Pt3D screenToWorld(Pt2D p) {
	Vector3 v(p.x, p.y, 1.0);
	Vector3 row0(2.0/(ImageW - 1.0),0.0,-1.0);
	Vector3 row1(0.0, -(2.0 / (ImageH - 1.0)), 1.0);
	Vector3 row2(0.0, 0.0, 1.0);
	float x = dot(v, row0);
	float y = dot(v, row1);
	return Pt3D(x, y, 0);
}

