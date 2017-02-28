#pragma once
#define ImageW 400
#define ImageH 400
#define min(a,b) ((a) < (b) ? (a) : (b))

#include <Windows.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

using std::vector;

#include "point.h"
#include "ray.h"
#include "light.h"
#include "surface.h"
#include "sphere.h"
#include "ellipsoid.h"
#include "plane.h"
#include "cylinder.h"
#include "ScanConvert.h"
#include "scenes.h"
#include "spiral.h"
#include "shared.h"
#include "raytrace.h"
