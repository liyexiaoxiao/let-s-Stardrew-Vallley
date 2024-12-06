#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include <vector>
#include <string>

class Crop : public cocos2d::Node {
public:
    Crop(const std::string& name, const std::vector<std::string>& stages);
    ~Crop();

    void grow(); // ��������
    bool isMature() const; // �ж������Ƿ����
    cocos2d::Sprite* getSprite() const; // ��ȡ����� Sprite

    void setPosition(cocos2d::Vec2 position); // ���������λ��
    void water(); // ��ˮ����������
    static Crop* plantSeed(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<Crop*>>& plantedCrops);


private:
    std::string name;                // ��������
    int currentStage;                // ��ǰ�ɳ��׶�
    std::vector<std::string> stages; // �洢���ﲻͬ�ɳ��׶ε�ͼƬ·��
    cocos2d::Sprite* sprite;         // ����� Sprite ����
};

#endif // __CROP_H__
