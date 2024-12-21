#include "Chicken.h"

Chicken::Chicken()
    : currentState(State::Hungry), eggAvailable(false), eggProductionTime(5.0f), eggTimer(0.0f) {
    // 创建进度条
    eggBar= cocos2d::ProgressTimer::create(cocos2d::Sprite::create("photo/startup_p/textBox.png"));
    eggBar->setType(cocos2d::ProgressTimer::Type::BAR);
    eggBar->setBarChangeRate(cocos2d::Vec2(1, 0));  // 水平进度条
    eggBar->setMidpoint(cocos2d::Vec2(0, 0));  // 从左到右
    eggBar->setPercentage(0);  // 初始进度为 0
    eggBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));  // 设置进度条的位置
    eggBar->setLocalZOrder(5);  // 设置进度条层次，确保较上层
    this->addChild(eggBar);  // 将进度条加入到建筑物中
}

Chicken::~Chicken() {
     // 清理修复计时器
    if (eggBar) {
        eggBar->removeFromParent();
    }
}

Chicken* Chicken::create(const std::string& image) {
    Chicken* ret = new Chicken();
    if (ret && ret->init(image)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Chicken::init(const std::string& image) {
    if (!Sprite::initWithFile(image)) {
        return false;
    }
    setState(State::Hungry);  // 初始状态是空腹
    return true;
}

void Chicken::setState(State newState) {
    currentState = newState;
    if (currentState == State::Full) {
        // 如果变成饱腹状态，开始计时并显示进度条
        eggTimer = eggProductionTime;
        eggBar->setPercentage(0);  // 重置进度条为 0
        eggBar->setVisible(true);  // 显示进度条
        startEggProduction(eggProductionTime);
    }
    else {
        // 如果状态是空腹，隐藏进度条
        eggBar->setVisible(false);
    }
}

Chicken::State Chicken::getState() const {
    return currentState;
}


void Chicken::startEggProduction(float timeToLayEgg) {
    eggTimer = timeToLayEgg;
    schedule([this](float dt) {
        if (currentState == State::Full) {
            eggTimer -= dt;
            // 更新进度条
            float progress = (eggProductionTime - eggTimer) / eggProductionTime * 100;
            eggBar->setPercentage(progress);  // 设置进度条的进度

            if (eggTimer <= 0.0f) {
                layEgg();  // 产蛋
                unschedule("egg_production");  // 停止蛋的生产计时
            }
        }
        }, 1.0f, "egg_production");//之后可以改速度
}

void Chicken::layEgg() {
    eggAvailable = true;  // 产蛋
}

bool Chicken::hasEgg() const {
    return eggAvailable;
}

void Chicken::collectEgg() {
    if (eggAvailable) {
        eggAvailable = false;  // 清空蛋
        eggBar->setVisible(false);  // 取完蛋后隐藏进度条
    }
}