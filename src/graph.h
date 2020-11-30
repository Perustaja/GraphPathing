#pragma once
#include "config.h"
#include "vertice.h"
#include "moveResult.h"
#include "pathResult.h"
#include "vehicle.h"
#include <vector>

class graph {
public:
	graph(graphConfig gc, vehicle v);
	// Prints a text representation of the graph to standard output
	void display();
	// Regenerates matrix to create a new terrain map
	void regenerate();
	// Attempts to move the vehicle to the given coordinates in {row, col} format
	moveResult moveVehicle(const std::pair<int,int>& moveCoord);
	size_t width;
	size_t height;
private:
	// Populates matrix with randomized vertices. Can be called to regenerate matrix
	void initialize();
	void addRoads();
	void addLakes();
	// Calculates a pathResult based on the given vector of coordinates
	pathResult calculatePathResult(const std::vector<std::pair<int, int>>& path) const;
	// Returns whether coordinate is in map bounds and has a valid terrainType
	bool isValidPath(int row, int col) const;
	int gridSizeKm;
	int lakeLength;
	int lakeCount;
	// Vehicle information is stored directly in graph for ease
	int vehicleRow = 0;
	int vehicleCol = 0;
	vehicle veh;
	std::vector<std::vector<vertice>> matrix;
};