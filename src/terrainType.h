#pragma once
#include <iostream>
#include <string>

enum class terrainType
{
	Grass,
	Road,
	Water
};

inline std::string toString(terrainType t) {
	switch (t) {
	case terrainType::Grass:
		return "G";
	case terrainType::Road:
		return "\033[1;33mR\033[0m";
	case terrainType::Water:
		return "\033[1;34mW\033[0m";
	default:
		return "Error matching string from terrainType enum.";
	}
}
