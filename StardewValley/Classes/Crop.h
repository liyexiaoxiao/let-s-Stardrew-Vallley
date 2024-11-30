#ifndef __CROP_H__
#define __CROP_H__

#include <vector>
#include <string>
#include "cocos2d.h"

class Crop {
public:
    Crop(const std::string& name, const std::vector<std::string>& stages);
    void grow(); // 作物生长
    bool isMature() const; // 作物是否成熟
    cocos2d::Sprite* getSprite() const; // 获取作物对应的Sprite
    void setPosition(cocos2d::Vec2 position); // 设置作物位置

private:
    std::string name;
    int currentAge; // 当前生长阶段
    std::vector<std::string> stages; // 不同阶段对应的图片路径
    cocos2d::Sprite* sprite; // 作物的Sprite
};

#endif
