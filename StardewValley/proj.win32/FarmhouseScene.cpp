#include "FarmhouseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "Tools.h"
#include "Clock.h"
#include "MenuLayer.h" // 菜单界面
#include "ItemStorage.h"
#include "ItemIDs.h"

using namespace cocos2d;
extern Player* mainPlayer; // 主玩家


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




// 键盘按下事件
void FarmhouseScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
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


    // 创建一个贴图
    auto centerImage = Sprite::create("photo/Character/PlayerFront1.png");  // 使用你想要显示的图片路径
    if (centerImage == nullptr) {
        CCLOG("Center image loading failed!");
    }
    else {
        centerImage->setPosition(setGroundPosition);  // 将图片位置设置为屏幕中心
        centerImage->setScale(0.7f);
        this->addChild(centerImage, 2);  // 将图片添加到场景中，2表示层级关系，越大的值会在上面显示
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


    // 更新函数
    schedule([this](float deltaTime) {
        Clock::getInstance()->updateClock(deltaTime);
       
        }, "update_key");

    // 创建按钮: 门
    auto startButton = cocos2d::ui::Button::create("photo/InternalHouse/Door.png");
    startButton->setPosition(Vec2(screenSize.width / 4 + 130, screenSize.height / 4 - 60));
    startButton->setScale(2.0f); // 设置按钮大小
    startButton->addClickEventListener([=](Ref* sender) {
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    // 创建按钮: 床
    auto startButton1 = cocos2d::ui::Button::create("photo/InternalHouse/bed.png");
    startButton1->setPosition(Vec2(screenSize.width / 2 + 290, screenSize.height / 4 +270));
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

    
    ItemStorage& storage = ItemStorage::getInstance();

    // 创建按钮: 菜谱1 水煮蛋
    auto startButton2 = cocos2d::ui::Button::create("photo/InternalHouse/boiled_egg.png");
    startButton2->setPosition(Vec2(screenSize.width / 8 , 2*screenSize.height / 4+50 ));
    startButton2->setScale(3.0f); // 设置按钮大小

    /*startButton2->addClickEventListener([=](Ref* sender) {

        if (storage.getItemQuantity(StorageID::EGG) >= 1) {
            storage.removeItem(StorageID::EGG,1);
            storage.addItem(StorageID::BOILED_EGG, 1);
        }
        else {
            auto label = cocos2d::Label::createWithSystemFont("Ingredients Insufficient", "Arial", 40);
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // 屏幕中心
            label->setTextColor(cocos2d::Color4B::RED);  // 设置文字颜色为红色
            this->addChild(label);

            // 提示显示完毕后，2秒后移除提示
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }

        });*/
    this->addChild(startButton2);

    // 创建按钮: 菜谱2 树莓
    auto startButton3 = cocos2d::ui::Button::create("photo/InternalHouse/berries.png");
    startButton3->setPosition(Vec2(screenSize.width / 8, 2 * screenSize.height / 4 ));
    startButton3->setScale(3.0f); // 设置按钮大小
    if (mainPlayer->cookingLevel >= 2) {
        startButton3->setVisible(true);
    }
    else
        startButton3->setVisible(false);

    /*startButton3->addClickEventListener([=](Ref* sender) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::SHUMEI)) >= 1) {
            storage.removeItem(StorageID::SHUMEI, 1);
            storage.addItem(StorageID::BERRIES, 1);
        }
        else {
            auto label = cocos2d::Label::createWithSystemFont("Ingredients Insufficient", "Arial", 40);
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // 屏幕中心
            label->setTextColor(cocos2d::Color4B::RED);  // 设置文字颜色为红色
            this->addChild(label);

            // 提示显示完毕后，2秒后移除提示
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }

        });*/
    this->addChild(startButton3);

    // 创建按钮: 菜谱3 水煮鱼
    auto startButton4 = cocos2d::ui::Button::create("photo/InternalHouse/cooked_fish.png");
    startButton4->setPosition(Vec2(screenSize.width / 8, 2 * screenSize.height / 4-50));
    startButton4->setScale(3.0f); // 设置按钮大小
    if (mainPlayer->cookingLevel >= 3) {
        startButton4->setVisible(true);
    }
    else
        startButton4->setVisible(false);
    /*startButton4->addClickEventListener([=](Ref* sender) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::FISH_A)) >= 1) {
            storage.removeItem(StorageID::FISH_A, 1);
            storage.addItem(StorageID::COOKED_FISH, 1);
        }
        else {
            auto label = cocos2d::Label::createWithSystemFont("Ingredients Insufficient", "Arial", 40);
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // 屏幕中心
            label->setTextColor(cocos2d::Color4B::RED);  // 设置文字颜色为红色
            this->addChild(label);

            // 提示显示完毕后，2秒后移除提示
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }
        });*/
    this->addChild(startButton4);

    // 创建按钮: 菜谱4 啤酒
    auto startButton5 = cocos2d::ui::Button::create("photo/InternalHouse/beer.png");
    startButton5->setPosition(Vec2(screenSize.width / 8, 2 * screenSize.height / 4-100));
    startButton5->setScale(3.0f); // 设置按钮大小
    if (mainPlayer->cookingLevel >= 3) {
        startButton5->setVisible(true);
    }
    else
        startButton5->setVisible(false);
    /*startButton5->addClickEventListener([=](Ref* sender) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::XIAOMAI)) >= 2) {
            storage.removeItem(StorageID::XIAOMAI, 2);
            storage.addItem(StorageID::BEER, 1);
        }
        else {
            auto label = cocos2d::Label::createWithSystemFont("Ingredients Insufficient", "Arial", 40);
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // 屏幕中心
            label->setTextColor(cocos2d::Color4B::RED);  // 设置文字颜色为红色
            this->addChild(label);

            // 提示显示完毕后，2秒后移除提示
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }

        });*/
    this->addChild(startButton5);

    // 监听键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(FarmhouseScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}
