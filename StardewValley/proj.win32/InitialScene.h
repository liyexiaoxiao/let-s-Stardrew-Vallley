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
    // ��������
    static Scene* createScene();
    // ��ʼ������
    virtual bool init();
    // �꣬������̬�� create() ����
    CREATE_FUNC(InitialScene);
};

#endif // __INITIAL_SCENE_H__
#pragma once
