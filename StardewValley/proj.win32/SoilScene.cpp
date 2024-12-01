#include "SoilScene.h"
#include "Tile.h"
#include "Crop.h"
#include "cocos2d.h"
#include "InitialScene.h"
#include "ui/CocosGUI.h"
#include "AppDelegate.h"

SoilScene::SoilScene() : SoilSceneWidth(5), SoilSceneHeight(5) {
    // 初始化农场网格，5x5大小
    SoilSceneGrid.resize(SoilSceneHeight, std::vector<Tile>(SoilSceneWidth));
}

SoilScene::~SoilScene() {}


SoilScene* SoilScene::create() {
    SoilScene* ret = new SoilScene();
    if (ret && ret->init()) {
        // 使用捕获方式：[this] 显式捕获
        ret->schedule([ret](float dt) {
            // 使用成员函数的对象调用
            ret->update(dt);
            }, "update_key");
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}





void SoilScene::update(float dt) {
    // 更新所有作物的成长状态
    for (int i = 0; i < SoilSceneHeight; ++i) {
        for (int j = 0; j < SoilSceneWidth; ++j) {
            Tile& tile = SoilSceneGrid[i][j];
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                tile.getCrop()->grow();  // 让作物生长
            }
        }
    }
}

void SoilScene::plantCrop(int x, int y, Crop* crop) {
    if (x >= 0 && x < SoilSceneWidth && y >= 0 && y < SoilSceneHeight) {
        Tile& tile = SoilSceneGrid[y][x];

        // 检查格子是否已经被种植过
        if (tile.isPlanted()) {
            CCLOG("This tile is already planted.");
            return;  // 如果已经种植作物，返回
        }

        tile.plow();  // 松土
        tile.plant(crop);  // 种植作物
    }
    else {
        CCLOG("Invalid tile position (%d, %d).", x, y);  // 无效的位置
    }
}

void SoilScene::waterCrop(int x, int y) {
    if (x >= 0 && x < SoilSceneWidth && y >= 0 && y < SoilSceneHeight) {
        Tile& tile = SoilSceneGrid[y][x];

        // 如果作物已经种植，可以浇水
        if (tile.isPlanted() && tile.getCrop() != nullptr) {
            tile.water();  // 浇水
        }
        else {
            CCLOG("No crop planted at (%d, %d) to water.", x, y);  // 没有作物可以浇水
        }
    }
    else {
        CCLOG("Invalid tile position (%d, %d).", x, y);  // 无效的位置
    }
}

void SoilScene::renderSoilScene(cocos2d::Layer* layer) {
    CCLOG("Rendering soil scene...");

    // 获取屏幕尺寸
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 假设每个格子为 50x50 像素
    const int gridWidth = 50;
    const int gridHeight = 50;

    // 渲染农场网格
    for (int i = 0; i < SoilSceneHeight; ++i) {
        for (int j = 0; j < SoilSceneWidth; ++j) {
            Tile& tile = SoilSceneGrid[i][j];
            cocos2d::Sprite* sprite = nullptr;

            // 如果有作物，则显示作物的 Sprite，否则显示土壤的 Sprite
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                sprite = tile.getCrop()->getSprite();  // 获取作物的 Sprite
            }
            else {
                sprite = cocos2d::Sprite::create("soil1.png");  // 默认土壤的图像
            }

            // 设置位置
            sprite->setPosition(j * gridWidth + gridWidth / 2, (SoilSceneHeight - i - 1) * gridHeight + gridHeight / 2);
            layer->addChild(sprite);
        }
    }
}


bool SoilScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 创建一个 Layer 对象
    auto layer = cocos2d::Layer::create();
    this->addChild(layer);  // 将它加入到 SoilScene 中

    // 渲染土壤场景
    renderSoilScene(layer);  // 传递 layer，而不是 SoilScene

    return true;
}





