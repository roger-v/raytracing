#include "common.h"

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
	return Vector3(v.x, v.y, v.z)*(1 / (sqrt(v.x*v.x + v.y*v.y + v.z*v.z)));
}

float magnitude(const Vector3 & v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Pt3D screenToWorld(Pt2D p) {
	Vector3 v(p.x, p.y, 1.0);
	Vector3 row0(2.0 / (ImageW - 1.0), 0.0, -1.0);
	Vector3 row1(0.0, -(2.0 / (ImageH - 1.0)), 1.0);
	Vector3 row2(0.0, 0.0, 1.0);
	float x = dot(v, row0);
	float y = dot(v, row1);
	return Pt3D(x, y, 0);
}