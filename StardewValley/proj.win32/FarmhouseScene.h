#ifndef __FARMHOUSE_SCENE_H__
#define __FARMHOUSE_SCENE_H__
#include "Clock.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuLayer.h"//菜单界面



class FarmhouseScene : public cocos2d::Scene
{
private:
    cocos2d::ui::TextField* PlayerNameTxt = nullptr;
    MenuLayer* menuLayer;
    bool isMenuActive = false;
public:
    
    FarmhouseScene();
    ~FarmhouseScene();
    // 创建场景
    static Scene* createScene();
    void movePlayer(float deltaX, float deltaY);
    // 初始化场景
    virtual bool init();
    // 宏，创建静态的 create() 函数
    CREATE_FUNC(FarmhouseScene);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //长按
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void moveMap(float deltaX, float deltaY);
};

#endif // __FARMHOUSE_SCENE_H__
#pragma once

