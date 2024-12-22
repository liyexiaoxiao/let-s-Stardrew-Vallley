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
    // ����������
    progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("photo/startup_p/textBox.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setBarChangeRate(cocos2d::Vec2(1, 0));  // ˮƽ������
    progressBar->setMidpoint(cocos2d::Vec2(0, 0));  // ������
    progressBar->setPercentage(0);  // ��ʼ����Ϊ 0
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
        startProduction(15.0f);  // ��������ʱ��Ϊ 15 ��
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
        productionTimer -= dt;  // ÿ֡����ʣ������ʱ��

        // ������Ȱٷֱȣ�ʣ��ʱ�� / ��ʱ��
        float progress = (1.0f - productionTimer / 15.0f) * 100.0f;  // ����ٷֱ�
        progressBar->setPercentage(progress);  // ���½������İٷֱ�
    }
    else if (productionTimer <= 0.0f) {
        progressBar->setPercentage(100.0f);  // ���������ɣ�ȷ��������Ϊ 100%
    }
}