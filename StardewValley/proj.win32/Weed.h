//目前为gyx11/30测试使用
#pragma once
#ifndef __WEED_H__
#define __WEED_H__

#include "cocos2d.h"

class Weed : public cocos2d::Sprite {
public:
    Weed();
    ~Weed();

    static Weed* create();
    bool init();

    void removeWeed(); // 移除杂草

    bool isRemoved() const { return removed; }

private:
    bool removed; // 标记杂草是否已被移除
};

#endif // __WEED_H__
