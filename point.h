#pragma once

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
Vector3 operator+(const Vector3 & v, float n);
Vector3 operator+(float n, const Vector3 & v);
Vector3 operator+ (const Vector3 & v1, const Vector3 & v2);
Vector3 operator- (const Vector3 & v1, const Vector3 & v2);
Vector3 operator* (float f, const Vector3 & v);
Vector3 operator* (const Vector3 & v, float f);
Vector3 operator*(const Vector3 & v1, const Vector3 & v2);
float dot(const Vector3 & v1, const Vector3 & v2);
Vector3 normalize(const Vector3 & v);
float magnitude(const Vector3 & v);
Pt3D screenToWorld(Pt2D p);