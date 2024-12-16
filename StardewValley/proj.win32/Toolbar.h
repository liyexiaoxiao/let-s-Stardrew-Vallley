#include "cocos2d.h"

class Toolbar : public cocos2d::Layer {
public:
    Toolbar() : currentToolIndex(0) {}
    ~Toolbar() {}

    static Toolbar* create();
    bool init();

    void createToolButton(const std::string& label, float x, float y, int index);

    // 点击工具按钮时，切换当前工具
    void onToolButtonClicked(int index);

    // 更新当前选择的工具
    void updateCurrentTool();

    // 鼠标滚轮事件，切换工具
    void onMouseScroll(cocos2d::Event* event);

private:
    int currentToolIndex;  // 当前持有的工具索引
};
#pragma once
