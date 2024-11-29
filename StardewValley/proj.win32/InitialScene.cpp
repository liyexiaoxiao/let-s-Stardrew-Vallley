#include "InitialScene.h"
#include "cocos2d.h"

using namespace cocos2d;

InitialScene::InitialScene() {
    CCLOG("InitialScene constructed");
}

// 析构函数
InitialScene::~InitialScene() {
    CCLOG("InitialScene destructed");
}

// 创建场景
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();  
    auto layer = InitialScene::create();
    scene->addChild(layer);// 使用 CREATE_FUNC 宏生成场景
    return scene;
}

// 初始化场景
bool InitialScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕尺寸
    const auto screenSize = Director::getInstance()->getVisibleSize();

    // 设置背景
    auto background = Sprite::create("photo/startup_p/StartupScene.png");
    if (background == nullptr) {
        CCLOG("Background image loading failed for GameScene!");
    }
    else {
        background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
        background->setContentSize(screenSize);
        this->addChild(background, 0);
    }

    // 设置场景标题或其他元素
    auto titleLabel = Label::createWithSystemFont("Welcome to the Game!", "Arial", 36);
    titleLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height * 0.8f));
    this->addChild(titleLabel);

 

    return true;
}
