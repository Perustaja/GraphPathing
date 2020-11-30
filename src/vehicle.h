#pragma once
#include "config.h"

class vehicle {
public:
	vehicle(vehicleConfig vc) : grasskmph(vc.grasskmph), roadkmph(vc.roadkmph), kmpl(vc.kmpl) {};
	int grasskmph;
	int roadkmph;
	int kmpl;
};