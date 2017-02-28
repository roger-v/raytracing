#include "common.h"

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