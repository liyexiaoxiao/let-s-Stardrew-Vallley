#ifndef __SOIL_SCENE_H__
#define __SOIL_SCENE_H__

#include "cocos2d.h"
#include "Tile.h"
#include "Crop.h"
#include <vector>

class SoilScene : public cocos2d::Scene {
public:
    // ���������ľ�̬����
    static SoilScene* create();

    // ���캯������������
    SoilScene();
    ~SoilScene();

    // ÿ֡����
    void update(float dt);

    // ��Ⱦũ������
    void renderSoilScene(cocos2d::Layer* layer);

    // ��ָ��λ����ֲ����
    void plantCrop(int x, int y, Crop* crop);

    // ��ָ��λ�ý�ˮ
    void waterCrop(int x, int y);

private:
    // ũ���Ŀ�Ⱥ͸߶�
    int SoilSceneWidth;
    int SoilSceneHeight;

    // �洢ũ���ĸ���
    std::vector<std::vector<Tile>> SoilSceneGrid;

    // ��ʼ��ũ�������Ĵ�С����������
    bool init();

};

#endif // __SOIL_SCENE_H__
