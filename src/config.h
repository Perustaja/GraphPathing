#pragma once
#include <stddef.h>

namespace config {
    // Graph configuration
    constexpr int gridSizeKm = 5;
	constexpr int lakeLength = 4;
	constexpr int lakeCount = 3;
	constexpr size_t width = 15;
	constexpr size_t height = 15;
    // Vehicle configuration
    constexpr int grasskmph = 40;
	constexpr int roadkmph = 100;
	constexpr int kmpl = 6;
}

struct graphConfig {
    int gridSizeKm = config::gridSizeKm;
	int lakeLength = config::lakeLength;
	int lakeCount = config::lakeCount;
	size_t height = config::height;
    size_t width = config::width;
};

struct vehicleConfig {
    int grasskmph = config::grasskmph;
	int roadkmph = config::roadkmph;
	int kmpl = config::kmpl;
};