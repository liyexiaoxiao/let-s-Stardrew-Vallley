#include "InitialScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"FarmScene.h"
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
//�����ʼ������
void InitialScene::addImageToScene(const std::string& imageFile, const Vec2& position)
{
    // ��������
    auto sprite = Sprite::create(imageFile);
    if (sprite != nullptr) {
        // ���þ����λ��
        sprite->setPosition(position);
        // ��������ӵ�����
        this->addChild(sprite);
    }
    else {
        CCLOG("Failed to load image: %s", imageFile.c_str());
    }
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



    //����ȫΪgyxΪ�˲��Ե�ͼ�Լ������д
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

    return true;
}
