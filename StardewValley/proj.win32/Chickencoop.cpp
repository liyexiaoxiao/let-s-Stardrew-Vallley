#include "ChickenCoop.h"

ChickenCoop::ChickenCoop()
    : chicken1(nullptr), chicken2(nullptr), feedButton(nullptr), collectEggButton(nullptr) {
}

ChickenCoop::~ChickenCoop() {}

ChickenCoop* ChickenCoop::create() {
    ChickenCoop* ret = new ChickenCoop();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ChickenCoop::init() {
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

    // ������ť���󶨻ص�����ťλ������ڼ��ᱳ����
    feedButton = cocos2d::MenuItemImage::create("photo/Farm/feed_button.png", "photo/Farm/feed_button.png", CC_CALLBACK_1(ChickenCoop::onFeedClicked, this));
    feedButton->setScale(2.0f);
    feedButton->setPosition(cocos2d::Vec2(400, 80));  // ���ð�ť�����λ��

    collectEggButton = cocos2d::MenuItemImage::create("photo/Farm/collect_egg_button.png", "photo/Farm/collect_egg_button.png", CC_CALLBACK_1(ChickenCoop::onCollectEggClicked, this));
    collectEggButton->setScale(2.0f);
    collectEggButton->setPosition(cocos2d::Vec2(500, 80));  // ���ð�ť�����λ��

    // �����˵�����Ӱ�ť
    auto menu = cocos2d::Menu::create(feedButton, collectEggButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void ChickenCoop::onFeedClicked(cocos2d::Ref* sender) {
    // ͬ��ι��
    chicken1->setState(Chicken::State::Full);  // ι��һֻ��
    chicken2->setState(Chicken::State::Full);  // ι�ڶ�ֻ��
}

void ChickenCoop::onCollectEggClicked(cocos2d::Ref* sender) {
    // ͬ��ȡ��
    if (chicken1->hasEgg()) {
        chicken1->collectEgg();  // ȡ��һֻ���ĵ�
    }

    if (chicken2->hasEgg()) {
        chicken2->collectEgg();  // ȡ�ڶ�ֻ���ĵ�
    }

}

