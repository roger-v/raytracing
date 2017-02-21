#include <Windows.h>
#include <GL/glut.h>
#include <math.h>
#include "ScanConvert.h"
#include "utils.h"
#include <vector>
#include <iostream>

using namespace std;

vector<surface*> scene;
vector<light> sceneLights;
void clearScene() { scene.clear(); sceneLights.clear(); }
Color A(0.5f, 0.5f, 0.5f);
bool RLF;
Pt3D eye(0, 0, -2);

bool objectInBetween(Pt3D loc, light L);

/******************************************************************
Notes:
Image size is 400 by 400 by default.  You may adjust this if
you want to.
You can assume the window will NOT be resized.
Call clearFramebuffer to clear the entire framebuffer.
Call setFramebuffer to set a pixel.  This should be the only
routine you use to set the color (other than clearing the
entire framebuffer).  drawit() will cause the current
framebuffer to be displayed.
As is, your scan conversion should probably be called from
within the display function.  There is a very short sample
of code there now.
You may add code to any of the subroutines here,  You probably
want to leave the drawit, clearFramebuffer, and
setFramebuffer commands alone, though.
*****************************************************************/

float framebuffer[ImageH][ImageW][3];

// Draws the scene
void drawit(void)
{
	glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
	glFlush();
}

// Clears framebuffer to black
void clearFramebuffer()
{
	int i, j;

	for (i = 0; i<ImageH; i++) {
		for (j = 0; j<ImageW; j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

// Sets pixel x,y to the color RGB
// I've made a small change to this function to make the pixels match
// those returned by the glutMouseFunc exactly - Scott Schaefer 
void setFramebuffer(int x, int y, float R, float G, float B)
{
	// changes the origin from the lower-left corner to the upper-left corner
	y = ImageH - 1 - y;
	if (R <= 1.0)
		if (R >= 0.0)
			framebuffer[y][x][0] = R;
		else
			framebuffer[y][x][0] = 0.0;
	else
		framebuffer[y][x][0] = 1.0;
	if (G <= 1.0)
		if (G >= 0.0)
			framebuffer[y][x][1] = G;
		else
			framebuffer[y][x][1] = 0.0;
	else
		framebuffer[y][x][1] = 1.0;
	if (B <= 1.0)
		if (B >= 0.0)
			framebuffer[y][x][2] = B;
		else
			framebuffer[y][x][2] = 0.0;
	else
		framebuffer[y][x][2] = 1.0;
}

void display(void)
{
	drawit();
}

Color rt(const ray & r, int depth);

Color rayTrace(const ray & r) {
	return rt(r, 0);
}

void init(void)
{
	clearFramebuffer();
	for (int x = 0; x < ImageW; x++) {
		for (int y = 0; y < ImageH; y++) {
			Pt3D p(screenToWorld(Pt2D(x, y)));
			Vector3 dir((Vector3(p.x, p.y, 0) - eye));
			ray r(eye, normalize(dir));
			Color c = rayTrace(r);
			setFramebuffer(x, y, c.x, c.y, c.z);
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		clearScene();
		scene1Init();
		break;
	case '2':
		clearScene();
		scene2Init();
		break;
	case '3':
		clearScene();
		scene3Init();
		break;
	case '4':
		clearScene();
		scene4Init();
	case 'd':
		eye.x += 0.25;
		break;
	case 'a':
		eye.x -= 0.25;
		break;
	case 'w':
		eye.z += 0.25;
		break;
	case 's':
		eye.z -= 0.25;
		break;
	default:
		break;
	}
	init();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	scene1Init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ImageW, ImageH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Roger Villanueva - Homework 4");
	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

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

	plane * s3 = new plane(Vector3(0,1,0), Pt3D(-2, -1, 1));

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

float randomFloat() {
	return (float)(rand() % 100) / 100;
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

	light l(eye, new float[3]{ 0.75f, 0.75f, 0.75f }, 2.0f);
	scene.push_back(s1);
	scene.push_back(s2);
	scene.push_back(s4);
	scene.push_back(p);
	sceneLights.push_back(l);
	RLF = true;
}

Pt3D spiralFunction(float c, float r, float t, float x0, float z0) {
	/*
	x=x0+r*cos(t);
	y=c*t;
	z=z0+r*sin(t);
	*/
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

void scene4Init() {
	scene.clear();
	sceneLights.clear();
	createSpiral(Pt3D(-0.15, 0.0, 1.75), 15, 0.5);
	light L(Pt3D(0.75, 2.5, 0), new float[3]{ 1, 1, 1 }, 0);
	sceneLights.push_back(L);
	RLF = false;
}

bool objectInBetween(Pt3D loc, light L) {
	ray r(loc, L.position - loc);
	for (int s = 0; s < scene.size(); s++) {
		float t = scene[s]->intersect(r);
		float distanceToLight = magnitude(L.position - loc);
		float distanceToObj = magnitude(r.L(t) - loc);
		if (scene[s]->intersect(r) > 0 && distanceToObj < distanceToLight) {
			return true;
		}
	}
	return false;
}

Color rt(const ray & r, int depth) {
	Color I(0, 0, 0);
	float minT = FLT_MAX;
	surface * closestSurface = nullptr;
	Vector3 R, N, E(r.v);
	Pt3D loc(0, 0, 0);
	Color ambientPortion(0, 0, 0);
	Color ka(0, 0, 0), kd(0, 0, 0);
	for (int s = 0; s < scene.size(); s++) { // every surface in the scene
		Color summation(0, 0, 0);
		float t = scene[s]->intersect(r);
		if (t < minT && t > 0) //hidden surface removal
		{
			closestSurface = scene[s];
			minT = t;
			ka = scene[s]->getAmbientCoefficient();
			kd = scene[s]->getDiffuseCoefficient();
			ambientPortion = ka * A; //add the ka*A only at the beginning otherwise "shadows" will just be the ambient color

			loc = r.L(t) + scene[s]->normalAt(loc)*0.00001; //prevents fuzziness with reflections and slanted planes (for shadow calculations)

			N = scene[s]->normalAt(loc), E = normalize(-1 * r.v);
			float ks = scene[s]->getReflectionCoefficient(), n = scene[s]->getSpecularExponent();


			for (int j = 0; j < sceneLights.size(); j++) { // for every light in the scene

				Color C(sceneLights[j].C[0], sceneLights[j].C[1], sceneLights[j].C[2]);

				Vector3 L = normalize(sceneLights[j].position - loc);

				R = (2 * dot(L, N) * N) - L;

				float REn = pow(dot(R, E), n);
				if (dot(L, N) > 0) {
					if (REn < 0) REn = 0;
					if (!objectInBetween(loc, sceneLights[j])) { //SHADOW
						summation = summation + C * (kd * dot(L, N) + ks * REn);
					}
				}
			}
			I = summation;
		}
	}
	if (closestSurface != nullptr && RLF) {
		float Ye = closestSurface->getReflectionCoefficient();
		if (Ye > 0 && depth < 4) {
			return I + Ye*rt(ray(loc, R), depth + 1);
		}
	}
	return I + ambientPortion;
}