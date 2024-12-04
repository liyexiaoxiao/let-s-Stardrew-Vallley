#pragma once
//第一个NPC：位于农场地图，是一个农民
#include "Resident.h"
#include "InteractiveElement.h" //交互式相关

class Farmer : public Resident,public InteractiveElement{
private:
    //交互相关
    cocos2d::Sprite* sprite;  // 显示农民图像的精灵
    cocos2d::Rect boundingBox;  // 当前农民的包围盒，通过农民在地图上的位置直接写死
    // 面板相关的成员变量
    cocos2d::Label* nameLabel;
    cocos2d::Label* professionLabel;
    cocos2d::Label* romanceLabel;
    cocos2d::Label* friendshipLabel;
    cocos2d::Label* taskLabel;
public:
    Farmer();  // 默认构造函数
    ~Farmer();

    // 显示 NPC 面板
    void showInfoPanel();  // 显示信息面板
    // 实现 InteractiveElement 的 onClick 方法
    void onClick() override {
        showInfoPanel();
    }
    //利用包围盒进行多态判断
    cocos2d::Rect getBoundingBox() const override;
 
    // 农民特有的任务行为
    void offerTask();  // 农民的任务
};