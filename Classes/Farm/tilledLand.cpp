#include "tilledLand.h"
#include "FarmScene.h"
TilledLand* TilledLand::create() {
    TilledLand* ret = new TilledLand();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TilledLand::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 设置土地的贴图
    this->setTexture("photo/Farm/tilledLand.png");
   
    return true;
}

TilledLand* TilledLand::tillLand(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<TilledLand*>>& tilledLand) {
    // 获取地图的偏移量
    cocos2d::Vec2 mapPos = map->getPosition();
    cocos2d::Size tileSize = map->getTileSize();

    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;

    // 检查是否已经开垦
    if (tilledLand[adjustedY][adjustedX] != nullptr) {
        return nullptr; // 如果土地已经开垦，返回 nullptr
    }
   
    // 创建新土地
    TilledLand* newTilledLand = TilledLand::create();
    newTilledLand->setPosition((adjustedX) * tileSize.width + tileSize.width / 2,
        (adjustedY) * tileSize.height + tileSize.height / 2);

    // 添加到地图层
    map->addChild(newTilledLand, 1); // Z 轴较低

    // 更新 tilledLand 数组
    tilledLand[adjustedY][adjustedX] = newTilledLand;

    return newTilledLand;
}
