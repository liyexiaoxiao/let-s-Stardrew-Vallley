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
    // 设置鸡舍背景（鸡舍的图片路径）
    auto coopBackground = cocos2d::Sprite::create("photo/Adventure/coop.png");
    coopBackground->setPosition(cocos2d::Vec2(400, 300));  // 设置鸡舍背景的坐标
    this->addChild(coopBackground);  // 将鸡舍加入当前层

    // 创建鸡并添加到鸡舍上层，鸡的位置相对于鸡舍
    chicken1 = Chicken::create("photo/Farm/chicken.png");
    chicken1->setPosition(cocos2d::Vec2(250, 170));  // 鸡的相对位置
    coopBackground->addChild(chicken1, 1);  // 将鸡添加到鸡舍背景的上层，层次为1

    chicken2 = Chicken::create("photo/Farm/chicken.png");
    chicken2->setPosition(cocos2d::Vec2(250, 130));  // 鸡的相对位置
    coopBackground->addChild(chicken2, 1);

    //创建牛、羊
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
    
    // 创建按钮并绑定回调（按钮位置相对于鸡舍背景）
    feedButton = cocos2d::MenuItemImage::create("photo/Farm/feed_button.png", "photo/Farm/feed_button.png", CC_CALLBACK_1(Coop::onFeedClicked, this));
    feedButton->setScale(2.0f);
    feedButton->setPosition(cocos2d::Vec2(400, 80));  // 设置按钮的相对位置

    collectEggButton = cocos2d::MenuItemImage::create("photo/Farm/collect_egg_button.png", "photo/Farm/collect_egg_button.png", CC_CALLBACK_1(Coop::onCollectEggClicked, this));
    collectEggButton->setScale(2.0f);
    collectEggButton->setPosition(cocos2d::Vec2(500, 80));  // 设置按钮的相对位置

    // 创建菜单并添加按钮
    auto menu = cocos2d::Menu::create(feedButton, collectEggButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void Coop::onFeedClicked(cocos2d::Ref* sender) {
    // 同步喂鸡
    chicken1->setState(Chicken::State::Full);  // 喂第一只鸡
    chicken2->setState(Chicken::State::Full);  // 喂第二只鸡
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

