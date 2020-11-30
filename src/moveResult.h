#pragma once
#include "pathResult.h"
#include "vertice.h"
#include <string>
#include <optional>
#include <vector>

class moveResult {
public:
	moveResult(bool succ, std::string errMsg = "") : success(succ), errorMessage(errMsg) {}
	// Returns a successful moveResult
	static moveResult successful(const std::vector<std::pair<int, int>>& pathTrace, pathResult res, std::vector<std::vector<vertice>> m);
	// Returns a failed moveResult
	static moveResult failed(std::string msg) { return moveResult(false, msg); };
	// Prints a formatted message to standard output displaying results and trace if successful
	void displayResult() const;
	bool success = false;
	std::string errorMessage;
private:
	// Lookup matrix for coordinates traversed in move result if successful
	std::optional<std::vector<std::vector<bool>>> traversedCoords;
	// Information about path taken if successful
	std::optional<pathResult> pathRes;
	// Copy of graph at time of result for graphical display of path taken if successful
	std::optional<std::vector<std::vector<vertice>>> matrix;
};
