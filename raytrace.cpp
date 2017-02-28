#include "common.h"
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

Color rayTrace(const ray & r) {
	return rt(r, 0);
}