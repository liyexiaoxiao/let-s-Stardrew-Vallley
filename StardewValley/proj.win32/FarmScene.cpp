//农场地图功能完善
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"

extern Player* mainPlayer; // 主玩家

// 构造析构初始化
FarmScene::FarmScene()
    : Farmmap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
    // 释放树的资源
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

    // 加载地图
    Farmmap = cocos2d::TMXTiledMap::create("photo/Map/0farmsoilground2048x2048.tmx");
    Farmmap->setContentSize(cocos2d::Size(2048, 2048));//设置大小
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Farmmap->setPosition(visibleSize.width / 2 - Farmmap->getContentSize().width / 2,
        visibleSize.height / 2 - Farmmap->getContentSize().height / 2);
    this->addChild(Farmmap);

    // 获取不同的图层
    groundLayer = Farmmap->getLayer("layer1ground");  // 地面层
    wallLayer = Farmmap->getLayer("layer2wall");      // 围墙层


    // 创建玩家
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // 玩家在屏幕中心
    mainPlayer->setScale(1.0f);
    this->addChild(mainPlayer);

    //创建农场里面的交互性元素--初始即存在
    // 创建 Farmer NPC 
    //1.农民
    farmer = new Resident();
    farmer->init("Alex", "Farmer", "photo/Character/Resident1.png", cocos2d::Vec2(1000, 1000));
    interactiveElements.push_back(farmer);//可点击交互
    this->addChild(farmer);  // 将 Farmer 添加到场景中
    //2.渔夫
    fisherman = new Resident();
    fisherman->init("Willy", "Fisherman", "photo/Character/Resident2.png", cocos2d::Vec2(1000, -50));
    interactiveElements.push_back(fisherman);//可点击交互
    this->addChild(fisherman);  // 将  fisherman 添加到场景中
    //3.饲养着
    breeder = new Resident();
    breeder->init("Marnie", "Breeder", "photo/Character/Resident3.png", cocos2d::Vec2(0, -100));
    interactiveElements.push_back(breeder);//可点击交互
    this->addChild(breeder);  // 将  fisherman 添加到场景中

    //创建农场里面的树
    for (int i = 0; i < 10; ++i) {
        Tree* tree = Tree::create();
        // 设置树的初始位置（你可以根据实际需要调整位置）
        tree->setPosition(cocos2d::Vec2((128 + i * 128) + 32, 600 + 32)); // 假设树的初始位置
        tree->setScale(1.5f);
        interactiveElements.push_back(tree);
        this->addChild(tree); // 将树添加到场景中
        trees.push_back(tree); //  
    }

    // 初始化所有土地未开垦
    int mapWidth = groundLayer->getLayerSize().width;
    int mapHeight = groundLayer->getLayerSize().height;
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));
    tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));


    // 更新函数
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    //初始化时间
    Clock* clock = Clock::getInstance();
    clock->startClock();
    this->addChild(clock);

    // 初始化 plantedCrops
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));

    // 创建菜单层并添加到场景中
    menuLayer = MenuLayer::create();
    this->addChild(menuLayer);

    // 监听键盘输入
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);


    //监听鼠标点击
    auto Mouselistener = cocos2d::EventListenerMouse::create();
    Mouselistener->onMouseDown = CC_CALLBACK_1(FarmScene::onMouseClicked, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);


    //进入其它场景
     //创建按钮，进入室内场景，这个按钮就是那个房子图标，player房子--左上角，即点击房子进入室内场景。
    startButton = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");
    // 设置按钮位置
    startButton->setPosition(cocos2d::Vec2(1, 1020));
    // 设置按钮大小，确保按钮不会超出屏幕
    startButton->setScale(0.8f);  // 可根据需要调整按钮大小
    // 设置按钮点击事件，连接到第二个画面：室内！！！
    startButton->addClickEventListener([=](Ref* sender) {
        // 切换到游戏场景
        /*auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);*/
        });
        this->addChild(startButton);

        return true;
        }



