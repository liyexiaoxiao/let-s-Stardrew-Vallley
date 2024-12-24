// Cow.cpp
#include"Cow.h"
#include "ItemStorage.h"
Cow* Cow::create(const std::string& image) {
    Cow* cow = new Cow();
    if (cow && cow->init(image)) {
        cow->autorelease();
        return cow;
    }
    CC_SAFE_DELETE(cow);
    return nullptr;
}

Cow::~Cow() {
    // 清理资源
}

bool Cow::init(const std::string& image) {
    if (!Animal::init(image)) {
        return false;
    }
    // 其他 Cow 特有的初始化
    return true;
}

Cow::Cow() {
    progressBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));
    progressBar->setScale(0.5f);
}

void Cow::startProduction(float timeToProduce) {
    productionTimer = timeToProduce;
    schedule([this](float dt) {
        updateProgressBar(dt);  // 更新进度条
        if (productionTimer <= 0.0f && currentState == State::Full) {
            produceMilk();  // 生产奶
            unschedule("milk_production");
        }
        }, 0.8f, "milk_production");//每过0.8秒进行刷新
}

void Cow::produceMilk() {
    productAvailable = true;
}

void Cow::collectProduct() {
    ItemStorage& storage = ItemStorage::getInstance();
    if (productAvailable) {
        productAvailable = false;
        // 假设仓库类有个 `addMilk` 方法
        storage.addItem(StorageID::NIUNAI, 1);//物品数量加1
         // 重置进度条
        productionTimer = 0.0f;  // 重置计时器
        progressBar->setPercentage(0);  // 重置进度条为 0%
    }
}