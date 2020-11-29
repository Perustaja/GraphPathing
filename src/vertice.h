#pragma once
#include "terrainType.h"

class vertice
{
public:
	vertice(terrainType t = terrainType::Grass) : terrain(t) {};
	terrainType terrain;
};