#include "graph.h"
#include "vertice.h"
#include "terrainType.h"
#include "vehicle.h"
#include "pathResult.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <stdexcept>

using std::cout; using std::pair;
using std::endl; using std::queue;
using std::vector; using std::exception;

graph::graph(graphConfig gc, vehicle v) : width(gc.width), height(gc.height), lakeCount(gc.lakeCount), lakeLength(gc.lakeLength), gridSizeKm(gc.gridSizeKm), veh(v) {
	initialize();
}

void graph::display(){
	cout << "Current representation of map: \n";
	cout << "Legend: V = Vehicle W = Water R = Road G = Grass.\n";
	cout << "\n  ";
	for (int i = 0; i < width; i++)
		cout << "  " << i;
	for (int r = 0; r < height; r++) {
		cout << "\n";
		if (r > 9)
			cout << r;
		else
			cout << " " << r;
		for (int c = 0; c < width; c++) {
			if (c > 10)
				cout << "   ";
			else
				cout << "  ";
			cout << ((r == vehicleRow && c == vehicleCol) ? "\033[1;31mV\033[0m" : toString(matrix[r][c].terrain));
		}
	}
	cout << endl;
}

void graph::regenerate() {
	initialize();
}

moveResult graph::moveVehicle(const pair<int, int>& moveCoord) {
	// Note: coordinate pair format is {row, col}
	if (moveCoord.first == vehicleRow && moveCoord.second == vehicleCol)
		return moveResult::failed("Vehicle is already at desired coordinate.");

	queue<vector<pair<int, int>>> q;
	vector<pair<int, int>> path {{vehicleRow, vehicleCol}};
	vector<vector<bool>> visited(height, vector<bool>(width, false));
	visited[vehicleRow][vehicleCol] = true;
	bool reached = false;
	int dr[] = {-1,1,0,0,-1,-1,1,1}; // Direction vectors for generating neighbors
	int dc[] = {0,0,1,-1,-1,1,1,-1};

	vector<pair<int, int>> bestPath;
	pathResult bestPathRes { 0, 0, 0 };

	q.push(path);
	while (!q.empty()) {
		path = q.front();
		q.pop();
		if (path[path.size() - 1] == moveCoord) {
			reached = true;
			// Check if path is best path and update variables
			pathResult res = calculatePathResult(path);
			if (bestPathRes.timeInH == 0 || res.timeInH < bestPathRes.timeInH) {
				bestPath = path;
				bestPathRes = res;
			}
		}
		// Use vector addition to add neighbor coordinates
		for (int i = 0; i < 8; i++) {
			int r = path[path.size() - 1].first + dr[i];
			int c = path[path.size() - 1].second + dc[i];
			if (isValidPath(r, c) && !visited[r][c]) {
				vector<pair<int, int>> newPath(path);
				newPath.push_back({r, c});
				q.push(newPath);
				visited[r][c] = true;
			}
		}
	}

	if (reached) {
		// Update vehicle variables
		vehicleRow = moveCoord.first;
		vehicleCol = moveCoord.second;
		return moveResult::successful(bestPath, bestPathRes, matrix);
	}
	return moveResult::failed("Unable to reach destination. Destination may be water or blocked by water.");
}

bool graph::isValidPath(int row, int col) const {
	if (row >= 0 && row < height)
		if (col >= 0 && col < width)
			return matrix[row][col].terrain != terrainType::Water;
	return false;
}

void graph::initialize() {
	// Initialize random seed used for roads and lakes
	srand((unsigned int)time(NULL));
	
	// Create matrix with default vertices
	matrix = vector<vector<vertice>>(height, vector<vertice>(width, vertice(terrainType::Grass)));
	addLakes();
	addRoads();
	vehicleRow = 0;
	vehicleCol = 0;
}

void graph::addRoads() {
	// Add a random horizontal-start road starting from (0, random y coordinate)
	// Has a bias for the road to travel vertically as opposed to straight horizontal
	int r = rand() % height; // Create random number between 0 and height
	int c = 0;
	while (r > -1 && r < height && c < width) {
		matrix[r][c].terrain = terrainType::Road;
		int ran = rand() % 4; // Create random number between 0 and 4
		if (ran < 2)
			r--;
		else if (ran < 4)
			r++;
		c++;
	}
	// Same approach, but vertically
	r = 0;
	c = rand() % width;
	while (c > -1 && c < width && r < height) {
		matrix[r][c].terrain = terrainType::Road;
		int ran = rand() % 4;
		if (ran < 2)
			c--;
		else if (ran < 4)
			c++;
		r++;
	}
}

void graph::addLakes() {
	int lakes = 0;
	while (lakes < lakeLength) {
		int h = rand() % height;
		int w = rand() % width;
		for (int r = h; r > -1 && r > h - lakeLength; r--)
			for (int c = w; c < width && c < w + lakeLength; c++)
				matrix[r][c].terrain = terrainType::Water;
		lakes++;
	}
}

pathResult graph::calculatePathResult(const std::vector<std::pair<int, int>>& path) const {
	pathResult res {0, 0};
	// For sake of simplicity, just act as though starting and ending points were traversed fully as well
	for (int i = 0; i < path.size() - 1; i++) {
		res.distanceInKm += gridSizeKm;
		switch (matrix[path[i].first][path[i].second].terrain) {
			case terrainType::Road: res.timeInH += (double) gridSizeKm / veh.roadkmph; break;
			case terrainType::Grass: res.timeInH += (double) gridSizeKm / veh.grasskmph; break;
			default: throw exception("Path trace contained coordinates with invalid terrain type.");
		}
	}
	res.fuelUsedInL = res.distanceInKm / veh.kmpl;
	return res;
}
