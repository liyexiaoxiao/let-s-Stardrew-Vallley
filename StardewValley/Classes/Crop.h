#ifndef __CROP_H__
#define __CROP_H__

#include <vector>
#include <string>
#include "cocos2d.h"

class Crop {
public:
    Crop(const std::string& name, const std::vector<std::string>& stages);
    void grow(); // ��������
    bool isMature() const; // �����Ƿ����
    cocos2d::Sprite* getSprite() const; // ��ȡ�����Ӧ��Sprite
    void setPosition(cocos2d::Vec2 position); // ��������λ��

private:
    std::string name;
    int currentAge; // ��ǰ�����׶�
    std::vector<std::string> stages; // ��ͬ�׶ζ�Ӧ��ͼƬ·��
    cocos2d::Sprite* sprite; // �����Sprite
};

#endif
