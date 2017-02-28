#include "common.h"

float randomFloat() {
	return (float)(rand() % 100) / 100;
}

Pt3D spiralFunction(float c, float r, float t, float x0, float z0) {
	return Pt3D(x0 + r*cos(t), c*t, z0 + r*sin(t));
}

void createSpiral(Pt3D center, float tRange, float r) {
	Pt3D spiralCenter(center);
	eye.x = 0;
	int i = 0;
	for (float t = -tRange; t < tRange; t += 0.25, i++) {
		scene.push_back(new sphere(spiralFunction(0.15, r*1.5, t, spiralCenter.x, spiralCenter.z), 0.1));
		float r = randomFloat();
		float g = randomFloat();
		float b = randomFloat();
		scene[i]->setAmbientCoefficient(r, g, b);
		scene[i]->setDiffuseCoefficient(r, g, b);
		scene[i]->setReflectionCoefficient(0.5f);
		scene[i]->setSpecularExponent(3.0f);
	}
	cylinder * c1 = new cylinder(spiralCenter, r);
	c1->setAmbientCoefficient(0.0f, 0.2f, 0.5f);
	c1->setDiffuseCoefficient(0.0f, 0.3f, 0.7f);
	c1->setReflectionCoefficient(0.5);
	c1->setSpecularExponent(3.0f);
	scene.push_back(c1);
}