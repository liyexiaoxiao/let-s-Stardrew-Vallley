#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "Tile.h"
#include <vector>

class FarmScene : public cocos2d::Scene {
public:
    static FarmScene* create();
    FarmScene();
    ~FarmScene();

    void update(float dt);
    void plantCrop(int x, int y, Crop* crop);
    void waterCrop(int x, int y);
    void harvestCrop(int x, int y);
    void renderFarm(cocos2d::Layer* layer);

private:
    std::vector<std::vector<Tile>> farmGrid;
    int farmWidth;
    int farmHeight;
};

#endif

#pragma once
