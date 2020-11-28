#pragma once
#include "constants.h"
#include "vertice.h"
#include "moveResult.h"
#include "pathResult.h"
#include <vector>

class graph
{
public:
	graph();
	// Prints a text representation of the graph to standard output
	void display();
	// Regenerates graph to create a new terrain map
	void regenerate();
	// Attempts to move the vehicle to the given coordinates
	moveResult moveVehicle(const std::pair<int,int>& moveCoord);
	// Constants
	int width = graphConstants::WIDTH;
	int height = graphConstants::HEIGHT;
private:
	void initialize();
	void addRoads();
	void addLakes();
	// Calculates the time and distance of a vector of coordinates
	pathResult calculatePathResult(const std::vector<std::pair<int, int>>& path) const;
	// Returns whether coordinate is in map bounds and has a valid terrainType
	bool isValidPath(int x, int y) const;
	// Fields
	int vehicleX = 0;
	int vehicleY = 0;
	vertice arr[graphConstants::WIDTH][graphConstants::HEIGHT];
};