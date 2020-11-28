#pragma once
#include "string"
#include <optional>
#include <vector>

class moveResult
{
public:
	moveResult(bool succ, std::string errMsg = "") : success(succ), errorMessage(errMsg) {}
	// Returns a successful moveResult
	static moveResult successful(std::vector<std::pair<int, int>> pathTrace_) { moveResult mr(true, ""); mr.pathTrace = pathTrace_; return mr; };
	// Returns a failed moveResult
	static moveResult failure(std::string msg) { return moveResult(false, msg); };
	// Prints a formatted message to standard output
	void displayResult() const;
	bool success = false;
	std::string errorMessage;
private:
	std::optional<std::vector<std::pair<int, int>>> pathTrace;
};

