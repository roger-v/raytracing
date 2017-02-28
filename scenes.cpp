#include "common.h"
void scene1Init() {

	ellipsoid * s1 = new ellipsoid(Pt3D(0.25, -0.25, 1.25), Pt3D(0.75, 0.42, 0.25));

	s1->setAmbientCoefficient(0.0f, 0.25f, 0.0f);
	s1->setDiffuseCoefficient(0.0f, 0.7f, 0.0f);
	s1->setReflectionCoefficient(0.8f);
	s1->setSpecularExponent(3.0f);

	sphere * s2 = new sphere(Pt3D(-0.25, 0.25f, 0.75f), 0.5f);

	s2->setAmbientCoefficient(0.5f, 0.0f, 0.0f);
	s2->setDiffuseCoefficient(0.7f, 0.0f, 0.0f);
	s2->setReflectionCoefficient(1.0f);
	s2->setSpecularExponent(5.0f);

	plane * s3 = new plane(Vector3(0, 1, 0), Pt3D(-2, -1, 1));

	s3->setAmbientCoefficient(0.0f, 0.0f, 0.5f);
	s3->setDiffuseCoefficient(0.0f, 0.0f, 0.7f);

	light l(Pt3D(2, 2, -2), new float[3]{ 0.75f, 0.75f, 0.75f }, 2.0f);
	light m(Pt3D(-1.0, 2, -1), new float[3]{ 1.0f, 1.0f, 1.0f }, 2.0f);
	scene.push_back(s2);
	scene.push_back(s1);
	scene.push_back(s3);
	sceneLights.push_back(m);
	sceneLights.push_back(l);
	RLF = false;
}

void scene2Init() {
	cylinder * s1 = new cylinder(Pt3D(-0.5, 0.0, 1.5), 0.5);
	s1->setAmbientCoefficient(0.0f, 0.0f, 0.5f);
	s1->setDiffuseCoefficient(0.0f, 0.0f, 0.7f);
	s1->setReflectionCoefficient(0.90f);
	s1->setSpecularExponent(20.0f);

	sphere * s2 = new sphere(Pt3D(0.25f, 0.25f, 0.35f), 0.35f);

	s2->setAmbientCoefficient(0.0f, 0.5f, 0.0f);
	s2->setDiffuseCoefficient(0.0f, 0.5f, 0.0f);
	s2->setReflectionCoefficient(1.0f);
	s2->setSpecularExponent(3.0f);

	plane * s3 = new plane(Vector3(0, 1, -0.3), Pt3D(-2, -1, 1));

	s3->setAmbientCoefficient(0.5f, 0.2f, 0.0f);
	s3->setDiffuseCoefficient(0.7f, 0.2f, 0.0f);

	plane * s4 = new plane(Vector3(0.2, 0.3, -1), Pt3D(0, 0, 4));

	s4->setAmbientCoefficient(0.0f, 0.5f, 0.5f);
	s4->setDiffuseCoefficient(0.0f, 0.5f, 0.5f);

	light l(Pt3D(2, 2, -2), new float[3]{ 0.75f, 0.75f, 0.75f }, 2.0f);
	scene.push_back(s2);
	scene.push_back(s1);
	scene.push_back(s3);
	scene.push_back(s4);
	sceneLights.push_back(l);
	RLF = false;
}

void scene3Init() {

	cylinder * s4 = new cylinder(Pt3D(-0.75, 0.0f, 1.5f), 0.3f);

	s4->setAmbientCoefficient(0.5f, 0, 0);
	s4->setDiffuseCoefficient(0.7f, 0, 0);
	s4->setReflectionCoefficient(1.0f);
	s4->setSpecularExponent(5.0f);

	sphere * s2 = new sphere(Pt3D(0.25, 0.25f, 2.0f), 0.5f);

	s2->setAmbientCoefficient(0.5f, 0.5f, 0.5f);
	s2->setDiffuseCoefficient(0.7f, 0.7f, 0.7f);
	s2->setReflectionCoefficient(1.0f);
	s2->setSpecularExponent(5.0f);

	sphere * s1 = new sphere(Pt3D(0.75, -0.25f, 1.0f), 0.25f);

	s1->setAmbientCoefficient(0.0f, 0.5f, 0.0f);
	s1->setDiffuseCoefficient(0.0f, 0.7f, 0.0f);
	s1->setReflectionCoefficient(1.0f);
	s1->setSpecularExponent(5.0f);

	plane * p = new plane(Vector3(1.0f, 0.75, -0.25), Pt3D(-4, 3, 0));
	p->setAmbientCoefficient(0.0f, 0.0f, 0.5f);
	p->setDiffuseCoefficient(0.0f, 0.0f, 0.7f);
	p->setReflectionCoefficient(1.0f);
	p->setSpecularExponent(5.0f);

	light l(Vector3(0.0f, 0.0f, -2.0f), new float[3]{ 0.75f, 0.75f, 0.75f }, 2.0f);
	scene.push_back(s1);
	scene.push_back(s2);
	scene.push_back(s4);
	scene.push_back(p);
	sceneLights.push_back(l);
	RLF = true;
}

void scene4Init() {
	scene.clear();
	sceneLights.clear();
	createSpiral(Pt3D(-0.15, 0.0, 1.75), 15, 0.5);
	light L(Pt3D(0.75, 2.5, 0), new float[3]{ 1, 1, 1 }, 0);
	sceneLights.push_back(L);
	RLF = false;
}
void clearScene() { 
	scene.clear(); 
	sceneLights.clear(); 
}