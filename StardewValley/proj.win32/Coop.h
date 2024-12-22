#pragma once
//实现鸡舍及其相关管理，包括--鸡和相关按钮
#include "cocos2d.h"
//三种动物
#include "Chicken.h"
#include "Cow.h"
#include "Sheep.h"

class Coop : public cocos2d::Layer {
public:
    Coop();
    ~Coop();

    // 创建农舍
    static Coop* create();
    bool init();

    // 按钮的回调函数
    void onFeedClicked(cocos2d::Ref* sender);
    void onCollectEggClicked(cocos2d::Ref* sender);

private:
    Chicken* chicken1;  // 第一只鸡
    Chicken* chicken2;  // 第二只鸡
    Cow* cow1;
    Cow* cow2;
    Sheep* sheep1;
    Sheep* sheep2;
    cocos2d::MenuItemImage* feedButton;  // 喂动物按钮
    cocos2d::MenuItemImage* collectEggButton;  // 取产品按钮
};
