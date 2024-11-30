#include "InitialScene.h"
#include "cocos2d.h"

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



 

    return true;
}
