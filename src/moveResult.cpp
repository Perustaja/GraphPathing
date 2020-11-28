#include "moveResult.h"
#include "iostream"

using std::cout; using std::endl;
using std::string; 

void moveResult::displayResult() const{
	if (pathTrace.has_value()) {
		cout << "Successfully moved vehicle. Coordinates taken to reach destination: \n";
		for (int i = 0; i < pathTrace.value().size(); i++) 
			cout << "(" << pathTrace.value()[i].first << ", " << pathTrace.value()[i].second << ") ";
	} else {
		cout << errorMessage;
	}
	cout << endl;
}