#include "Coop.h"

Coop::Coop()
    : chicken1(nullptr), chicken2(nullptr), feedButton(nullptr), collectEggButton(nullptr) {
}

Coop::~Coop() {}

Coop* Coop::create() {
    Coop* ret = new Coop();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Coop::init() {
    // ���ü��ᱳ���������ͼƬ·����
    auto coopBackground = cocos2d::Sprite::create("photo/Adventure/coop.png");
    coopBackground->setPosition(cocos2d::Vec2(400, 300));  // ���ü��ᱳ��������
    this->addChild(coopBackground);  // ��������뵱ǰ��

    // ����������ӵ������ϲ㣬����λ������ڼ���
    chicken1 = Chicken::create("photo/Farm/chicken.png");
    chicken1->setPosition(cocos2d::Vec2(250, 170));  // �������λ��
    coopBackground->addChild(chicken1, 1);  // ������ӵ����ᱳ�����ϲ㣬���Ϊ1

    chicken2 = Chicken::create("photo/Farm/chicken.png");
    chicken2->setPosition(cocos2d::Vec2(250, 130));  // �������λ��
    coopBackground->addChild(chicken2, 1);

    //����ţ����
    cow1 = Cow::create("photo/Farm/cow.png");
    cow1->setPosition(cocos2d::Vec2(500, 300)); 
    coopBackground->addChild(cow1, 1);  

    cow2 = Cow::create("photo/Farm/cow.png");
    cow2->setPosition(cocos2d::Vec2(500, 100));
    coopBackground->addChild(cow2, 1);

    sheep1 = Sheep::create("photo/Farm/sheep.png");
    sheep1->setPosition(cocos2d::Vec2(700, 300));
    coopBackground->addChild(sheep1, 1);

    sheep2 = Sheep::create("photo/Farm/sheep.png");
    sheep2->setPosition(cocos2d::Vec2(700, 100));
    coopBackground->addChild(sheep2, 1);
    
    // ������ť���󶨻ص�����ťλ������ڼ��ᱳ����
    feedButton = cocos2d::MenuItemImage::create("photo/Farm/feed_button.png", "photo/Farm/feed_button.png", CC_CALLBACK_1(Coop::onFeedClicked, this));
    feedButton->setScale(2.0f);
    feedButton->setPosition(cocos2d::Vec2(400, 80));  // ���ð�ť�����λ��

    collectEggButton = cocos2d::MenuItemImage::create("photo/Farm/collect_egg_button.png", "photo/Farm/collect_egg_button.png", CC_CALLBACK_1(Coop::onCollectEggClicked, this));
    collectEggButton->setScale(2.0f);
    collectEggButton->setPosition(cocos2d::Vec2(500, 80));  // ���ð�ť�����λ��

    // �����˵�����Ӱ�ť
    auto menu = cocos2d::Menu::create(feedButton, collectEggButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void Coop::onFeedClicked(cocos2d::Ref* sender) {
    // ͬ��ι��
    chicken1->setState(Chicken::State::Full);  // ι��һֻ��
    chicken2->setState(Chicken::State::Full);  // ι�ڶ�ֻ��
    cow1->setState(Cow::State::Full);
    cow2->setState(Cow::State::Full);
    sheep1->setState(Sheep::State::Full);
    sheep2->setState(Sheep::State::Full);
}

void Coop::onCollectEggClicked(cocos2d::Ref* sender) {
    chicken1->collectProduct();
    chicken2->collectProduct();
    cow1->collectProduct();
    cow2->collectProduct();
    sheep1->collectProduct();
    sheep2->collectProduct();
}

