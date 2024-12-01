#include"StartupScene.h"
#include "AppDelegate.h"
#include "ui/CocosGUI.h"
#include "InitialScene.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;
using namespace cocos2d::ui;
// 创建场景
Scene* StartupScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartupScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool StartupScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }
    // 加载音乐
    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("photo/startup_p/stardewbackground.png");
    if (background == nullptr)
    {
        //problemLoading("'HelloWorld.png'");一个报错信息，我还没做
    }
    else
    {
        // position the sprite on the center of the screen
        background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
        background->setContentSize(screenSize);
        // add the sprite as a child to this layer 在库函数中设置了自动适应大小，所以窗口设置大一点图片就可以显示完全
        this->addChild(background, 0);//0表示图片级别
    }
    //创建按钮
    auto NewButton = Button::create("photo/startup_p/NewButton.png", "photo/startup_p/NewButtonPressed.png");
    auto ExitButton=Button::create("photo/startup_p/ExitButton.png", "photo/startup_p/ExitButtonPressed.png");
    // 设置按钮位置
    NewButton->setPosition(Vec2(screenSize.width / 2 - 150, screenSize.height / 4));
    ExitButton->setPosition(Vec2(screenSize.width / 2 + 150, screenSize.height / 4));
    // 设置按钮大小，确保按钮不会超出屏幕
    NewButton->setScale(1.3f);  // 可根据需要调整按钮大小
    ExitButton->setScale(1.3f);
    // 将按钮添加到场景
    this->addChild(NewButton);
    this->addChild(ExitButton);
    // 设置按钮点击事件
    NewButton->addClickEventListener([=](Ref* sender) {
        // 切换到游戏场景
        auto transition = cocos2d::TransitionFade::create(1.0f, InitialScene::createScene(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    ExitButton->addClickEventListener([](Ref* sender) {
        cocos2d::Director::getInstance()->end();
        });

    addImageToScene("photo/startup_p/logo.png", Vec2(screenSize.width / 2, screenSize.height / 2 + 150));
    return true;
}

void StartupScene::addImageToScene(const std::string& imageFile, const Vec2& position)
{
    // 创建精灵
    auto sprite = Sprite::create(imageFile);
    if (sprite != nullptr) {
        // 设置精灵的位置
        sprite->setPosition(position);
        // 将精灵添加到场景
        this->addChild(sprite);
    }
    else {
        CCLOG("Failed to load image: %s", imageFile.c_str());
    }
}