#ifndef __TILE_H__
#define __TILE_H__

#include "cocos2d.h"
#include "Crop.h"

class Tile {
public:
    Tile(); // 构造函数
    void plow(); // 耕作
    void plant(Crop* crop); // 种植作物
    void water(); // 浇水
    bool isPlanted() const; // 是否已种植作物
    bool isHarvestable() const; // 是否可以收获
    Crop* getCrop() const; // 获取作物

private:
    bool plowed; // 是否已耕作
    bool watered; // 是否已浇水
    Crop* crop; // 土地上的作物
};

#endif
