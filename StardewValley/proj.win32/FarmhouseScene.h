#ifndef __FARMHOUSE_SCENE_H__
#define __FARMHOUSE_SCENE_H__
#include "Clock.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuLayer.h"//�˵�����



class FarmhouseScene : public cocos2d::Scene
{
private:
    cocos2d::ui::TextField* PlayerNameTxt = nullptr;
    MenuLayer* menuLayer;
    bool isMenuActive = false;
public:
    
    FarmhouseScene();
    ~FarmhouseScene();
    // ��������
    static Scene* createScene();
    // ��ʼ������
    virtual bool init();
    // �꣬������̬�� create() ����
    CREATE_FUNC(FarmhouseScene);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //����
};

#endif // __FARMHOUSE_SCENE_H__
#pragma once

