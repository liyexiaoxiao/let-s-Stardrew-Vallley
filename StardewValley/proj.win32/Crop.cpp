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

Crop* Crop::plantSeed(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<Crop*>>& plantedCrops) {
    // ��ȡ��ͼ��ƫ����
    cocos2d::Vec2 mapPos = map->getPosition();
    float X = mapPos.x;
    float Y = mapPos.y;

    int offsetX = static_cast<int>(std::round(X / map->getTileSize().width));  // ������Ƭ��ȼ������ƫ��
    int offsetY = static_cast<int>(std::round(Y / map->getTileSize().height)); // ������Ƭ�߶ȼ�������ƫ��


    // ����λ���Ƿ��Ѿ���ֲ������
    if (plantedCrops[y - offsetY][x - offsetX] != nullptr) {
        return nullptr;  // �����λ������������� nullptr
    }

    // ����������󣬼��������������׶�
    std::vector<std::string> cropStages = { "photo/Farm/seed.png", "photo/Farm/growing.png", "photo/Farm/mature.png" };
    Crop* newCrop = new Crop("Crop", cropStages);

    // ��ȡ��Ƭ�Ĵ�С
    cocos2d::Size tileSize = map->getTileSize();  // ��ȡ��Ƭ�Ŀ�Ⱥ͸߶�

    // �����������λ�ü����Ӧ����Ƭ����
    cocos2d::Vec2 tilePos = cocos2d::Vec2((x - offsetX) * tileSize.width + tileSize.width / 2,
        (y - offsetY) * tileSize.height + tileSize.height / 2);

    // ���������λ��Ϊ��Ƭ������
    newCrop->setPosition(tilePos);  // �������������Ƭ������λ��

    // ��������ӵ���ͼ����
    map->addChild(newCrop);

    // �洢����
    plantedCrops[y - offsetY][x - offsetX] = newCrop;

    return newCrop;
}


