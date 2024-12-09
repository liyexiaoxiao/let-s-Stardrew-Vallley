//目前为gyx11/30测试使用
#pragma once

#include "InteractiveElement.h" //交互式相关
#include "cocos2d.h"

class Tree : public cocos2d::Sprite,public InteractiveElement {
public:
    Tree();
    ~Tree();
    //初始化
    static Tree* create();
    bool init();

    //相关功能
    void removeTree(); // 移除杂草
    bool isRemoved() const { return removed; }

    // 实现 InteractiveElement 的 onClick 方法
    void onClick() override {
        removeTree();
    }
    //利用包围盒进行多态判断
    cocos2d::Rect getBoundingBox() const override;

private:
    bool removed; // 标记杂草是否已被移除
};

