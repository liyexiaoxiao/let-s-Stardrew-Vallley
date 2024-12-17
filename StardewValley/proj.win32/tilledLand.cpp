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

    // �������ص���ͼ
    this->setTexture("photo/Farm/tilledLand.png");
   
    return true;
}

TilledLand* TilledLand::tillLand(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<TilledLand*>>& tilledLand) {
    // ��ȡ��ͼ��ƫ����
    cocos2d::Vec2 mapPos = map->getPosition();
    cocos2d::Size tileSize = map->getTileSize();

    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;

    // ����Ƿ��Ѿ�����
    if (tilledLand[adjustedY][adjustedX] != nullptr) {
        return nullptr; // ��������Ѿ����ѣ����� nullptr
    }
   
    // ����������
    TilledLand* newTilledLand = TilledLand::create();
    newTilledLand->setPosition((adjustedX) * tileSize.width + tileSize.width / 2,
        (adjustedY) * tileSize.height + tileSize.height / 2);

    // ��ӵ���ͼ��
    map->addChild(newTilledLand, 1); // Z ��ϵ�

    // ���� tilledLand ����
    tilledLand[adjustedY][adjustedX] = newTilledLand;

    return newTilledLand;
}
