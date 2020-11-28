#pragma once
#include "vehicle.h"
#include "terrainType.h"
#include <optional>

class vertice
{
public:
	vertice(terrainType t = terrainType::Grass);
	void setVehicle(vehicle v);
	void removeVehicle();
	bool isOccupied();
	terrainType terrain;
	std::optional<vehicle> veh;
};