#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    ִ�е��ݺͳ�����ʼ������
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.��ʼ��ʧ����ֱ����ֹ��
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief ��Ӧ�ó����ƶ�����̨ʱ����
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  ��Ӧ�ó��򼴽�����ǰ̨ʱ����
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_
