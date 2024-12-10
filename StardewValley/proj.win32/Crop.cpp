#include "Crop.h"
#include "cocos2d.h"
using namespace cocos2d;

Crop::Crop(const std::string& name, const std::vector<std::string>& stages)
    : name(name), currentStage(0), stages(stages) {
    // ��������ĵ�һ���׶Σ����ӣ�
    sprite = Sprite::create(stages[0]);
    this->addChild(sprite); // �����ﾫ����ӵ��ڵ���
}

Crop::~Crop() {
    // �ͷž�����Դ
    if (sprite) {
        sprite->removeFromParent();
    }
}

void Crop::grow() {
    // ���������δ���죬���ӽ׶β����¾���ͼ��
    if (currentStage < stages.size() - 1) {
        currentStage++;
        sprite->setTexture(stages[currentStage]); // ���������ͼƬ
    }
}

bool Crop::isMature() const {
    // �ж������Ƿ��Ѿ�����
    return currentStage == stages.size() - 1;
}

Sprite* Crop::getSprite() const {
    return sprite; // ��������ľ������
}

void Crop::setPosition(cocos2d::Vec2 position) {
    sprite->setPosition(position); // �������ﾫ���λ��
}

void Crop::water() {
    // ������ﻹû���죬������ɳ�����һ���׶�
    if (currentStage < stages.size() - 1) {
        currentStage++;
        sprite->setTexture(stages[currentStage]); // ��������ͼ��
    }
}

Crop* Crop::plantSeed(int x, int y, cocos2d::TMXTiledMap* map,
    std::vector<std::vector<Crop*>>& plantedCrops,
    int cropType) { // ��� cropType ����
    // ��ȡ��ͼ��ƫ����
    cocos2d::Vec2 mapPos = map->getPosition();
    float X = mapPos.x;
    float Y = mapPos.y;

    int offsetX = static_cast<int>(std::round(X / map->getTileSize().width));
    int offsetY = static_cast<int>(std::round(Y / map->getTileSize().height));

    // ����λ���Ƿ��Ѿ���ֲ������
    if (plantedCrops[y - offsetY][x - offsetX] != nullptr) {
        return nullptr; // �����λ������������� nullptr
    }

    // ���� cropType ѡ������Ľ׶���ͼ
    std::vector<std::string> cropStages;
    switch (cropType) {
    case 1:
        cropStages = { "photo/Farm/crop1_seed.png", "photo/Farm/crop1_growing1.png",
                       "photo/Farm/crop1_growing2.png", "photo/Farm/crop1_mature.png" };
        break;
    case 2:
        cropStages = { "photo/Farm/crop2_seed.png", "photo/Farm/crop2_growing1.png",
                       "photo/Farm/crop2_growing2.png", "photo/Farm/crop2_growing3.png","photo/Farm/crop2_mature.png" };
        break;
    case 3:
        cropStages = { "photo/Farm/crop3_seed.png", "photo/Farm/crop3_growing1.png",
                       "photo/Farm/crop3_growing2.png", "photo/Farm/crop3_growing3.png","photo/Farm/crop3_mature.png" };
        break;
    case 4:
        cropStages = { "photo/Farm/crop4_seed.png", "photo/Farm/crop4_growing1.png",
                       "photo/Farm/crop4_growing2.png", "photo/Farm/crop4_mature.png" };
        break;
    default:
        return nullptr; // ��� cropType ��Ч������ nullptr
    }

    // �����������
    Crop* newCrop = new Crop("Crop", cropStages);

    // ��ȡ��Ƭ�Ĵ�С
    cocos2d::Size tileSize = map->getTileSize();

    // �����������λ�ü����Ӧ����Ƭ����
    float Cropheight = std::min((newCrop->getSprite()->getContentSize().height)/ 2, tileSize.height / 2);
    cocos2d::Vec2 tilePos = cocos2d::Vec2((x - offsetX) * tileSize.width + tileSize.width / 2,
        (y - offsetY+1) * tileSize.height- Cropheight);
    
    // ���������λ��Ϊ��Ƭ������
    newCrop->setPosition(cocos2d::Vec2(tilePos));
    newCrop->setLocalZOrder(2); // ���ýϸߵ� Z ��㼶

    // ��������ӵ���ͼ����
    map->addChild(newCrop);

    // �洢����
    plantedCrops[y - offsetY][x - offsetX] = newCrop;

    return newCrop;
}
