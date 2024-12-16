#include "ExploreScene.h"
#include "Clock.h"
#include "cocos2d.h"
using namespace cocos2d;
extern Player* mainPlayer;

//键盘和鼠标相关---------------------------------
// 检查与工具或其他元素的交互（类似处理）
// 鼠标点击事件处理
// 检查点击位置是否是一个实例

void ExploreScene::onMouseClicked(cocos2d::Event* event) {
    // 获取鼠标点击的位置
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos); // 转换为OpenGL坐标


    // 判断点击的区域：点击土地还是其他可交互元素
    const auto tileSize = Exploremap->getTileSize();
    const int tileX = clickPos.x / (tileSize.width);
    const int tileY = clickPos.y / (tileSize.height);

    int Interacted = checkForElementInteraction(clickPos);
}
int ExploreScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // 将鼠标点击位置从屏幕坐标系转换为当前场景的坐标系
    cocos2d::Vec2 worldPos = clickPos;
    for (auto& child : interactiveElements) {
        // 获取交互元素的包围盒并检查点击是否在其范围内
        cocos2d::Rect boundingBox = child->getBoundingBox();
        if (boundingBox.containsPoint(worldPos)) {
            int choosenextstep = child->onClick();  // 触发该元素的 onClick 事件 通过返回值进行后续操作
            //返回值为1，进行了看书操作
            mainPlayer->upgradeSkillTree(ItemCategory::A, 1);//农业经验值加一
            mainPlayer->addItem(ItemID::A_wood, 1);//木材数量加一
            return 1;
        }
    }
    return 0;
}

// 设置按键状态为真，表示按键被按下
void ExploreScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

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
// 设置按键状态为假，表示按键已松开
void ExploreScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

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
//地图显示相关----------------------------------
void ExploreScene::moveMap(float deltaX, float deltaY) {
    // 获取玩家当前的位置
    const cocos2d::Vec2 playerPos = mainPlayer->getPosition();

    // 计算背景移动后的玩家新位置
    const cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY);

    // 判断玩家是否碰到围墙
    if (!isColliding(newPlayerPos)) {
        // 如果没有碰到围墙，更新玩家位置
        const cocos2d::Vec2 newPos = Exploremap->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        Exploremap->setPosition(newPos);
        const cocos2d::Vec2 buttonPosition = returnButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        returnButton->setPosition(buttonPosition);
    }
}
void ExploreScene::update(float deltaTime) {
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
bool ExploreScene::isColliding(const cocos2d::Vec2& newPos) {
    // 获取玩家的边界框（Bounding Box）
    cocos2d::Rect playerBoundingBox = mainPlayer->getBoundingBox();

    // 获取瓦片的大小
    const cocos2d::Size tileSize = Exploremap->getTileSize();
    const float tileWidth = tileSize.width;
    const float tileHeight = tileSize.height;

    // 计算新位置
    const cocos2d::Vec2 mapSpacePos = Exploremap->convertToNodeSpace(newPos);  // 将屏幕坐标转换为地图坐标
    // 调整Y坐标（反转Y轴）
    const float adjustedY = Exploremap->getContentSize().height - mapSpacePos.y;

    // 获取玩家在新位置时的边界框
    playerBoundingBox.origin = cocos2d::Vec2(mapSpacePos.x, adjustedY);

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
