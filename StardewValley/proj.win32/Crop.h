#pragma once
#ifndef CROP_H_ 
#define CROP_H_ 
#include "cocos2d.h"
#include <string>
#include <vector>

class Crop : public cocos2d::Node {
private:
    std::string name;
    int currentStage;
    std::vector<std::string> stages;
    cocos2d::Sprite* sprite;
    bool watered;// �Ƿ񱻽�ˮ�ı�־
    int bestseason;

public:
    Crop(const std::string& name, const std::vector<std::string>& stages);
    ~Crop();

    void grow();
    bool isMature() const;
    cocos2d::Sprite* getSprite() const;
    void setPosition(cocos2d::Vec2 position);
    void water();
    void resetWatered();  // ÿ�����ʱ���ý�ˮ״̬

    static Crop* plantSeed(int x, int y, cocos2d::TMXTiledMap* map,
        std::vector<std::vector<Crop*>>& plantedCrops,
        int cropType); // ��� cropType ����

    static void updateTileTexture(cocos2d::TMXTiledMap* map, int x, int y, bool watered);

};
#endif // CROP_H_
