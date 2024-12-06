//农场地图功能完善
#include "FarmScene.h"
#include "Clock.h"


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

    //创建农场里面的npc
    // 创建 Farmer NPC 
    farmer = new Farmer();
   // farmer->setPosition(cocos2d::Vec2(1180, 1180));  // 初始位置设为左下角
    //获取这个人物相对于地图的位置
    const cocos2d::Vec2 farmerPos = Farmmap->convertToNodeSpace(cocos2d::Vec2(1180, 1180));  // 将屏幕坐标转换为地图坐标
    std::string debugInfo1 = "farmerPos : x=" + std::to_string(farmerPos.x) +
        ", y=" + std::to_string(farmerPos.y);

    // 显示调试信息
    displayDebugInfo(debugInfo1);
    interactiveElements.push_back(farmer);
    this->addChild(farmer);  // 将 Farmer 添加到场景中

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

    //监听鼠标点击
    auto Mouselistener = cocos2d::EventListenerMouse::create();
    Mouselistener->onMouseDown = CC_CALLBACK_1(FarmScene::onMouseClicked, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);

    return true;
}

void FarmScene::moveMap(float deltaX, float deltaY) {
    // 获取玩家当前的位置
    const cocos2d::Vec2 playerPos = mainPlayer->getPosition();
    // 计算背景移动后的玩家新位置
    const cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY); 
    //更新地图移动以及跟随他移动的所有图片
    const cocos2d::Vec2 newPos = Farmmap ->getPosition() + cocos2d::Vec2(deltaX, deltaY);
    const cocos2d::Vec2 farmerPosition = farmer->getPosition() + cocos2d::Vec2(deltaX, deltaY);
    // 判断玩家是否碰到围墙
    if (!isColliding(newPlayerPos)) {
        // 如果没有碰到围墙，更新玩家位置
        Farmmap->setPosition(newPos);
        farmer->setPosition(farmerPosition);
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
    const cocos2d::Size tileSize = Farmmap->getTileSize();
    const float tileWidth = tileSize.width;
    const float tileHeight = tileSize.height;

    // 计算新位置
    const cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(newPos);  // 将屏幕坐标转换为地图坐标

    // 获取玩家在新位置时的边界框
    playerBoundingBox.origin = mapSpacePos;

    // 遍历围墙图层的所有瓦片，检查是否与玩家的边界框相交
    const int layerWidth = wallLayer->getLayerSize().width;
    const int layerHeight = wallLayer->getLayerSize().height;

    for (int x = 0; x < layerWidth; ++x) {
        for (int y = 0; y < layerHeight; ++y) {
            const auto tile = wallLayer->getTileAt(cocos2d::Vec2(x, y));

            if (tile) {
                // 获取瓦片的边界框
                const cocos2d::Rect tileBoundingBox(x * tileWidth, y * tileHeight, tileWidth, tileHeight);

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
// 检查点击位置是否是一个实例
void FarmScene::onMouseClicked(cocos2d::Event* event) {
    // 获取鼠标点击的位置
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    // 获取鼠标点击位置（屏幕坐标系）
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);
    // 遍历所有的可交互元素，检查是否被点击
    checkForElementInteraction(clickPos);
}

void FarmScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // 将鼠标点击位置从屏幕坐标系转换为当前场景的坐标系
    // 将屏幕坐标转换为地图的显示坐标（相对地图左下角）
    cocos2d::Vec2 worldPos =clickPos;
    for (auto& child : interactiveElements) {
        // 获取交互元素的包围盒并更新它
        cocos2d::Rect boundingBox = child->getBoundingBox();
        // 创建调试信息
        std::string debugInfo = "Bounding Box: x=" + std::to_string(boundingBox.origin.x) +
            ", y=" + std::to_string(boundingBox.origin.y) +
            ", width=" + std::to_string(boundingBox.size.width) +
            ", height=" + std::to_string(boundingBox.size.height) +
            "\nClick Position: x=" + std::to_string(worldPos.x) +
            ", y=" + std::to_string(worldPos.y);

        // 显示调试信息
        displayDebugInfo(debugInfo);

        // 判断点击位置是否在包围盒内
        if (boundingBox.containsPoint(worldPos)) {
            // 如果点击了该元素，触发其 onClick 事件
            child->onClick();
            break;
        }
    }
}
