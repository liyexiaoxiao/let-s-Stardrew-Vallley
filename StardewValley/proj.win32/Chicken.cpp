#include "Chicken.h"
#include "ItemStorage.h"
Chicken::Chicken()
    {
    //����������λ��
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
    // ������Դ
}

bool Chicken::init(const std::string& image) {
    if (!Animal::init(image)) {
        return false;
    }
    // ���� Chicken ���еĳ�ʼ��
    return true;
}

void Chicken::startProduction(float timeToProduce) {
    productionTimer = timeToProduce;
    schedule([this](float dt) {
        updateProgressBar(dt);  // ���½�����
        if (productionTimer <= 0.0f && currentState == State::Full) {
            layEgg();  // ������
            unschedule("egg_production");
        }
        }, 0.8f, "egg_production");//ÿ��0.8�����ˢ��
}

void Chicken::layEgg() {
    productAvailable = true;
}

void Chicken::collectProduct() {
    ItemStorage& storage = ItemStorage::getInstance();
    if (productAvailable) {
        productAvailable = false;
        // ����ֿ����и� `addEgg` ����
        storage.addItem(StorageID::EGG, 1);//��Ʒ������1
         // ���ý�����
        productionTimer = 0.0f;  // ���ü�ʱ��
        progressBar->setPercentage(0);  // ���ý�����Ϊ 0%
    }
}