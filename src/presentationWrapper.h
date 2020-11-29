#pragma once
#include "graph.h"
#include "config.h"
#include <string>
#include <utility>

// Purpose of this class is to take input, display menus, and bridge the gap between the user interface and the underlying graph. Presentation logic only.
class presentationWrapper
{
public:
	presentationWrapper(graphConfig gc, vehicleConfig vc);
	// Contains main code for controlling session by displaying content and taking input.
	void run();
private:
	void displayMenu();
	// Returns whether coordinates are in map bounds
	bool areValidCoords(int x, int y) const;
	// Prompts the user to input coordinates for the vehicle to move to.
	void moveVehicle();
	// Determines whether a given string represents a valid csv of two integers.
	bool stringIsCoordinateFormat(const std::string& s) const;
	// Parses valid coordinate string to a pair of integers. Throws an exception if string is not in valid format.
	std::pair<int, int> parseCoordinateString(const std::string& s) const;
	graph g;
};