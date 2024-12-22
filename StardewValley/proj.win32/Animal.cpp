// Animal.cpp
#include"Animal.h"

bool Animal::init(const std::string& image) {
    if (!Sprite::initWithFile(image)) {
        return false;
    }
    return true;
}

Animal::Animal()
    : currentState(State::Hungry), productAvailable(false), productionTimer(0.0f), progressBar(nullptr) {
    // 创建进度条
    progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("photo/startup_p/textBox.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setBarChangeRate(cocos2d::Vec2(1, 0));  // 水平进度条
    progressBar->setMidpoint(cocos2d::Vec2(0, 0));  // 从左到右
    progressBar->setPercentage(0);  // 初始进度为 0
    this->addChild(progressBar);
}

Animal::~Animal() {
    if (progressBar) {
        progressBar->removeFromParent();
    }
}

void Animal::setState(State newState) {
    currentState = newState;
    if (currentState == State::Full) {
        startProduction(15.0f);  // 假设生产时间为 15 秒
    }
}

Animal::State Animal::getState() const {
    return currentState;
}

bool Animal::hasProduct() const {
    return productAvailable;
}

void Animal::updateProgressBar(float dt) {
    if (progressBar && productionTimer > 0.0f) {
        productionTimer -= dt;  // 每帧减少剩余生产时间

        // 计算进度百分比：剩余时间 / 总时间
        float progress = (1.0f - productionTimer / 15.0f) * 100.0f;  // 计算百分比
        progressBar->setPercentage(progress);  // 更新进度条的百分比
    }
    else if (productionTimer <= 0.0f) {
        progressBar->setPercentage(100.0f);  // 如果生产完成，确保进度条为 100%
    }
}