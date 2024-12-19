//农场地图功能完善
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "FarmhouseScene.h"
#include"ExploreScene.h"

extern Player* mainPlayer; // 主玩家


// 构造析构初始化
FarmScene::FarmScene()
    : Farmmap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
    /*释放树的资源
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

    // 加载地图
    Farmmap = cocos2d::TMXTiledMap::create("photo/Map/0farmsoilground2048x2048.tmx");
    // 设置缩放因子为 4.0f--此后每一次计算位置都要考量farmscale
    //Farmmap->setScale(farmscale);
    //Farmmap->setContentSize(cocos2d::Size(2048, 2048));//设置大小
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Farmmap->setPosition(visibleSize.width / 2 - Farmmap->getContentSize().width / 2,
        visibleSize.height / 2 - Farmmap->getContentSize().height / 2);
    this->addChild(Farmmap);

    // 获取不同的图层
    groundLayer = Farmmap->getLayer("layer1ground");  // 地面层
    wallLayer = Farmmap->getLayer("layer2wall");      // 围墙层


    // 创建玩家
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 4); // 玩家在屏幕中心
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
    // 从Tiled地图的Object Layer中读取对象信息并创建对象
    auto objectGroup = Farmmap->getObjectGroup("Olayer1Tree");
    if (objectGroup) {
        // 遍历所有的对象
        for (auto& object : objectGroup->getObjects()) {
            // object 是 Value 类型，可以转化为 ValueMap
            auto obj = object.asValueMap();

            // 根据 "type" 字段判断对象类型
            if (obj["type"].asString() == "tree") {
                Tree* tree = Tree::create();
                // 获取树在 TileMap 坐标系中的位置
                float tileX = obj["x"].asFloat();
                float tileY = obj["y"].asFloat();

                // 将 TileMap 坐标转换为屏幕坐标
                cocos2d::Vec2 mapPosition = cocos2d::Vec2(tileX, tileY);
                cocos2d::Vec2 worldPosition = Farmmap->convertToWorldSpace(mapPosition);

                // 设置树的位置为屏幕坐标
                tree->setPosition(worldPosition);
                this->addChild(tree);
                trees.push_back(tree);//加入管理树的容器
                // 将树添加到可交互对象列表中
                interactiveElements.push_back(tree);
            }
            // 可以添加更多类型的对象
        }
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
    wateredLand.resize(mapHeight, std::vector<WateredLand*>(mapWidth, nullptr));
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr)); 
    tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));

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
    // 设置按钮的 Z 值为第1层（较高的显示层级）
    startButton->setLocalZOrder(1);
    // 设置按钮大小，确保按钮不会超出屏幕
    startButton->setScale(0.8f);  // 可根据需要调整按钮大小
    // 设置按钮点击事件，连接到第二个画面：室内！！！
    startButton->addClickEventListener([=](Ref* sender) {
        // 切换到游戏场景
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmhouseScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    startButton2 = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");//先懒得改
    // 设置按钮位置
    startButton2->setPosition(cocos2d::Vec2(1180, 1000));
    // 设置按钮大小，确保按钮不会超出屏幕
    startButton2->setScale(0.8f);  // 可根据需要调整按钮大小
    // 设置按钮的 Z 值为第1层（较高的显示层级）
    startButton->setLocalZOrder(1);
    // 设置按钮点击事件，连接到第二个画面：冒险！！！
    startButton2->addClickEventListener([=](Ref* sender) {
        // 切换到 ExploreScene 场景
        //onExit();
     
        auto exploreScene = ExploreScene::create();  // 创建新场景
        auto transition = cocos2d::TransitionFade::create(1.0f, exploreScene, cocos2d::Color3B::WHITE);  // 创建切换过渡效果
        cocos2d::Director::getInstance()->replaceScene(transition);  // 执行场景替换
        });
    this->addChild(startButton2);

    return true;
 }

 ////资源清理--手动
 //void FarmScene::onExit() {
 //    if (mainPlayer) {
 //        this->removeChild(mainPlayer);
 //    }

 //    // 清理交互元素
 //    for (auto element : interactiveElements) {
 //        delete element;  // 手动删除交互元素
 //    }
 //    interactiveElements.clear();  // 清空容器

 //    // 移除事件监听器
 //    _eventDispatcher->removeEventListenersForTarget(this);

 //    // 清理其他资源，如工具、树等
 //    for (auto tree : trees) {
 //        delete tree;  // 手动删除树
 //    }
 //    trees.clear();  // 清空树列表

 //    // 如果有定时器或动作，需要取消它们
 //    this->unscheduleAllCallbacks();  // 取消所有定时器

 //    // 调用基类的 onExit 方法
 //    Scene::onExit();
 //    
 //}

