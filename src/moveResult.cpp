#include "moveResult.h"
#include "pathResult.h"
#include "vertice.h"
#include <iostream>
#include <iomanip>

using std::cout; using std::endl;
using std::string; using std::pair;
using std::vector; using std::fixed;
using std::setprecision; using std::showpoint;


moveResult moveResult::successful(const std::vector<std::pair<int, int>>& pathTrace, pathResult res, std::vector<std::vector<vertice>> m)
{
	// Ideally, an unordered_set would be used to store the coordinates. This would provide amortized constant lookup necessary when displaying the move
	// However, hashing a pair<int,int> in a way that will not cause tons of collisions is not a simple task nor provided by std::hash.
	// Using a set here would only get O(logn) lookup time so, in exchange for memory, a lookup matrix is created for constant lookup time in displayResult().
	vector<vector<bool>> travCoords(m.size(), vector<bool>(m[0].size(), false));
	for (auto p : pathTrace)
		travCoords[p.first][p.second] = true;
	moveResult mr(true);
	mr.traversedCoords.emplace(travCoords);
	mr.pathRes = res;
	mr.matrix = m;
	return mr;
}

void moveResult::displayResult() const {
	if (traversedCoords.has_value() && pathRes.has_value() && matrix.has_value()) {
		size_t height = matrix.value().size();
		size_t width = matrix.value()[0].size();
		
		size_t prec = cout.precision();
		cout << fixed << showpoint << setprecision(2)
			<< "Successfully moved vehicle. \nTime taken: " 
			<< pathRes.value().timeInH << " hours.\nDistance traveled: " << pathRes.value().distanceInKm 
			<< " km.\n" << "Fuel used: " << pathRes.value().fuelUsedInL << " L.\n";
		cout << "Graphical representation of path taken: \n";
		cout << "Legend: # = Not Traversed R = Road G = Grass.\n";
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
				// Print graph, and display only the points that were traversed
				cout << ((traversedCoords.value()[r][c]) ? toString(matrix.value()[r][c].terrain) : "#");
			}
		}
		cout.precision(prec);
	} else {
		cout << errorMessage;
	}
	cout << endl;
}
