#include "presentationWrapper.h"
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include <stdexcept>

using std::cin; using std::cout;
using std::endl; using std::string;
using std::vector; using std::pair;

void presentationWrapper::run() {
	g.display();
	string input;
	while (true) {
		displayMenu();
		cin >> input;
		if (input == "1")
			moveVehicle();
		else if (input == "2")
			g.display();
		else if (input == "3") {
			g.regenerate();
			cout << "Map regenerated.\n";
			g.display();
		}
		else if (input == "4") {
			cout << "Exiting...";
			return;
		}
		else {
			cout << "Invalid input. Please enter in a number between 1 and 4.\n";
		}
	}
}

void presentationWrapper::displayMenu() {
	cout << "Please select an option.\n";
	cout << "1. Move vehicle.\n";
	cout << "2. Display current map.\n";
	cout << "3. Regenerate map.\n";
	cout << "4. Exit.\n";
}


bool presentationWrapper::areValidCoords(int x, int y) const {
	if (x >= 0 && x < g.WIDTH)
		if (y >= 0 && y < g.HEIGHT)
			return true;
	return false;
}

void presentationWrapper::moveVehicle() {
	string input;
	cout << "Please enter in the desired coordinates the vehicle should move to, separated by a comma. (e.g 5,2)\n";
	while (true) {
		cin >> input;
		if (stringIsCoordinateFormat(input)) {
			pair<int, int> coords = parseCoordinateString(input);
			if (areValidCoords(coords.first, coords.second)) {
				moveResult r = g.moveVehicle(coords);
				r.displayResult();
				break;
			}
		}
		cout << "Invalid input. Please enter in two comma-separated coordinates (e.g. 5,2).\n";
	}
}

bool presentationWrapper::stringIsCoordinateFormat(const std::string& s) const{
	if (std::regex_match(s, std::regex("\\d+[,]\\d+")))
		return true;
	return false;
}

pair<int, int> presentationWrapper::parseCoordinateString(const std::string& s) const{
	// Split string based on , and parse integers from the resulting two strings
	std::stringstream stream(s);
	string splitStr;
	vector<string> splitStrings;
	while (std::getline(stream, splitStr, ',')) {
		splitStrings.push_back(splitStr);
	}
	if (splitStrings.size() == 2) {
		int x = std::stoi(splitStrings[0], nullptr);
		int y = std::stoi(splitStrings[1], nullptr);
		return pair<int, int>(x, y);

	}
	throw std::invalid_argument("Input coordinate string did not match proper coordinate format.");
}
