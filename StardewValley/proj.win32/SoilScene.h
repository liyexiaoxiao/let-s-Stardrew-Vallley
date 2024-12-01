#ifndef __SOIL_SCENE_H__
#define __SOIL_SCENE_H__

#include "cocos2d.h"
#include "Tile.h"
#include "Crop.h"
#include <vector>

class SoilScene : public cocos2d::Scene {
public:
    // 创建场景的静态方法
    static SoilScene* create();

    // 构造函数与析构函数
    SoilScene();
    ~SoilScene();

    // 每帧更新
    void update(float dt);

    // 渲染农场场景
    void renderSoilScene(cocos2d::Layer* layer);

    // 在指定位置种植作物
    void plantCrop(int x, int y, Crop* crop);

    // 在指定位置浇水
    void waterCrop(int x, int y);

private:
    // 农场的宽度和高度
    int SoilSceneWidth;
    int SoilSceneHeight;

    // 存储农场的格子
    std::vector<std::vector<Tile>> SoilSceneGrid;

    // 初始化农场场景的大小及其他设置
    bool init();

};

#endif // __SOIL_SCENE_H__
