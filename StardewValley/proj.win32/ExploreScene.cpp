#include"ExploreScene.h"
#include "FarmScene.h"//���ڻص�ũ��
#include "Clock.h"

extern Player* mainPlayer; // �����

// ����������ʼ��
ExploreScene::ExploreScene()
    : Exploremap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

ExploreScene::~ExploreScene() {}

ExploreScene* ExploreScene::create() {
    ExploreScene* ret = new ExploreScene();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ExploreScene::init() {

    // ���ص�ͼ
    Exploremap = cocos2d::TMXTiledMap::create("photo/Map/exploremap2560x2560.tmx");
    //Exploremap->setContentSize(cocos2d::Size(2048, 2048));//���ô�С
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Exploremap->setPosition(visibleSize.width / 2 - Exploremap->getContentSize().width / 2,
        visibleSize.height / 2 - Exploremap->getContentSize().height / 2);
    this->addChild(Exploremap);

    // ��ȡ��ͬ��ͼ��
    groundLayer = Exploremap->getLayer("layer1ground");  // �����
    wallLayer = Exploremap->getLayer("layer2wall");      // Χǽ��


    // �������
    if (mainPlayer) {
        // ��̽��������������ҵĳ�ʼλ��
        mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // ��������λ��
    }

    //����ð�յ�ͼ����Ľ�����Ԫ��--��ʼ������
    // ���º���
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    //��ʼ��ʱ��
    Clock* clock = Clock::getInstance();
    clock->startClock();
    this->addChild(clock);

    // ������������
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(ExploreScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(ExploreScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);


    //���������
    auto Mouselistener = cocos2d::EventListenerMouse::create();
    Mouselistener->onMouseDown = CC_CALLBACK_1(ExploreScene::onMouseClicked, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);


    //�ص���������
     //������ť���������ڳ����������ť�����Ǹ�����ͼ�꣬player����--���Ͻǣ���������ӽ������ڳ�����
    returnButton = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");
    // ���ð�ťλ��
    returnButton->setPosition(cocos2d::Vec2(1, 1020));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    returnButton->setScale(0.8f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť����¼������ӵ��ڶ������棺ũ��111
    returnButton->addClickEventListener([=](Ref* sender) {
        // ���л�����֮ǰ����ǰ�����������ӽڵ�
        this->removeChild(returnButton, true);  // �Ƴ���ǰ��ť
        // �л��� FarmScene ����
        auto farmScene = FarmScene::create();  // �����µ�ũ������
        auto transition = cocos2d::TransitionFade::create(1.0f, farmScene, cocos2d::Color3B::WHITE);  // �����л�����Ч��
        cocos2d::Director::getInstance()->replaceScene(transition);  // ִ�г����滻
        });
    this->addChild(returnButton);

    return true;
}



