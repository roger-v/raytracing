#pragma once
#define ImageW 400
#define ImageH 400

/*
class color {
public:
	color(float r, float g, float b) : r(r), g(g), b(b) {}
	float r, g, b;		// Color (R,G,B values)
	void setColors(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};
*/

// Clears framebuffer to black
void clearFramebuffer();

// Sets pixel x,y to the color RGB
void setFramebuffer(int x, int y, float R, float G, float B);

void scene1Init();
void scene2Init();
void scene3Init();
void scene4Init();