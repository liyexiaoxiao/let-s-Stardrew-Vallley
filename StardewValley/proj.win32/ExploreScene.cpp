#include"ExploreScene.h"
#include "FarmScene.h"//用于回到农场
#include "Clock.h"

extern Player* mainPlayer; // 主玩家

// 构造析构初始化
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

    // 加载地图
    Exploremap = cocos2d::TMXTiledMap::create("photo/Map/exploremap2560x2560.tmx");
    //Exploremap->setContentSize(cocos2d::Size(2048, 2048));//设置大小
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Exploremap->setPosition(visibleSize.width / 2 - Exploremap->getContentSize().width / 2,
        visibleSize.height / 2 - Exploremap->getContentSize().height / 2);
    this->addChild(Exploremap);

    // 获取不同的图层
    groundLayer = Exploremap->getLayer("layer1ground");  // 地面层
    wallLayer = Exploremap->getLayer("layer2wall");      // 围墙层


    // 创建玩家
    if (mainPlayer) {
        // 在探索场景中设置玩家的初始位置
        mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // 重新设置位置
    }

    //创建冒险地图里面的交互性元素--初始即存在
    // 更新函数
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    //初始化时间
    Clock* clock = Clock::getInstance();
    clock->startClock();
    this->addChild(clock);

    // 监听键盘输入
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(ExploreScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(ExploreScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);


    //监听鼠标点击
    auto Mouselistener = cocos2d::EventListenerMouse::create();
    Mouselistener->onMouseDown = CC_CALLBACK_1(ExploreScene::onMouseClicked, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);


    //回到其它场景
     //创建按钮，进入室内场景，这个按钮就是那个房子图标，player房子--左上角，即点击房子进入室内场景。
    returnButton = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");
    // 设置按钮位置
    returnButton->setPosition(cocos2d::Vec2(1, 1020));
    // 设置按钮大小，确保按钮不会超出屏幕
    returnButton->setScale(0.8f);  // 可根据需要调整按钮大小
    // 设置按钮点击事件，连接到第二个画面：农场111
    returnButton->addClickEventListener([=](Ref* sender) {
        // 在切换场景之前清理当前场景的所有子节点
        this->removeChild(returnButton, true);  // 移除当前按钮
        // 切换回 FarmScene 场景
        auto farmScene = FarmScene::create();  // 创建新的农场场景
        auto transition = cocos2d::TransitionFade::create(1.0f, farmScene, cocos2d::Color3B::WHITE);  // 创建切换过渡效果
        cocos2d::Director::getInstance()->replaceScene(transition);  // 执行场景替换
        });
    this->addChild(returnButton);

    return true;
}



