#include "Chicken.h"
#include "ItemStorage.h"
Chicken::Chicken()
    {
    //调整进度条位置
    progressBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));
    progressBar->setScale(0.5f);
}


Chicken* Chicken::create(const std::string& image) {
    Chicken* sheep = new Chicken();
    if (sheep && sheep->init(image)) {
        sheep->autorelease();
        return sheep;
    }
    CC_SAFE_DELETE(sheep);
    return nullptr;
}

Chicken::~Chicken() {
    // 清理资源
}

bool Chicken::init(const std::string& image) {
    if (!Animal::init(image)) {
        return false;
    }
    // 其他 Chicken 特有的初始化
    return true;
}

void Chicken::startProduction(float timeToProduce) {
    productionTimer = timeToProduce;
    schedule([this](float dt) {
        updateProgressBar(dt);  // 更新进度条
        if (productionTimer <= 0.0f && currentState == State::Full) {
            layEgg();  // 生产奶
            unschedule("egg_production");
        }
        }, 0.8f, "egg_production");//每过0.8秒进行刷新
}

void Chicken::layEgg() {
    productAvailable = true;
}

void Chicken::collectProduct() {
    ItemStorage& storage = ItemStorage::getInstance();
    if (productAvailable) {
        productAvailable = false;
        // 假设仓库类有个 `addEgg` 方法
        storage.addItem(StorageID::EGG, 1);//物品数量加1
         // 重置进度条
        productionTimer = 0.0f;  // 重置计时器
        progressBar->setPercentage(0);  // 重置进度条为 0%
    }
}