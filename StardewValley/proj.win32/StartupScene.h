#pragma once
#pragma once
#ifndef _STARTUP_SCENE_H_
#define _STARTUP_SCENE_H_


#include "cocos2d.h"

class StartupScene : public cocos2d::Scene {
public:
    // ��������
    static cocos2d::Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ʵ�� StartupScene ��� create ����
    CREATE_FUNC(StartupScene);
};
#endif
