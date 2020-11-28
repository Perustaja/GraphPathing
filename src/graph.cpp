#include "constants.h"
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

using namespace graphConstants;
using namespace vehicleConstants;
using std::cout; using std::pair;
using std::endl; using std::queue;
using std::vector; 

graph::graph() {
	initialize();
}

void graph::display(){
	cout << "Current representation of map: \n";
	cout << "Legend: V = Vehicle W = Water R = Road G = Grass.\n";
	cout << "\n  ";
	for (int i = 0; i < width; i++)
		cout << "  " << i;
	for (int i = 0; i < height; i++) {
		cout << "\n";
		if (i > 9)
			cout << i;
		else
			cout << " " << i;
		for (int j = 0; j < width; j++) {
			if (j > 10)
				cout << "   ";
			else
				cout << "  ";
			cout << (arr[i][j].isOccupied() ? "\033[1;31mV\033[0m" : toString(arr[i][j].terrain));
		}
	}
	cout << endl;
}

void graph::regenerate() {
	initialize();
}

moveResult graph::moveVehicle(const pair<int, int>& moveCoord) {
	queue<vector<pair<int, int>>> q;
	vector<pair<int, int>> path{{vehicleX, vehicleY}};
	bool visited[WIDTH][HEIGHT] {};
	visited[vehicleX][vehicleY] = true;
	bool reached = false;
	int dx[] = {-1,1,0,0,-1,-1,1,1}; // Direction vectors for generating neighbors
	int dy[] = {0,0,1,-1,-1,1,1,-1};

	vector<pair<int, int>> bestPath;
	pathResult bestPathR;


	q.push(path);
	while (!q.empty()) {
		path = q.front();
		q.pop();
		if (path[path.size() - 1] == moveCoord) {
			reached = true;
			// Check if path is best path
			pathResult res = calculatePathResult(path);
			if (res.timeInH < bestPathR.timeInH) {
				bestPath = path;
				bestPathR = res;
			}
		}
		// Use vector addition to add neighbor coordinates
		for (int i = 0; i < 8; i++) {
			int x = path[path.size() - 1].first + dx[i];
			int y = path[path.size() - 1].second + dy[i];
			if (isValidPath(x, y) && !visited[x][y]) {
				vector<pair<int, int>> newPath(path);
				newPath.push_back({x, y});
				q.push(newPath);
				visited[x][y] = true;
			}
		}
	}

	if (reached) {
		// TODO: Update vehicle location
		// Perform shortest path calculation based on vehicle and terrain
		return moveResult::successful(path);
	}
	return moveResult::failure("Unable to reach destination. Destination may be water or blocked by water.");
}

bool graph::isValidPath(int x, int y) const {
	if (x >= 0 && x < width)
		if (y >= 0 && y < height)
			return arr[x][y].terrain != terrainType::Water;
	return false;
}

void graph::initialize() {
	// Initialize random seed used for roads and lakes
	srand(time(NULL));

	// Create graph with default vertices
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			arr[i][j] = vertice(terrainType::Grass);
		}
	}
	addLakes();
	addRoads();
	vehicle v;
	arr[0][0].setVehicle(v);
}

void graph::addRoads() {
	// Add a random horizontal-start road starting from (0, random y coordinate)
	// Has a bias for the road to travel vertically as opposed to straight horizontal
	int i = rand() % height; // Create random number between 0 and height
	int j = 0;
	while (i > -1 && i < height && j < width) {
		arr[i][j].terrain = terrainType::Road;
		int ran = rand() % 4; // Create random number between 0 and 4
		if (ran < 2)
			i--;
		else if (ran < 4)
			i++;
		j++;
	}
	// Same approach, but vertically
	i = 0;
	j = rand() % width;
	while (j > -1 && j < width && i < height) {
		arr[i][j].terrain = terrainType::Road;
		int ran = rand() % 4;
		if (ran < 2)
			j--;
		else if (ran < 4)
			j++;
		i++;
	}
}

void graph::addLakes() {
	int lakes = 0;
	while (lakes < graphConstants::LAKE_LENGTH) {
		int y = rand() % height;
		int x = rand() % width;
		for (int i = y; i > -1 && i > y - graphConstants::LAKE_LENGTH; i--)
			for (int j = x; j < width && j < x + graphConstants::LAKE_LENGTH; j++)
				arr[i][j].terrain = terrainType::Water;
		lakes++;
	}
}

pathResult graph::calculatePathResult(const std::vector<std::pair<int, int>>& path) const {
	pathResult r;
	for (int i = 0; i < path.size(); i++) {
		r.distanceInKm += GRID_SIZE_KM;
		switch (arr[path[i].first][path[i].second].terrain) {
			case terrainType::Road: r.timeInH += GRID_SIZE_KM / VEH_ROAD_SPEED_KMH * 60; break;
			case terrainType::Grass: r.timeInH += GRID_SIZE_KM / VEH_GRASS_SPEED_KMH * 60; break;
			default: break; // do nothing
	}
	return r;
}
