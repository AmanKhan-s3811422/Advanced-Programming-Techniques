#include "Tile.h"

// Empty... for now?

std::string Tile::getTileCode()
{
	std::stringstream str;
	str << colour << shape;
	std::string s = str.str();
	return str.str();
}
