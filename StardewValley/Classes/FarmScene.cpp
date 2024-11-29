#include "FarmScene.h"
#include "Crop.h"
#include "Tile.h"
#include "cocos2d.h"

FarmScene::FarmScene() : farmWidth(10), farmHeight(10) {
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
    // ����ũ����ÿ�����ӣ�����ɳ�
    for (int i = 0; i < farmHeight; ++i) {
        for (int j = 0; j < farmWidth; ++j) {
            Tile& tile = farmGrid[i][j];
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                tile.getCrop()->grow();
            }
        }
    }
}

void FarmScene::plantCrop(int x, int y, Crop* crop) {
    if (x >= 0 && x < farmWidth && y >= 0 && y < farmHeight) {
        Tile& tile = farmGrid[y][x];
        if (!tile.isPlanted()) {
            tile.plant(crop);
        }
    }
}

void FarmScene::waterCrop(int x, int y) {
    if (x >= 0 && x < farmWidth && y >= 0 && y < farmHeight) {
        farmGrid[y][x].water();
    }
}

void FarmScene::harvestCrop(int x, int y) {
    if (x >= 0 && x < farmWidth && y >= 0 && y < farmHeight) {
        Tile& tile = farmGrid[y][x];
        if (tile.isHarvestable()) {
            tile.harvest();
        }
    }
}

void FarmScene::renderFarm(cocos2d::Layer* layer) {
    // ����ũ����ÿ�����ӵ�״̬
    for (int i = 0; i < farmHeight; ++i) {
        for (int j = 0; j < farmWidth; ++j) {
            Tile& tile = farmGrid[i][j];
            cocos2d::Sprite* sprite = nullptr;
            if (tile.isPlanted()) {
                sprite = cocos2d::Sprite::create("crop.png"); // �������� crop.png ͼƬ
                if (tile.getCrop()->isMature()) {
                    sprite->setColor(cocos2d::Color3B::GREEN);
                }
            }
            else {
                sprite = cocos2d::Sprite::create("soil.png"); // �������� soil.png ͼƬ
            }
            sprite->setPosition(j * 50, i * 50);  // ÿ����50px
            layer->addChild(sprite);
        }
    }
}
