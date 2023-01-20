#include "PlaceCommand.h"

void PlaceCommand::execute(glm::vec2 pos)
{
	_world.placeTile(Tile(glm::tvec3<int>(pos.x, pos.y, 0), 16, 16, _tileType));
}
