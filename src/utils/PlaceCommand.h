#pragma once
#include "../Command.h"
#include "../scene/Tile.h"
#include "../scene/World.h"

class PlaceCommand : public Command
{
public:

	PlaceCommand(TileType tile, World& world) : _tileType(tile), _world(world) {};

	// Inherited via Command
	virtual void execute(glm::vec2 pos) override;

private:
	TileType _tileType;
	World& _world;
};

