#pragma once
//ʵ�ּ��ἰ����ع�������--������ذ�ť
#include "cocos2d.h"
//���ֶ���
#include "Chicken.h"
#include "Cow.h"
#include "Sheep.h"

class Coop : public cocos2d::Layer {
public:
    Coop();
    ~Coop();

    // ����ũ��
    static Coop* create();
    bool init();

    // ��ť�Ļص�����
    void onFeedClicked(cocos2d::Ref* sender);
    void onCollectEggClicked(cocos2d::Ref* sender);

private:
    Chicken* chicken1;  // ��һֻ��
    Chicken* chicken2;  // �ڶ�ֻ��
    Cow* cow1;
    Cow* cow2;
    Sheep* sheep1;
    Sheep* sheep2;
    cocos2d::MenuItemImage* feedButton;  // ι���ﰴť
    cocos2d::MenuItemImage* collectEggButton;  // ȡ��Ʒ��ť
};
