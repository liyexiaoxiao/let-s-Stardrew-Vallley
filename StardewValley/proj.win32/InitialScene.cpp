#include "InitialScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"FarmScene.h"
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
//人物初始化界面
void InitialScene::addImageToScene(const std::string& imageFile, const Vec2& position)
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



    //以下全为gyx为了测试地图以及游玩而写
     //创建按钮,确定键
    auto startButton = cocos2d::ui::Button::create("photo/startup_p/button1.png", "button_pressed.png", "button_disabled.png");
    // 设置按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 4));
    // 设置按钮大小，确保按钮不会超出屏幕
    startButton->setScale(0.5f);  // 可根据需要调整按钮大小

    // 设置按钮点击事件，连接到第一个画面：农场！！！
    startButton->addClickEventListener([=](Ref* sender) {
        // 切换到游戏场景
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    return true;
}
