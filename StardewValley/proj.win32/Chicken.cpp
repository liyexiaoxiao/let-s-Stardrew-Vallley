#include "Chicken.h"

Chicken::Chicken()
    : currentState(State::Hungry), eggAvailable(false), eggProductionTime(5.0f), eggTimer(0.0f) {
    // ����������
    eggBar= cocos2d::ProgressTimer::create(cocos2d::Sprite::create("photo/startup_p/textBox.png"));
    eggBar->setType(cocos2d::ProgressTimer::Type::BAR);
    eggBar->setBarChangeRate(cocos2d::Vec2(1, 0));  // ˮƽ������
    eggBar->setMidpoint(cocos2d::Vec2(0, 0));  // ������
    eggBar->setPercentage(0);  // ��ʼ����Ϊ 0
    eggBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));  // ���ý�������λ��
    eggBar->setLocalZOrder(5);  // ���ý�������Σ�ȷ�����ϲ�
    this->addChild(eggBar);  // �����������뵽��������
}

Chicken::~Chicken() {
     // �����޸���ʱ��
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
    setState(State::Hungry);  // ��ʼ״̬�ǿո�
    return true;
}

void Chicken::setState(State newState) {
    currentState = newState;
    if (currentState == State::Full) {
        // �����ɱ���״̬����ʼ��ʱ����ʾ������
        eggTimer = eggProductionTime;
        eggBar->setPercentage(0);  // ���ý�����Ϊ 0
        eggBar->setVisible(true);  // ��ʾ������
        startEggProduction(eggProductionTime);
    }
    else {
        // ���״̬�ǿո������ؽ�����
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
            // ���½�����
            float progress = (eggProductionTime - eggTimer) / eggProductionTime * 100;
            eggBar->setPercentage(progress);  // ���ý������Ľ���

            if (eggTimer <= 0.0f) {
                layEgg();  // ����
                unschedule("egg_production");  // ֹͣ����������ʱ
            }
        }
        }, 1.0f, "egg_production");//֮����Ը��ٶ�
}

void Chicken::layEgg() {
    eggAvailable = true;  // ����
}

bool Chicken::hasEgg() const {
    return eggAvailable;
}

void Chicken::collectEgg() {
    if (eggAvailable) {
        eggAvailable = false;  // ��յ�
        eggBar->setVisible(false);  // ȡ�군�����ؽ�����
    }
}