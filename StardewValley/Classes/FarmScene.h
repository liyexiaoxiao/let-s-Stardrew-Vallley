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

    void update(float dt); // ÿ֡����
    void renderFarm(cocos2d::Layer* layer); // ��Ⱦũ��
    void plantCrop(int x, int y, Crop* crop); // ��ָ��λ����ֲ����
    void waterCrop(int x, int y); // ��ˮ

private:
    int farmWidth;
    int farmHeight;
    std::vector<std::vector<Tile>> farmGrid; // �洢ũ���ĸ���
};

#endif
