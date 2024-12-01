#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InitialScene : public cocos2d::Scene
{
private:
    cocos2d::ui::TextField* PlayerNameTxt = nullptr;
public:

    InitialScene();
    ~InitialScene();
    // 创建场景
    static Scene* createScene();
    // 初始化场景
    virtual bool init();
    // 宏，创建静态的 create() 函数
    CREATE_FUNC(InitialScene);
};

#endif // __INITIAL_SCENE_H__
#pragma once
