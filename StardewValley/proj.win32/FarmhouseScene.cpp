#include "FarmhouseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "Tools.h"
#include "Clock.h"
#include "MenuLayer.h" // �˵�����
#include "ItemStorage.h"
#include "ItemIDs.h"

using namespace cocos2d;
extern Player* mainPlayer; // �����


FarmhouseScene::FarmhouseScene() {
    CCLOG("FarmhouseScene constructed");
}

// ��������
FarmhouseScene::~FarmhouseScene() {
    CCLOG("FarmhouseScene destructed");
}

// ��������
Scene* FarmhouseScene::createScene()
{
    auto scene = Scene::create();
    auto layer = FarmhouseScene::create();
    scene->addChild(layer); // ʹ�� CREATE_FUNC �����ɳ���
    return scene;
}




// ���̰����¼�
void FarmhouseScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_E: // ��e�򿪻�رղ˵�
        if (menuLayer) {
            menuLayer->toggleVisibility();  // Toggle the menu visibility
        }
        isMenuActive = !isMenuActive;
        break;
    default:
        break;
    }
}






// ��ʼ������
bool FarmhouseScene::init()
{
    Tools Tool;
    if (!Scene::init()) {
        return false;
    }

    // ��ȡ��Ļ�ߴ�
    const auto screenSize = Director::getInstance()->getVisibleSize();
    auto setGroundPosition = Vec2(screenSize.width / 2, screenSize.height / 2);

    // ���ñ���
    auto background = Sprite::create("photo/InternalHouse/Farmhouse.png");
    if (background == nullptr) {
        CCLOG("Background image loading failed for GameScene!");
    }
    else {
        background->setPosition(setGroundPosition);
        background->setContentSize(screenSize);
        this->addChild(background, 0);
    }


    // ����һ����ͼ
    auto centerImage = Sprite::create("photo/Character/PlayerFront1.png");  // ʹ������Ҫ��ʾ��ͼƬ·��
    if (centerImage == nullptr) {
        CCLOG("Center image loading failed!");
    }
    else {
        centerImage->setPosition(setGroundPosition);  // ��ͼƬλ������Ϊ��Ļ����
        centerImage->setScale(0.7f);
        this->addChild(centerImage, 2);  // ��ͼƬ��ӵ������У�2��ʾ�㼶��ϵ��Խ���ֵ����������ʾ
    }

   // ����ʱ����ʾ
    Clock* clock = Clock::getInstance();
    if (clock->getParent() == nullptr) {
        this->addChild(clock);
    }
    if (clock == nullptr) {
        CCLOG("Clock instance is null");
        return false;
    }
    
    clock->setTimeDisplay();
    

    menuLayer = MenuLayer::create();  // �����˵�����
    if (menuLayer == nullptr) {
        CCLOG("MenuLayer creation failed");
        return false;
    }
    this->addChild(menuLayer, 1);


    // ���º���
    schedule([this](float deltaTime) {
        Clock::getInstance()->updateClock(deltaTime);
       
        }, "update_key");

    // ������ť: ��
    auto startButton = cocos2d::ui::Button::create("photo/InternalHouse/Door.png");
    startButton->setPosition(Vec2(screenSize.width / 4 + 130, screenSize.height / 4 - 60));
    startButton->setScale(2.0f); // ���ð�ť��С
    startButton->addClickEventListener([=](Ref* sender) {
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    // ������ť: ��
    auto startButton1 = cocos2d::ui::Button::create("photo/InternalHouse/bed.png");
    startButton1->setPosition(Vec2(screenSize.width / 2 + 290, screenSize.height / 4 +270));
    startButton1->setScale(1.5f); // ���ð�ť��С
    startButton1->addClickEventListener([=](Ref* sender) {
        // ����һ����ɫ����
        auto blackScreen = LayerColor::create(Color4B(0, 0, 0, 255)); // ��ɫ����
        blackScreen->setOpacity(0); // ��ʼ͸��
        this->addChild(blackScreen, 1000); // ��ӵ����ϲ�

        // ������ʾ��ɫ����
        auto fadeIn = FadeTo::create(1.0f, 255); // ���䵽��ȫ��ɫ
        blackScreen->runAction(fadeIn);

        // �ӳٺ��޸�ʱ�䲢�л�����
        auto delay = DelayTime::create(1.0f); // �ӳ�1������ʾ��ɫ����
        auto callFunc = CallFunc::create([=]() {
            // ����ʱ��Ϊ�ڶ�������6��
            Clock* clock = Clock::getInstance();
            clock->setTimeafterSleep(6, 0, 0);  // ����Ϊ����6��

            // ���ɻ�FarmScene
            auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
            Director::getInstance()->replaceScene(transition);

            // �Ƴ���ɫ����
            blackScreen->removeFromParent();
            });

        // ִ�ж���
        blackScreen->runAction(Sequence::create(fadeIn, delay, callFunc, nullptr));
        });
    this->addChild(startButton1);

    
    ItemStorage& storage = ItemStorage::getInstance();

    // ������ť: ����1 ˮ��
    auto startButton2 = cocos2d::ui::Button::create("photo/InternalHouse/boiled_egg.png");
    startButton2->setPosition(Vec2(screenSize.width / 8 , 2*screenSize.height / 4+50 ));
    startButton2->setScale(3.0f); // ���ð�ť��С

    /*startButton2->addClickEventListener([=](Ref* sender) {

        if (storage.getItemQuantity(StorageID::EGG) >= 1) {
            storage.removeItem(StorageID::EGG,1);
            storage.addItem(StorageID::BOILED_EGG, 1);
        }
        else {
            auto label = cocos2d::Label::createWithSystemFont("Ingredients Insufficient", "Arial", 40);
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // ��Ļ����
            label->setTextColor(cocos2d::Color4B::RED);  // ����������ɫΪ��ɫ
            this->addChild(label);

            // ��ʾ��ʾ��Ϻ�2����Ƴ���ʾ
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }

        });*/
    this->addChild(startButton2);

    // ������ť: ����2 ��ݮ
    auto startButton3 = cocos2d::ui::Button::create("photo/InternalHouse/berries.png");
    startButton3->setPosition(Vec2(screenSize.width / 8, 2 * screenSize.height / 4 ));
    startButton3->setScale(3.0f); // ���ð�ť��С
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
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // ��Ļ����
            label->setTextColor(cocos2d::Color4B::RED);  // ����������ɫΪ��ɫ
            this->addChild(label);

            // ��ʾ��ʾ��Ϻ�2����Ƴ���ʾ
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }

        });*/
    this->addChild(startButton3);

    // ������ť: ����3 ˮ����
    auto startButton4 = cocos2d::ui::Button::create("photo/InternalHouse/cooked_fish.png");
    startButton4->setPosition(Vec2(screenSize.width / 8, 2 * screenSize.height / 4-50));
    startButton4->setScale(3.0f); // ���ð�ť��С
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
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // ��Ļ����
            label->setTextColor(cocos2d::Color4B::RED);  // ����������ɫΪ��ɫ
            this->addChild(label);

            // ��ʾ��ʾ��Ϻ�2����Ƴ���ʾ
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }
        });*/
    this->addChild(startButton4);

    // ������ť: ����4 ơ��
    auto startButton5 = cocos2d::ui::Button::create("photo/InternalHouse/beer.png");
    startButton5->setPosition(Vec2(screenSize.width / 8, 2 * screenSize.height / 4-100));
    startButton5->setScale(3.0f); // ���ð�ť��С
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
            label->setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2));  // ��Ļ����
            label->setTextColor(cocos2d::Color4B::RED);  // ����������ɫΪ��ɫ
            this->addChild(label);

            // ��ʾ��ʾ��Ϻ�2����Ƴ���ʾ
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);
                }, 2.0f, "remove_no_tool");
        }

        });*/
    this->addChild(startButton5);

    // ���������¼�
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(FarmhouseScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}
