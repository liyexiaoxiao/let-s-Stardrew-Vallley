#include "Sheep.h"
Sheep::Sheep() {
    progressBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));
    progressBar->setScale(0.5f);
}

Sheep* Sheep::create(const std::string& image) {
    Sheep* sheep = new Sheep();
    if (sheep && sheep->init(image)) {
        sheep->autorelease();
        return sheep;
    }
    CC_SAFE_DELETE(sheep);
    return nullptr;
}

Sheep::~Sheep() {
    // 清理资源
}

bool Sheep::init(const std::string& image) {
    if (!Animal::init(image)) {
        return false;
    }
    // 其他 Sheep 特有的初始化
    return true;
}

void Sheep::startProduction(float timeToProduce) {
    productionTimer = timeToProduce;
    schedule([this](float dt) {
        updateProgressBar(dt);  // 更新进度条
        if (productionTimer <= 0.0f && currentState == State::Full) {
            produceWool();  // 生产羊毛
            unschedule("wool_production");
        }
        }, 0.8f, "wool_production");
}

void Sheep::produceWool() {
    productAvailable = true;
}

void Sheep::collectProduct() {
    if (productAvailable) {
        productAvailable = false;
        // 假设仓库类有个 `addWool` 方法
        //Warehouse::getInstance()->addWool();
         // 重置进度条
        productionTimer = 0.0f;  // 重置计时器
        progressBar->setPercentage(0);  // 重置进度条为 0%
    }
}