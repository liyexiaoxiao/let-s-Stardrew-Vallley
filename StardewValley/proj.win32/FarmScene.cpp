//ũ����ͼ��������
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"

extern Player* mainPlayer; // �����

// ����������ʼ��
FarmScene::FarmScene()
    : Farmmap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
    // �ͷ�������Դ
    for (auto tree : trees) {
        tree->release();
    }
}

FarmScene* FarmScene::create() {
    FarmScene* ret = new FarmScene();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool FarmScene::init() {

    // ���ص�ͼ
    Farmmap = cocos2d::TMXTiledMap::create("photo/Map/0farmsoilground2048x2048.tmx");
    Farmmap->setContentSize(cocos2d::Size(2048, 2048));//���ô�С
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Farmmap->setPosition(visibleSize.width / 2 - Farmmap->getContentSize().width / 2,
        visibleSize.height / 2 - Farmmap->getContentSize().height / 2);
    this->addChild(Farmmap);

    // ��ȡ��ͬ��ͼ��
    groundLayer = Farmmap->getLayer("layer1ground");  // �����
    wallLayer = Farmmap->getLayer("layer2wall");      // Χǽ��


    // �������
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // �������Ļ����
    mainPlayer->setScale(1.0f);
    this->addChild(mainPlayer);

    //����ũ������Ľ�����Ԫ��--��ʼ������
    // ���� Farmer NPC 
    farmer = new Farmer();
    //��ȡ�����������ڵ�ͼ��λ��
    const cocos2d::Vec2 farmerPos = Farmmap->convertToNodeSpace(cocos2d::Vec2(1180, 1180));  // ����Ļ����ת��Ϊ��ͼ����
    std::string debugInfo1 = "farmerPos : x=" + std::to_string(farmerPos.x) +
        ", y=" + std::to_string(farmerPos.y);

    // ��ʾ������Ϣ
    displayDebugInfo(debugInfo1);
    interactiveElements.push_back(farmer);
    this->addChild(farmer);  // �� Farmer ��ӵ�������

    //����ũ���������
    for (int i = 0; i < 10; ++i) {
        Tree* tree = Tree::create();
        // �������ĳ�ʼλ�ã�����Ը���ʵ����Ҫ����λ�ã�
        tree->setPosition(cocos2d::Vec2((128 + i * 128)+32, 600+32)); // �������ĳ�ʼλ��
        tree->setScale(1.5f);
        interactiveElements.push_back(tree);
        this->addChild(tree); // ������ӵ�������
        trees.push_back(tree); //  
    }

    // ��ʼ����������δ����
    int mapWidth = groundLayer->getLayerSize().width;
    int mapHeight = groundLayer->getLayerSize().height;
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));
    tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));


    // ���º���
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    Clock* clock = Clock::getInstance();
    clock->startClock();
    this->addChild(clock);

    // ��ʼ�� plantedCrops
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));

    // �����˵��㲢��ӵ�������
    menuLayer = MenuLayer::create();
    this->addChild(menuLayer);

    // ������������
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);


    //���������
    auto Mouselistener = cocos2d::EventListenerMouse::create();
    Mouselistener->onMouseDown = CC_CALLBACK_1(FarmScene::onMouseClicked, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);


    //������������
     //������ť���������ڳ����������ť�����Ǹ�����ͼ�꣬player����--���Ͻǣ���������ӽ������ڳ�����
    startButton = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");
    // ���ð�ťλ��
    startButton->setPosition(cocos2d::Vec2(1, 1020));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton->setScale(0.8f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť����¼������ӵ��ڶ������棺���ڣ�����
    startButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    return true;
}



