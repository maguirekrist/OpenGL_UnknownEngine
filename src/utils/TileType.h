//
// Created by magui on 9/30/2022.
//

#ifndef WORLD_CPP_TILETYPE_H
#define WORLD_CPP_TILETYPE_H

enum class TileType : std::uint8_t {
    Terrain = 1,
    Water = 2,
    WaterShallow = 3,
    Mountain = 3,
    Wall = 4
};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif //WORLD_CPP_TILETYPE_H
