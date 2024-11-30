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



 

    return true;
}
