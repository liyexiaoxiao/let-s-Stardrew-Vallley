#include "Crop.h"
#include "cocos2d.h"

using namespace cocos2d;

Crop::Crop(const std::string& name, const std::vector<std::string>& stages)
    : name(name), currentStage(0), stages(stages) {
    // 创建作物的第一个阶段（种子）
    sprite = Sprite::create(stages[0]);
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
    if (currentStage < stages.size() - 1) {
        currentStage++;
        sprite->setTexture(stages[currentStage]); // 更换精灵的图片
    }
}

bool Crop::isMature() const {
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
    // 如果作物还没成熟，则让其成长到下一个阶段
    if (currentStage < stages.size() - 1) {
        currentStage++;
        sprite->setTexture(stages[currentStage]); // 更新作物图像
    }
}

Crop* Crop::plantSeed(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<Crop*>>& plantedCrops) {
    // 获取地图的偏移量
    cocos2d::Vec2 mapPos = map->getPosition();
    float X = mapPos.x;
    float Y = mapPos.y;

    int offsetX = static_cast<int>(std::round(X / map->getTileSize().width));  // 根据瓦片宽度计算横向偏移
    int offsetY = static_cast<int>(std::round(Y / map->getTileSize().height)); // 根据瓦片高度计算纵向偏移


    // 检查该位置是否已经种植过作物
    if (plantedCrops[y - offsetY][x - offsetX] != nullptr) {
        return nullptr;  // 如果该位置已有作物，返回 nullptr
    }

    // 创建作物对象，假设作物有三个阶段
    std::vector<std::string> cropStages = { "photo/Farm/seed.png", "photo/Farm/growing.png", "photo/Farm/mature.png" };
    Crop* newCrop = new Crop("Crop", cropStages);

    // 获取瓦片的大小
    cocos2d::Size tileSize = map->getTileSize();  // 获取瓦片的宽度和高度

    // 根据鼠标点击的位置计算对应的瓦片坐标
    cocos2d::Vec2 tilePos = cocos2d::Vec2((x - offsetX) * tileSize.width + tileSize.width / 2,
        (y - offsetY) * tileSize.height + tileSize.height / 2);

    // 设置作物的位置为瓦片的中心
    newCrop->setPosition(tilePos);  // 将作物放置在瓦片的中心位置

    // 将作物添加到地图层中
    map->addChild(newCrop);

    // 存储作物
    plantedCrops[y - offsetY][x - offsetX] = newCrop;

    return newCrop;
}


