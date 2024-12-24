#include "SoilScene.h"
#include "Tile.h"
#include "Crop.h"
#include "cocos2d.h"
#include "InitialScene.h"
#include "ui/CocosGUI.h"
#include "AppDelegate.h"

SoilScene::SoilScene() : SoilSceneWidth(5), SoilSceneHeight(5) {
    // ��ʼ��ũ������5x5��С
    SoilSceneGrid.resize(SoilSceneHeight, std::vector<Tile>(SoilSceneWidth));
}

SoilScene::~SoilScene() {}


SoilScene* SoilScene::create() {
    SoilScene* ret = new SoilScene();
    if (ret && ret->init()) {
        // ʹ�ò���ʽ��[this] ��ʽ����
        ret->schedule([ret](float dt) {
            // ʹ�ó�Ա�����Ķ������
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
    // ������������ĳɳ�״̬
    for (int i = 0; i < SoilSceneHeight; ++i) {
        for (int j = 0; j < SoilSceneWidth; ++j) {
            Tile& tile = SoilSceneGrid[i][j];
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                tile.getCrop()->grow();  // ����������
            }
        }
    }
}

void SoilScene::plantCrop(int x, int y, Crop* crop) {
    if (x >= 0 && x < SoilSceneWidth && y >= 0 && y < SoilSceneHeight) {
        Tile& tile = SoilSceneGrid[y][x];

        // �������Ƿ��Ѿ�����ֲ��
        if (tile.isPlanted()) {
            CCLOG("This tile is already planted.");
            return;  // ����Ѿ���ֲ�������
        }

        tile.plow();  // ����
        tile.plant(crop);  // ��ֲ����
    }
    else {
        CCLOG("Invalid tile position (%d, %d).", x, y);  // ��Ч��λ��
    }
}

void SoilScene::waterCrop(int x, int y) {
    if (x >= 0 && x < SoilSceneWidth && y >= 0 && y < SoilSceneHeight) {
        Tile& tile = SoilSceneGrid[y][x];

        // ��������Ѿ���ֲ�����Խ�ˮ
        if (tile.isPlanted() && tile.getCrop() != nullptr) {
            tile.water();  // ��ˮ
        }
        else {
            CCLOG("No crop planted at (%d, %d) to water.", x, y);  // û��������Խ�ˮ
        }
    }
    else {
        CCLOG("Invalid tile position (%d, %d).", x, y);  // ��Ч��λ��
    }
}

void SoilScene::renderSoilScene(cocos2d::Layer* layer) {
    CCLOG("Rendering soil scene...");

    // ��ȡ��Ļ�ߴ�
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����ÿ������Ϊ 50x50 ����
    const int gridWidth = 50;
    const int gridHeight = 50;

    // ��Ⱦũ������
    for (int i = 0; i < SoilSceneHeight; ++i) {
        for (int j = 0; j < SoilSceneWidth; ++j) {
            Tile& tile = SoilSceneGrid[i][j];
            cocos2d::Sprite* sprite = nullptr;

            // ������������ʾ����� Sprite��������ʾ������ Sprite
            if (tile.isPlanted() && tile.getCrop() != nullptr) {
                sprite = tile.getCrop()->getSprite();  // ��ȡ����� Sprite
            }
            else {
                sprite = cocos2d::Sprite::create("soil1.png");  // Ĭ��������ͼ��
            }

            // ����λ��
            sprite->setPosition(j * gridWidth + gridWidth / 2, (SoilSceneHeight - i - 1) * gridHeight + gridHeight / 2);
            layer->addChild(sprite);
        }
    }
}


bool SoilScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // ����һ�� Layer ����
    auto layer = cocos2d::Layer::create();
    this->addChild(layer);  // �������뵽 SoilScene ��

    // ��Ⱦ��������
    renderSoilScene(layer);  // ���� layer�������� SoilScene

    return true;
}





