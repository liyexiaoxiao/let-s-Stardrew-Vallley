#include "InitialScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"FarmScene.h"
#include"SoilScene.h"
using namespace cocos2d;

InitialScene::InitialScene() {
    CCLOG("InitialScene constructed");
}

// ��������
InitialScene::~InitialScene() {
    CCLOG("InitialScene destructed");
}

// ��������
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();  
    auto layer = InitialScene::create();
    scene->addChild(layer);// ʹ�� CREATE_FUNC �����ɳ���
    return scene;
}

// ��ʼ������
bool InitialScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    // ��ȡ��Ļ�ߴ�
    const auto screenSize = Director::getInstance()->getVisibleSize();

    // ���ñ���
    auto background = Sprite::create("photo/startup_p/StartupScene.png");
    if (background == nullptr) {
        CCLOG("Background image loading failed for GameScene!");
    }
    else {
        background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
        background->setContentSize(screenSize);
        this->addChild(background, 0);
    }

    // ���ó������������Ԫ��
    auto titleLabel = Label::createWithSystemFont("Welcome to the Game!", "Arial", 36);
    titleLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height * 0.8f));
    this->addChild(titleLabel);

    //����ΪgyxΪ�˲��Ե�ͼ�Լ������д
     //������ť,ȷ����
    auto startButton = cocos2d::ui::Button::create("photo/startup_p/button1.png", "button_pressed.png", "button_disabled.png");
    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 4));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton->setScale(0.5f);  // �ɸ�����Ҫ������ť��С

    // ���ð�ť����¼������ӵ���һ�����棺ũ��������
    startButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);


    //����ΪzskΪ�˲����ֵ�(���ǳ�ʼ��һֱ��һ������������أ�
    //������ť,ȷ����(����Ǹ�)
    auto startButton2 = cocos2d::ui::Button::create("photo/startup_p/button1.png", "button_pressed.png", "button_disabled.png");
    // ���ð�ťλ��
    startButton2->setPosition(Vec2(screenSize.width /4, screenSize.height / 4));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton2->setScale(0.5f);  // �ɸ�����Ҫ������ť��С

    // ���ð�ť����¼������ӵ�ũ������
    startButton2->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
        Director::getInstance()->replaceScene(new SoilScene());
        });
    this->addChild(startButton2);

    return true;
}
