#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "player.h"
class MenuLayer : public cocos2d::Layer {
public:
    MenuLayer();
    ~MenuLayer();

    // 创建菜单界面
    bool init();
    static MenuLayer* create();

    cocos2d::Layer* MenuLayer::createPanel(int panelIndex);
    // 切换菜单显示状态
    void toggleVisibility();
    void createPanels(); //创建四个面板
    void showPanel(int index);
private:
    bool isVisible;  // 控制菜单显示状态
    cocos2d::Sprite* MenuBG;
    cocos2d::Layer* panel1;  // 面板1：农场信息
    cocos2d::Layer* panel2;  // 面板2：仓库存储
    cocos2d::Layer* panel3;  // 面板3：人物技能
    cocos2d::Layer* panel4;  // 面板4：退出游戏
};

#endif  // __MENU_LAYER_H__

