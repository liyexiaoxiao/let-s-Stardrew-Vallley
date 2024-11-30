#include "FarmScene.h"
#include "Tile.h"
#include "Crop.h"
#include "cocos2d.h"

FarmScene::FarmScene() : farmWidth(5), farmHeight(5) {
    farmGrid.resize(farmHeight, std::vector<Tile>(farmWidth));
}

FarmScene::~FarmScene() {}

FarmScene* FarmScene::create() {
    FarmScene* ret = new FarmScene();
    if (ret && ret->init()) {
        ret->schedule([=](float dt) { update(dt); }, "update_key");
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

void FarmScene::update(float dt) {
    // ������������ĳɳ�״̬
    for (int i = 0; i < farmHeight; ++i) {
        for (int j = 0; j < farmWidth; ++j) {
            Tile& tile = farmGrid[i][j];
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                tile.getCrop()->grow(); // ����������
            }
        }
    }
}

void FarmScene::plantCrop(int x, int y, Crop* crop) {
    if (x >= 0 && x < farmWidth && y >= 0 && y < farmHeight) {
        Tile& tile = farmGrid[y][x];
        tile.plow();
        tile.plant(crop);
    }
}

void FarmScene::waterCrop(int x, int y) {
    if (x >= 0 && x < farmWidth && y >= 0 && y < farmHeight) {
        Tile& tile = farmGrid[y][x];
        tile.water();
    }
}

void FarmScene::renderFarm(cocos2d::Layer* layer) {
    // ��Ⱦũ��
    for (int i = 0; i < farmHeight; ++i) {
        for (int j = 0; j < farmWidth; ++j) {
            Tile& tile = farmGrid[i][j];
            cocos2d::Sprite* sprite = nullptr;
            if (tile.isPlanted()) {
                sprite = tile.getCrop()->getSprite(); // ��ȡ����� Sprite
            }
            else {
                sprite = cocos2d::Sprite::create("soil.png"); // �������� soil.png ͼƬ
            }
            sprite->setPosition(j * 50, i * 50);  // ÿ����50px
            layer->addChild(sprite);
        }
    }
}
