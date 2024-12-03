//农场地图功能完善
#include "FarmScene.h"
#include "cocos2d.h"
#include "Clock.h"
#include "Player.h"

// 构造析构初始化
FarmScene::FarmScene()
    : Farmmap(nullptr), mainPlayer(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {}

FarmScene::~FarmScene() {}

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
    mainPlayer->setScale(2.0f);
    this->addChild(mainPlayer);

    // 更新函数
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // 创建并启动时钟
    Clock* clock = Clock::create();
    clock->setLocalZOrder(1000);
    this->addChild(clock); // 将时钟添加到场景
    clock->startClock(); // 启动时钟

    // 监听键盘输入
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

    return true;
}

void FarmScene::moveMap(float deltaX, float deltaY) {
    // 获取玩家当前的位置
    cocos2d::Vec2 playerPos = mainPlayer->getPosition();
    // 计算背景移动后的玩家新位置
    cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY); 
    //更新地图移动
    cocos2d::Vec2 newPos = Farmmap ->getPosition() + cocos2d::Vec2(deltaX, deltaY);
    // 判断玩家是否碰到围墙
    if (!isColliding(newPlayerPos)) {
        // 如果没有碰到围墙，更新玩家位置
        Farmmap->setPosition(newPos);
    }
}

// 地图显示相关
void FarmScene::update(float deltaTime) {
    // 每帧更新，检查是否有按键被长按，持续移动地图
    if (movingUp) {
        moveMap(0, -10.0f); // 向上持续移动
    }
    if (movingDown) {
        moveMap(0, +10.0f); // 向下持续移动
    }
    if (movingLeft) {
        moveMap(+10.0f, 0); // 向左持续移动
    }
    if (movingRight) {
        moveMap(-10.0f, 0); // 向右持续移动
    }
}

void FarmScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // 设置按键状态为真，表示按键被按下
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        movingUp = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        movingDown = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        movingLeft = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        movingRight = true;
        break;
    default:
        break;
    }
}
void FarmScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // 设置按键状态为假，表示按键已松开
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        movingUp = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        movingDown = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        movingLeft = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        movingRight = false;
        break;
    default:
        break;
    }
}

bool FarmScene::isColliding(const cocos2d::Vec2& newPos) {
    // 获取玩家的边界框（Bounding Box）
    cocos2d::Rect playerBoundingBox = mainPlayer->getBoundingBox();

    // 获取瓦片的大小
    cocos2d::Size tileSize = Farmmap->getTileSize();
    float tileWidth = tileSize.width;
    float tileHeight = tileSize.height;

    // 计算新位置
    cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(newPos);  // 将屏幕坐标转换为地图坐标

    // 获取玩家在新位置时的边界框
    playerBoundingBox.origin = mapSpacePos;

    // 遍历围墙图层的所有瓦片，检查是否与玩家的边界框相交
    int layerWidth = wallLayer->getLayerSize().width;
    int layerHeight = wallLayer->getLayerSize().height;

    for (int x = 0; x < layerWidth; ++x) {
        for (int y = 0; y < layerHeight; ++y) {
            auto tile = wallLayer->getTileAt(cocos2d::Vec2(x, y));

            if (tile) {
                // 获取瓦片的边界框
                cocos2d::Rect tileBoundingBox(x * tileWidth, y * tileHeight, tileWidth, tileHeight);

                // 判断瓦片的边界框是否与玩家的边界框重叠
                if (playerBoundingBox.intersectsRect(tileBoundingBox)) {
                    // 如果重叠，表示玩家与围墙发生碰撞
                    return true;
                }
            }
        }
    }

    // 没有碰撞
    return false;
}


// 检查与工具或其他元素的交互（类似处理）
// 鼠标点击事件处理
void FarmScene::onMouseClicked(cocos2d::Event* event) {
    // 获取鼠标点击的屏幕位置
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();

    // 处理点击与元素的交互
    checkForElementInteraction(clickPos);
}
// 检查点击位置是否与元素重叠
void FarmScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // 将屏幕坐标转换为地图坐标
    cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(clickPos);

    // 检查点击是否与杂草重叠
    for (auto weed : weeds) {
        if (!weed->isRemoved() && weed->getBoundingBox().containsPoint(mapSpacePos)) {
            weed->removeWeed();
            break;
        }
    }
}

