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
    // 更新所有作物的成长状态
    for (int i = 0; i < farmHeight; ++i) {
        for (int j = 0; j < farmWidth; ++j) {
            Tile& tile = farmGrid[i][j];
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                tile.getCrop()->grow(); // 让作物生长
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
    // 渲染农场
    for (int i = 0; i < farmHeight; ++i) {
        for (int j = 0; j < farmWidth; ++j) {
            Tile& tile = farmGrid[i][j];
            cocos2d::Sprite* sprite = nullptr;
            if (tile.isPlanted()) {
                sprite = tile.getCrop()->getSprite(); // 获取作物的 Sprite
            }
            else {
                sprite = cocos2d::Sprite::create("soil.png"); // 假设你有 soil.png 图片
            }
            sprite->setPosition(j * 50, i * 50);  // 每格子50px
            layer->addChild(sprite);
        }
    }
}
