#include "common.h"

Color surface::getAmbientCoefficient() { return ambientCoefficient; }
Color surface::getDiffuseCoefficient() { return diffuseCoefficient; }
float surface::getReflectionCoefficient() { return reflectionCoefficient; }
float surface::getSpecularExponent() { return specularExponent; }

void surface::setAmbientCoefficient(float a, float b, float c) {
	ambientCoefficient.x = a;
	ambientCoefficient.y = b;
	ambientCoefficient.z = c;
}
void surface::setDiffuseCoefficient(float a, float b, float c) {
	diffuseCoefficient.x = a;
	diffuseCoefficient.y = b;
	diffuseCoefficient.z = c;
}
void surface::setReflectionCoefficient(float a) {
	reflectionCoefficient = a;
}

void surface::setSpecularExponent(float n) {
	specularExponent = n;
}