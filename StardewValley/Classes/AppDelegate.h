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
    @brief    执行导演和场景初始化代码
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.初始化失败则直接终止。
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief 当应用程序移动到后台时调用
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  当应用程序即将进入前台时调用
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_
