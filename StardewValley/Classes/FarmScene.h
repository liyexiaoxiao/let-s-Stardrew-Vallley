#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "Tile.h"
#include "Crop.h"
#include <vector>

class FarmScene : public cocos2d::Scene {
public:
    static FarmScene* create();
    FarmScene();
    ~FarmScene();

    void update(float dt); // 每帧更新
    void renderFarm(cocos2d::Layer* layer); // 渲染农场
    void plantCrop(int x, int y, Crop* crop); // 在指定位置种植作物
    void waterCrop(int x, int y); // 浇水

private:
    int farmWidth;
    int farmHeight;
    std::vector<std::vector<Tile>> farmGrid; // 存储农场的格子
};

#endif
