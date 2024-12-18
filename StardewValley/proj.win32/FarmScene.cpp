//ũ����ͼ��������
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "FarmhouseScene.h"
#include"ExploreScene.h"

extern Player* mainPlayer; // �����


// ����������ʼ��
FarmScene::FarmScene()
    : Farmmap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
    /*�ͷ�������Դ
    for (auto tree : trees) {
        tree->release();
    }
    for (auto resident : interactiveElements) {
        delete resident;
    }*/
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
    // ������������Ϊ 4.0f--�˺�ÿһ�μ���λ�ö�Ҫ����farmscale
    //Farmmap->setScale(farmscale);
    //Farmmap->setContentSize(cocos2d::Size(2048, 2048));//���ô�С
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
    //1.ũ��
    farmer = new Resident();
    farmer->init("Alex", "Farmer", "photo/Character/Resident1.png", cocos2d::Vec2(1000, 1000));
    interactiveElements.push_back(farmer);//�ɵ������
    this->addChild(farmer);  // �� Farmer ��ӵ�������
    //2.���
    fisherman = new Resident();
    fisherman->init("Willy", "Fisherman", "photo/Character/Resident2.png", cocos2d::Vec2(1000, -50));
    interactiveElements.push_back(fisherman);//�ɵ������
    this->addChild(fisherman);  // ��  fisherman ��ӵ�������
    //3.������
    breeder = new Resident();
    breeder->init("Marnie", "Breeder", "photo/Character/Resident3.png", cocos2d::Vec2(0, -100));
    interactiveElements.push_back(breeder);//�ɵ������
    this->addChild(breeder);  // ��  fisherman ��ӵ�������

    //����ũ���������
    for (int i = 0; i < 10; ++i) {
        Tree* tree = Tree::create();
        // �������ĳ�ʼλ�ã�����Ը���ʵ����Ҫ����λ�ã�
        tree->setPosition(cocos2d::Vec2((128 + i * 128) + 32, 600 + 32)); // �������ĳ�ʼλ��
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

    //��ʼ��ʱ��
    Clock* clock = Clock::getInstance();
    clock->startClock();
    this->addChild(clock);

    // ��ʼ�� plantedCrops
    wateredLand.resize(mapHeight, std::vector<WateredLand*>(mapWidth, nullptr));
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr)); 
    tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));

    // �����˵��㲢��ӵ�������
    menuLayer = MenuLayer::create();
    this->addChild(menuLayer);
    //������
    Toolbar *toolbar=Toolbar::create();
    if (toolbar) {
        this->addChild(toolbar, 5);  
    }

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
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmhouseScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    startButton2 = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");//�����ø�
    // ���ð�ťλ��
    startButton2->setPosition(cocos2d::Vec2(1180, 1000));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton2->setScale(0.8f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť����¼������ӵ��ڶ������棺ð�գ�����
    startButton2->addClickEventListener([=](Ref* sender) {
        // �л��� ExploreScene ����
        auto exploreScene = ExploreScene::create();  // �����³���
        auto transition = cocos2d::TransitionFade::create(1.0f, exploreScene, cocos2d::Color3B::WHITE);  // �����л�����Ч��
        cocos2d::Director::getInstance()->replaceScene(transition);  // ִ�г����滻
        });
    this->addChild(startButton2);

    return true;
 }



