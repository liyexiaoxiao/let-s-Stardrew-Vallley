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
    // ������Դ
}

bool Cow::init(const std::string& image) {
    if (!Animal::init(image)) {
        return false;
    }
    // ���� Cow ���еĳ�ʼ��
    return true;
}

Cow::Cow() {
    progressBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));
    progressBar->setScale(0.5f);
}

void Cow::startProduction(float timeToProduce) {
    productionTimer = timeToProduce;
    schedule([this](float dt) {
        updateProgressBar(dt);  // ���½�����
        if (productionTimer <= 0.0f && currentState == State::Full) {
            produceMilk();  // ������
            unschedule("milk_production");
        }
        }, 0.8f, "milk_production");//ÿ��0.8�����ˢ��
}

void Cow::produceMilk() {
    productAvailable = true;
}

void Cow::collectProduct() {
    ItemStorage& storage = ItemStorage::getInstance();
    if (productAvailable) {
        productAvailable = false;
        // ����ֿ����и� `addMilk` ����
        storage.addItem(StorageID::NIUNAI, 1);//��Ʒ������1
         // ���ý�����
        productionTimer = 0.0f;  // ���ü�ʱ��
        progressBar->setPercentage(0);  // ���ý�����Ϊ 0%
    }
}