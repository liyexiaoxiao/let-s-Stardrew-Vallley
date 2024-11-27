#include"StartupScene.h"
#include "AppDelegate.h"
#include "ui/CocosGUI.h"

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
    const auto background = Sprite::create("photo/startup_p/1.png");
    if (background == nullptr)
    {
        //problemLoading("'HelloWorld.png'");һ��������Ϣ���һ�û��
    }
    else
    {
        // position the sprite on the center of the screen
        background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));

        // add the sprite as a child to this layer �ڿ⺯�����������Զ���Ӧ��С�����Դ������ô�һ��ͼƬ�Ϳ�����ʾ��ȫ
        this->addChild(background, 0);//0��ʾͼƬ����
    }
    //������ť
    auto startButton = Button::create("photo/startup_p/button1.png", "button_pressed.png", "button_disabled.png");
    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 4));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton->setScale(0.5f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť����¼�
    startButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
       // Director::getInstance()->replaceScene(GameScene::createScene());
        });

    // ����ť��ӵ�����
    this->addChild(startButton);
    return true;
}