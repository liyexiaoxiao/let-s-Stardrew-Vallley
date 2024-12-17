#include "WateredLand.h"
#include "FarmScene.h"
WateredLand* WateredLand::create() {
    WateredLand* ret = new WateredLand();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool WateredLand::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 设置土地的贴图
    this->setTexture("photo/Farm/WateredLand.png");

    return true;
}

WateredLand* WateredLand::waterLand(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<WateredLand*>>& wateredLand) {
    // 获取地图的偏移量
    cocos2d::Vec2 mapPos = map->getPosition();
    cocos2d::Size tileSize = map->getTileSize();

    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;

    // 检查是否已经浇水
    if (wateredLand[adjustedY][adjustedX] != nullptr) {
        return nullptr; // 如果土地已经浇水，返回 nullptr
    }

    // 创建新土地
    WateredLand* newWateredLand = WateredLand::create();
    newWateredLand->setPosition((adjustedX)*tileSize.width + tileSize.width / 2,
        (adjustedY)*tileSize.height + tileSize.height / 2);

    // 添加到地图层
    map->addChild(newWateredLand, 1); // Z 轴较低

    // 更新 WateredLand 数组
    wateredLand[adjustedY][adjustedX] = newWateredLand;

    return newWateredLand;
}
