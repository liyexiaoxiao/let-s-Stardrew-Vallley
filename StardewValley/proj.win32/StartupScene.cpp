#include"StartupScene.h"
#include "AppDelegate.h"
#include "ui/CocosGUI.h"
#include "InitialScene.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;
using namespace cocos2d::ui;
// ��������
Scene* StartupScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartupScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool StartupScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }
    // ��������
    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("photo/startup_p/stardewbackground.png");
    if (background == nullptr)
    {
        //problemLoading("'HelloWorld.png'");һ��������Ϣ���һ�û��
    }
    else
    {
        // position the sprite on the center of the screen
        background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
        background->setContentSize(screenSize);
        // add the sprite as a child to this layer �ڿ⺯�����������Զ���Ӧ��С�����Դ������ô�һ��ͼƬ�Ϳ�����ʾ��ȫ
        this->addChild(background, 0);//0��ʾͼƬ����
    }
    //������ť
    auto NewButton = Button::create("photo/startup_p/NewButton.png", "photo/startup_p/NewButtonPressed.png");
    auto ExitButton=Button::create("photo/startup_p/ExitButton.png", "photo/startup_p/ExitButtonPressed.png");
    // ���ð�ťλ��
    NewButton->setPosition(Vec2(screenSize.width / 2 - 150, screenSize.height / 4));
    ExitButton->setPosition(Vec2(screenSize.width / 2 + 150, screenSize.height / 4));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    NewButton->setScale(1.3f);  // �ɸ�����Ҫ������ť��С
    ExitButton->setScale(1.3f);
    // ����ť��ӵ�����
    this->addChild(NewButton);
    this->addChild(ExitButton);
    // ���ð�ť����¼�
    NewButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
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