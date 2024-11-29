#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__

#include "cocos2d.h"

class InitialScene : public cocos2d::Scene
{
public:
    InitialScene();
    ~InitialScene();

    // ��������
    static Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ����������صĺ��������Ը������������

    // �꣬������̬�� create() ����
    CREATE_FUNC(InitialScene);
};

#endif // __INITIAL_SCENE_H__
#pragma once
