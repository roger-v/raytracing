#pragma once

class surface {
public:
	virtual float intersect(const ray & ray) const = 0;
	virtual Vector3 normalAt(const Pt3D & p) const = 0;
	Color getAmbientCoefficient();
	Color getDiffuseCoefficient();
	float getReflectionCoefficient();
	float getSpecularExponent();
	void setAmbientCoefficient(float a, float b, float c);
	void setDiffuseCoefficient(float a, float b, float c);
	void setReflectionCoefficient(float a);
	void setSpecularExponent(float n);
protected:
	Color ambientCoefficient = Color(0.0f, 0.0f, 0.0f);
	Color diffuseCoefficient = Color(0.0f, 0.0f, 0.0f);
	float reflectionCoefficient = 0.0;
	float specularExponent = 0.0;
};