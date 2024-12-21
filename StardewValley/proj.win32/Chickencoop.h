#pragma once
//ʵ�ּ��ἰ����ع�������--������ذ�ť
#include "cocos2d.h"
#include "Chicken.h"

class ChickenCoop : public cocos2d::Layer {
public:
    ChickenCoop();
    ~ChickenCoop();

    // ��������
    static ChickenCoop* create();
    bool init();

    // ��ť�Ļص�����
    void onFeedClicked(cocos2d::Ref* sender);
    void onCollectEggClicked(cocos2d::Ref* sender);

private:
    Chicken* chicken1;  // ��һֻ��
    Chicken* chicken2;  // �ڶ�ֻ��
    cocos2d::MenuItemImage* feedButton;  // ι����ť
    cocos2d::MenuItemImage* collectEggButton;  // ȡ����ť
};
