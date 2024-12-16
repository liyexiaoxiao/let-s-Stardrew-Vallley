#include "FarmhouseScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "Tools.h"
#include "player.h"
#include "Clock.h"
#include "MenuLayer.h" // �˵�����

using namespace cocos2d;
extern Player* mainPlayer;

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

// ��¼��ҵ��ƶ�״̬
bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;

// ���̰����¼�
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

// ���ð���״̬Ϊ�٣���ʾ�������ɿ�
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
    // ��ȡ��Ļ��С�����ﵱǰλ��
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto playerPos = mainPlayer->getPosition();

    // �����µ����λ��
    Vec2 newPos = playerPos + Vec2(deltaX, deltaY);

    // ������������Ļ�߽���
    newPos.x = std::clamp(newPos.x, 0.f, screenSize.width); // ����X����
    newPos.y = std::clamp(newPos.y, 0.f, screenSize.height); // ����Y����

    // ��������λ��
    mainPlayer->setPosition(newPos);
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

    // ������ҽ�ɫ
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    if (mainPlayer == nullptr) {
        CCLOG("Failed to create player!");
        return false;
    }
    mainPlayer->setPosition(screenSize.width / 2, screenSize.height / 2); // �������Ļ����
    mainPlayer->setScale(1.0f);
    this->addChild(mainPlayer); // �������ӵ�������

    // ���º�����������״̬���ƶ����
    schedule([this](float deltaTime) {
        Clock::getInstance()->updateClock(deltaTime);
        // ��鰴��״̬����������λ��
        if (movingUp) {
            movePlayer(0, 10.0f); // �����ƶ�
        }
        if (movingDown) {
            movePlayer(0, -10.0f); // �����ƶ�
        }
        if (movingLeft) {
            movePlayer(-10.0f, 0); // �����ƶ�
        }
        if (movingRight) {
            movePlayer(10.0f, 0); // �����ƶ�
        }
        }, "update_key");

    // ������ť: ��
    auto startButton = cocos2d::ui::Button::create("photo/InternalHouse/Door.png");
    startButton->setPosition(Vec2(screenSize.width / 4 + 180, screenSize.height / 4 - 60));
    startButton->setScale(2.0f); // ���ð�ť��С
    startButton->addClickEventListener([=](Ref* sender) {
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    // ������ť: ��
    auto startButton1 = cocos2d::ui::Button::create("photo/InternalHouse/bed.png");
    startButton1->setPosition(Vec2(screenSize.width / 2 + 227, screenSize.height / 4 +70));
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

    // ���������¼�
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(FarmhouseScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(FarmhouseScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}
