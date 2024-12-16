#include "FarmhouseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "Tools.h"
#include "player.h"
#include "Clock.h"
#include "MenuLayer.h" // 菜单界面

using namespace cocos2d;
extern Player* mainPlayer;

FarmhouseScene::FarmhouseScene() {
    CCLOG("FarmhouseScene constructed");
}

// 析构函数
FarmhouseScene::~FarmhouseScene() {
    CCLOG("FarmhouseScene destructed");
}

// 创建场景
Scene* FarmhouseScene::createScene()
{
    auto scene = Scene::create();
    auto layer = FarmhouseScene::create();
    scene->addChild(layer); // 使用 CREATE_FUNC 宏生成场景
    return scene;
}

// 记录玩家的移动状态
bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;

// 键盘按下事件
void FarmhouseScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        movingUp = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        movingDown = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        movingLeft = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        movingRight = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_E: // 按e打开或关闭菜单
        if (menuLayer) {
            menuLayer->toggleVisibility();  // Toggle the menu visibility
        }
        isMenuActive = !isMenuActive;
        break;
    default:
        break;
    }
}

// 设置按键状态为假，表示按键已松开
void FarmhouseScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        movingUp = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        movingDown = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        movingLeft = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        movingRight = false;
        break;
    default:
        break;
    }
}


void FarmhouseScene::movePlayer(float deltaX, float deltaY) {
    // 获取屏幕大小和人物当前位置
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto playerPos = mainPlayer->getPosition();

    // 计算新的玩家位置
    Vec2 newPos = playerPos + Vec2(deltaX, deltaY);

    // 限制人物在屏幕边界内
    newPos.x = std::clamp(newPos.x, 0.f, screenSize.width); // 限制X坐标
    newPos.y = std::clamp(newPos.y, 0.f, screenSize.height); // 限制Y坐标

    // 更新人物位置
    mainPlayer->setPosition(newPos);
}

// 初始化场景
bool FarmhouseScene::init()
{
    Tools Tool;
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕尺寸
    const auto screenSize = Director::getInstance()->getVisibleSize();
    auto setGroundPosition = Vec2(screenSize.width / 2, screenSize.height / 2);

    // 设置背景
    auto background = Sprite::create("photo/InternalHouse/Farmhouse.png");
    if (background == nullptr) {
        CCLOG("Background image loading failed for GameScene!");
    }
    else {
        background->setPosition(setGroundPosition);
        background->setContentSize(screenSize);
        this->addChild(background, 0);
    }

   // 设置时钟显示
    Clock* clock = Clock::getInstance();
    if (clock->getParent() == nullptr) {
        this->addChild(clock);
    }
    if (clock == nullptr) {
        CCLOG("Clock instance is null");
        return false;
    }
    
    clock->setTimeDisplay();
    

    menuLayer = MenuLayer::create();  // 创建菜单对象
    if (menuLayer == nullptr) {
        CCLOG("MenuLayer creation failed");
        return false;
    }
    this->addChild(menuLayer, 1);

    // 创建玩家角色
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    if (mainPlayer == nullptr) {
        CCLOG("Failed to create player!");
        return false;
    }
    mainPlayer->setPosition(screenSize.width / 2, screenSize.height / 2); // 玩家在屏幕中心
    mainPlayer->setScale(1.0f);
    this->addChild(mainPlayer); // 将玩家添加到场景中

    // 更新函数：处理按键状态，移动玩家
    schedule([this](float deltaTime) {
        Clock::getInstance()->updateClock(deltaTime);
        // 检查按键状态，更新人物位置
        if (movingUp) {
            movePlayer(0, 10.0f); // 向上移动
        }
        if (movingDown) {
            movePlayer(0, -10.0f); // 向下移动
        }
        if (movingLeft) {
            movePlayer(-10.0f, 0); // 向左移动
        }
        if (movingRight) {
            movePlayer(10.0f, 0); // 向右移动
        }
        }, "update_key");

    // 创建按钮: 门
    auto startButton = cocos2d::ui::Button::create("photo/InternalHouse/Door.png");
    startButton->setPosition(Vec2(screenSize.width / 4 + 180, screenSize.height / 4 - 60));
    startButton->setScale(2.0f); // 设置按钮大小
    startButton->addClickEventListener([=](Ref* sender) {
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    // 创建按钮: 床
    auto startButton1 = cocos2d::ui::Button::create("photo/InternalHouse/bed.png");
    startButton1->setPosition(Vec2(screenSize.width / 2 + 227, screenSize.height / 4 +70));
    startButton1->setScale(1.5f); // 设置按钮大小
    startButton1->addClickEventListener([=](Ref* sender) {
        // 创建一个黑色遮罩
        auto blackScreen = LayerColor::create(Color4B(0, 0, 0, 255)); // 黑色背景
        blackScreen->setOpacity(0); // 初始透明
        this->addChild(blackScreen, 1000); // 添加到最上层

        // 渐变显示黑色背景
        auto fadeIn = FadeTo::create(1.0f, 255); // 渐变到完全黑色
        blackScreen->runAction(fadeIn);

        // 延迟后修改时间并切换场景
        auto delay = DelayTime::create(1.0f); // 延迟1秒来显示黑色背景
        auto callFunc = CallFunc::create([=]() {
            // 设置时间为第二天早上6点
            Clock* clock = Clock::getInstance();
            clock->setTimeafterSleep(6, 0, 0);  // 设置为早上6点

            // 过渡回FarmScene
            auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
            Director::getInstance()->replaceScene(transition);

            // 移除黑色背景
            blackScreen->removeFromParent();
            });

        // 执行动作
        blackScreen->runAction(Sequence::create(fadeIn, delay, callFunc, nullptr));
        });
    this->addChild(startButton1);

    // 监听键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(FarmhouseScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(FarmhouseScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}
