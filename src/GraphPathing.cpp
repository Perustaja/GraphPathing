#include "config.h"
#include "presentationWrapper.h"
#include "vehicle.h"

int main()
{
	// Arrange configuration structs and pass to wrapper
	graphConfig gc;
	vehicleConfig vc;
	presentationWrapper p(gc, vc);
	p.run();
}