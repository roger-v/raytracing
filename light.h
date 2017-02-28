#pragma once

class light {
public:
	const float * C;
	const Pt3D position;
	const float attenuationRadius;
	light(float intensity[3]) : position(Pt3D(0, 0, 0)), C(intensity), attenuationRadius(0) {}
	light(Pt3D position, float intensity[3], float attenuationRadius) : position(position), C(intensity), attenuationRadius(attenuationRadius) {}
};

bool objectInBetween(Pt3D loc, light L);