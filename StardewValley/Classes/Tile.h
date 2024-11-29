#ifndef __TILE_H__
#define __TILE_H__

#include "Crop.h"

class Tile {
public:
    Tile();
    void plow();
    void plant(Crop* crop);
    void water();
    void harvest();
    bool isPlanted() const;
    bool isHarvestable() const;
    Crop* getCrop() const;

private:
    bool plowed;
    bool watered;
    Crop* crop;
};

#endif
#pragma once
