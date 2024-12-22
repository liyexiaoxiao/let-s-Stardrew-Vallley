#include "Crop.h"
#include "cocos2d.h"
#include "Clock.h"
using namespace cocos2d;

Crop::Crop(const std::string& name, const std::vector<std::string>& stages)
    : name(name), currentStage(0), stages(stages) {
    // 创建作物的第一个阶段（种子）
    sprite = Sprite::create(stages[0]);
    switch (bestseason=1) {
    case 1:Bestseason = "Spring";
        break;
    case 2:Bestseason = "Summer";
        break;
    case 3:Bestseason = "Autumn";
        break;
    case 4:Bestseason = "Winter";
        break;
    }

    Clock* clock = Clock::getInstance();
    if (Bestseason == clock->getSeason()) {
        neededwatereddays = 1;
    }
    else
        neededwatereddays = 2;
    watered = false;
    watereddays = 0;
        
    this->addChild(sprite); // 将作物精灵添加到节点中
}

Crop::~Crop() {
    // 释放精灵资源
    if (sprite) {
        sprite->removeFromParent();
    }
}

void Crop::grow() {
    // 如果作物尚未成熟，增加阶段并更新精灵图像
    if (currentStage < stages.size() - 2) {
        currentStage++;
        sprite->setTexture(stages[currentStage]); // 更换精灵的图片
    }
}

bool Crop::isMature() const {
    // 判断作物是否已经成熟
    return currentStage == stages.size() - 2;
}

bool Crop::isDead() const {
    // 判断作物是否已经成熟
    return currentStage == stages.size() - 1;
}

Sprite* Crop::getSprite() const {
    return sprite; // 返回作物的精灵对象
}

void Crop::setPosition(cocos2d::Vec2 position) {
    sprite->setPosition(position); // 设置作物精灵的位置
}

void Crop::water() {
    watered = true;  // 标记为已浇水
};


void Crop::resetWatered() {
    if (watered == true) {
        watereddays++;
        //if (watereddays == neededwatereddays) {
            grow();
        //}
    }
    watered = false;
    
}

void Crop::notWatered() {
     sprite->setTexture(stages[stages.size() - 1]);// 前一天未浇水，植物枯萎
     currentStage = stages.size() - 1;
     watered = false;  // 每天开始时重置浇水状态
}



Crop* Crop::plantSeed(int x, int y, cocos2d::TMXTiledMap* map,
    std::vector<std::vector<Crop*>>& plantedCrops,
    int cropType) { // 添加 cropType 参数
    // 获取地图的偏移量
    cocos2d::Vec2 mapPos = map->getPosition();
    float X = mapPos.x;
    float Y = mapPos.y;

    int offsetX = static_cast<int>(std::round(X / map->getTileSize().width));
    int offsetY = static_cast<int>(std::round(Y / map->getTileSize().height));

    // 检查该位置是否已经种植过作物
    if (plantedCrops[y - offsetY][x - offsetX] != nullptr) {
        return nullptr; // 如果该位置已有作物，返回 nullptr
    }

    // 根据 cropType 选择作物的阶段贴图
    std::vector<std::string> cropStages;
    switch (cropType) {
    case 1:
        cropStages = { "photo/Farm/crop1_seed.png", "photo/Farm/crop1_growing1.png",
                       "photo/Farm/crop1_growing2.png", "photo/Farm/crop1_mature.png", "photo/Farm/wilted_crop.png" };
        break;
    case 2:
        cropStages = { "photo/Farm/crop2_seed.png", "photo/Farm/crop2_growing1.png",
                       "photo/Farm/crop2_growing2.png", "photo/Farm/crop2_growing3.png","photo/Farm/crop2_mature.png", "photo/Farm/wilted_crop.png" };
        break;
    case 3:
        cropStages = { "photo/Farm/crop3_seed.png", "photo/Farm/crop3_growing1.png",
                       "photo/Farm/crop3_growing2.png", "photo/Farm/crop3_growing3.png","photo/Farm/crop3_mature.png", "photo/Farm/wilted_crop.png" };
        break;
    case 4:
        cropStages = { "photo/Farm/crop4_seed.png", "photo/Farm/crop4_growing1.png",
                       "photo/Farm/crop4_growing2.png", "photo/Farm/crop4_mature.png", "photo/Farm/wilted_crop.png" };
        break;
    default:
        return nullptr; // 如果 cropType 无效，返回 nullptr
    }

    // 创建作物对象
    Crop* newCrop = new Crop("Crop", cropStages);
    newCrop->croptype = cropType;
    newCrop->bestseason = cropType;

    // 获取瓦片的大小
    cocos2d::Size tileSize = map->getTileSize();

    // 根据鼠标点击的位置计算对应的瓦片坐标
    float Cropheight = std::min((newCrop->getSprite()->getContentSize().height)/ 2, tileSize.height / 2);
    cocos2d::Vec2 tilePos = cocos2d::Vec2((x - offsetX) * tileSize.width + tileSize.width / 2,
        (y - offsetY+1) * tileSize.height- Cropheight);
    
    // 设置作物的位置为瓦片的中心
    newCrop->setPosition(cocos2d::Vec2(tilePos));
    newCrop->setLocalZOrder(2); // 设置较高的 Z 轴层级

    // 将作物添加到地图层中
    map->addChild(newCrop);

    // 存储作物
    plantedCrops[y - offsetY][x - offsetX] = newCrop;

    return newCrop;
}


