#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include <vector>
#include <string>

class Crop : public cocos2d::Node {
public:
    Crop(const std::string& name, const std::vector<std::string>& stages);
    ~Crop();

    void grow(); // 作物生长
    bool isMature() const; // 判断作物是否成熟
    cocos2d::Sprite* getSprite() const; // 获取作物的 Sprite

    void setPosition(cocos2d::Vec2 position); // 设置作物的位置
    void water(); // 浇水，触发生长
    static Crop* plantSeed(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<Crop*>>& plantedCrops);


private:
    std::string name;                // 作物名称
    int currentStage;                // 当前成长阶段
    std::vector<std::string> stages; // 存储作物不同成长阶段的图片路径
    cocos2d::Sprite* sprite;         // 作物的 Sprite 对象
};

#endif // __CROP_H__
