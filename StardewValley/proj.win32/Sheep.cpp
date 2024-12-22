#include "Sheep.h"
#include "ItemStorage.h"
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
    // ������Դ
}

bool Sheep::init(const std::string& image) {
    if (!Animal::init(image)) {
        return false;
    }
    // ���� Sheep ���еĳ�ʼ��
    return true;
}

void Sheep::startProduction(float timeToProduce) {
    productionTimer = timeToProduce;
    schedule([this](float dt) {
        updateProgressBar(dt);  // ���½�����
        if (productionTimer <= 0.0f && currentState == State::Full) {
            produceWool();  // ������ë
            unschedule("wool_production");
        }
        }, 0.8f, "wool_production");
}

void Sheep::produceWool() {
    productAvailable = true;
}

void Sheep::collectProduct() {
    ItemStorage& storage = ItemStorage::getInstance();
    if (productAvailable) {
        productAvailable = false;
        // ����ֿ����и� `addWool` ����
        storage.addItem(StorageID::YANGMAO, 1);//��Ʒ������1
         // ���ý�����
        productionTimer = 0.0f;  // ���ü�ʱ��
        progressBar->setPercentage(0);  // ���ý�����Ϊ 0%
    }
}