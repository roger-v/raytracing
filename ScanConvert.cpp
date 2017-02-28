#include "common.h"

float framebuffer[ImageH][ImageW][3];

void drawit(void)
{
	glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
	glFlush();
}

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

