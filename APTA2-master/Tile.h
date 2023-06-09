#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include <sstream>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
	Colour colour;
	Shape  shape;

	std::string getTileCode();
};

#endif // ASSIGN2_TILE_H
