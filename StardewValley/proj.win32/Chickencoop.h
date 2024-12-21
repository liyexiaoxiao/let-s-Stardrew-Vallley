#pragma once
//实现鸡舍及其相关管理，包括--鸡和相关按钮
#include "cocos2d.h"
#include "Chicken.h"

class ChickenCoop : public cocos2d::Layer {
public:
    ChickenCoop();
    ~ChickenCoop();

    // 创建鸡舍
    static ChickenCoop* create();
    bool init();

    // 按钮的回调函数
    void onFeedClicked(cocos2d::Ref* sender);
    void onCollectEggClicked(cocos2d::Ref* sender);

private:
    Chicken* chicken1;  // 第一只鸡
    Chicken* chicken2;  // 第二只鸡
    cocos2d::MenuItemImage* feedButton;  // 喂鸡按钮
    cocos2d::MenuItemImage* collectEggButton;  // 取蛋按钮
};
