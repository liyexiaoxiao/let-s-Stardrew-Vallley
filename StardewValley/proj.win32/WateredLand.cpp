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

    // �������ص���ͼ
    this->setTexture("photo/Farm/WateredLand.png");

    return true;
}

WateredLand* WateredLand::waterLand(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<WateredLand*>>& wateredLand) {
    // ��ȡ��ͼ��ƫ����
    cocos2d::Vec2 mapPos = map->getPosition();
    cocos2d::Size tileSize = map->getTileSize();

    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;

    // ����Ƿ��Ѿ���ˮ
    if (wateredLand[adjustedY][adjustedX] != nullptr) {
        return nullptr; // ��������Ѿ���ˮ������ nullptr
    }

    // ����������
    WateredLand* newWateredLand = WateredLand::create();
    newWateredLand->setPosition((adjustedX)*tileSize.width + tileSize.width / 2,
        (adjustedY)*tileSize.height + tileSize.height / 2);

    // ��ӵ���ͼ��
    map->addChild(newWateredLand, 1); // Z ��ϵ�

    // ���� WateredLand ����
    wateredLand[adjustedY][adjustedX] = newWateredLand;

    return newWateredLand;
}
