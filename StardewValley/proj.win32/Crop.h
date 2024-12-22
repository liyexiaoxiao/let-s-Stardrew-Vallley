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
    int bestseason;
    std::string Bestseason;

public:
    Crop(const std::string& name, const std::vector<std::string>& stages);
    ~Crop();
    int croptype;
    int watereddays=0;
    int neededwatereddays;
    bool watered;// �Ƿ񱻽�ˮ�ı�־
    void grow();
    bool isMature() const;
    bool isDead() const ;
    cocos2d::Sprite* getSprite() const;
    void setPosition(cocos2d::Vec2 position);
    void water();
    void resetWatered();  // ÿ�����ʱ���ý�ˮ״̬
    void notWatered();

    static Crop* plantSeed(int x, int y, cocos2d::TMXTiledMap* map,
        std::vector<std::vector<Crop*>>& plantedCrops,
        int cropType); // ��� cropType ����


};
#endif // CROP_H_
