#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__

#include "cocos2d.h"

class InitialScene : public cocos2d::Scene
{
public:
    InitialScene();
    ~InitialScene();

    // 创建场景
    static Scene* createScene();
    // 添加图片到场景
    void addImageToScene(const std::string& imageFile, const cocos2d::Vec2& position);
    // 初始化场景
    virtual bool init();

    // 其他场景相关的函数，可以根据需求来添加

    // 宏，创建静态的 create() 函数
    CREATE_FUNC(InitialScene);
};

#endif // __INITIAL_SCENE_H__
#pragma once
