//农场地图功能完善
#include "FarmScene.h"
#include "cocos2d.h"

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
    // 获取屏幕尺寸
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 加载地图
    Farmmap = cocos2d::Sprite::create("photo/Map/FarmInit.png");
    Farmmap->setPosition(visibleSize.width / 2, visibleSize.height / 2); // 初始时地图居中
    FarmmapSize = Farmmap->getContentSize();  // 地图的总大小
    this->addChild(Farmmap);

    // 创建玩家
    mainPlayer = Player::create("photo/Character/mainPlayer.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // 玩家在屏幕中心
    this->addChild(mainPlayer);

    // 更新函数
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // 监听键盘输入
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

    return true;
}

#include "FarmScene.h"
#include "Player.h"
#include "cocos2d.h"


// 定义控制状态
bool isKeyPressed[4] = { false, false, false, false }; // 用于判断是否按下了某个方向的键
// 方向键的映射：上、下、左、右
enum Direction { UP, DOWN, LEFT, RIGHT };
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
// 地图移动控制相关
void FarmScene::moveMap(float deltaX, float deltaY) {
    // 计算新的地图位置
    cocos2d::Vec2 newPosition = Farmmap->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    // 防止地图超出边界
    if (newPosition.x > FarmmapSize.width / 2) {
        newPosition.x = FarmmapSize.width / 2;  // 到达右边界
    }
    if (newPosition.x < -FarmmapSize.width / 2 + cocos2d::Director::getInstance()->getVisibleSize().width) {
        newPosition.x = -FarmmapSize.width / 2 + cocos2d::Director::getInstance()->getVisibleSize().width;  // 到达左边界
    }
    if (newPosition.y > FarmmapSize.height / 2) {
        newPosition.y = FarmmapSize.height / 2;  // 到达上边界
    }
    if (newPosition.y < -FarmmapSize.height / 2 + cocos2d::Director::getInstance()->getVisibleSize().height) {
        newPosition.y = -FarmmapSize.height / 2 + cocos2d::Director::getInstance()->getVisibleSize().height;  // 到达下边界
    }

    // 更新地图位置
    Farmmap->setPosition(newPosition);
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

