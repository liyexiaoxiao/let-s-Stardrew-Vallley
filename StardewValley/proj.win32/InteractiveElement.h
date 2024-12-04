#pragma once
#include "cocos2d.h"
//有关交互元素的操作 由于方向键的执行较为简单则不放在该文件下
//目前存在：鼠标点击交互--实现不同事物的不同功能
class InteractiveElement {
public:
    virtual ~InteractiveElement() {}

    // 纯虚函数，所有交互元素都必须实现此函数
    virtual void onClick() = 0;
    // 返回包围盒，派生类可以重写此方法来自动获取包围盒
    virtual cocos2d::Rect getBoundingBox() const = 0;
};
