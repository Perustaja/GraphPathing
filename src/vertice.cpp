#include "vertice.h"
#include "terrainType.h"

vertice::vertice(terrainType t) {
	terrain = t;
}

void vertice::setVehicle(vehicle v) {
	veh = v;
}

bool vertice::isOccupied() {
	return veh.has_value();
}