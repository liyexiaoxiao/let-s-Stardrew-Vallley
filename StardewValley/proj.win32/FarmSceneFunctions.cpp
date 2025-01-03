#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "WateredLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "ItemStorage.h"
#include "ItemIDs.h"
#include "calendar.h"

using namespace cocos2d;
extern Player* mainPlayer;

//键盘和鼠标相关---------------------------------
// 检查与工具或其他元素的交互（类似处理）
// 鼠标点击事件处理
// 检查点击位置是否是一个实例

void FarmScene::onMouseClicked(cocos2d::Event* event) {
    if (isMenuActive) {
        // 如果菜单活动，忽略鼠标点击事件
        return;
    }
    // 获取鼠标点击的位置
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos); // 转换为OpenGL坐标


    // 判断点击的区域：点击土地还是其他可交互元素
    const auto tileSize = Farmmap->getTileSize();
    const int tileX = clickPos.x / (tileSize.width);
    const int tileY = clickPos.y / (tileSize.height);

    int Interacted = checkForElementInteraction(clickPos);

    // 如果点击的瓦片在土地上，调用 `onMouseClickedSoil`
    if (/*!Interacted && */(tileX >= -groundLayer->getLayerSize().width && tileX < groundLayer->getLayerSize().width &&
        tileY >= 0 && tileY < groundLayer->getLayerSize().height)) {
        onMouseClickedSoil(event);  // 处理种植作物的逻辑
    }

}
int FarmScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    //获得增加仓库内物品数量的资格
    ItemStorage& storage = ItemStorage::getInstance();
    // 将鼠标点击位置从屏幕坐标系转换为当前场景的坐标系
    cocos2d::Vec2 worldPos = clickPos;
    for (auto& child : interactiveElements) {
        // 获取交互元素的包围盒并检查点击是否在其范围内
        cocos2d::Rect boundingBox = child->getBoundingBox();
        if (boundingBox.containsPoint(worldPos)) {
            int choosenextstep = child->onClick();  // 触发该元素的 onClick 事件 通过返回值进行后续操作
            switch(choosenextstep){
            case 1: //返回值为1，进行了砍树操作
                storage.addItem(StorageID::MUTOU, 1);//物品数量加1
                mainPlayer->upgradeSkillTree(static_cast<int>(StorageID::MUTOU), 1);//农业经验值加1
                break;
            case 2:
                storage.addItem(StorageID::MINE, 1);//物品数量加1
                mainPlayer->upgradeSkillTree(static_cast<int>(StorageID::MINE), 1);//农业经验值加1
                break;
            //返回值为2，进行了挖矿操作
            }
        }
    }
    return 0;
}

void FarmScene::onMouseClickedSoil(cocos2d::Event* event) {
    ItemStorage& storage = ItemStorage::getInstance();

    // 获取鼠标点击位置
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);

    // 获取瓦片大小和点击位置
    const auto tileSize = Farmmap->getTileSize();
    int tileX = clickPos.x / (tileSize.width );
    int tileY = clickPos.y / (tileSize.height);

    cocos2d::Vec2 mapPos = Farmmap->getPosition();
    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    // 计算实际的瓦片坐标，偏移量需要减去
    int adjustedX = tileX - offsetX;
    int adjustedY = tileY - offsetY;

    // 确保点击在有效范围内

    if (adjustedX >= 0 && adjustedX < groundLayer->getLayerSize().width &&
        adjustedY >= 0 && adjustedY < groundLayer->getLayerSize().height) {
        // 获取点击位置的状态
        int adjustedX = tileX - offsetX;
        int adjustedY = tileY - offsetY;
        const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
        // 开垦土地
        if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT&&mainPlayer->Heldtool == 2 && !tilledLand[adjustedY][adjustedX]) {
            TilledLand::tillLand(tileX, tileY, Farmmap, tilledLand);
        }
        // 种植作物
        else if (mainPlayer->Heldseed > 0) {
            const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT) {
                // 如果是右键点击
                Crop* crop = plantedCrops[adjustedY][adjustedX];
                if (tilledLand[adjustedY][adjustedX] && plantedCrops[adjustedY][adjustedX] == nullptr) {
                    // 调用种植方法
                    Crop::plantSeed(tileX, tileY, Farmmap, plantedCrops, mainPlayer->Heldseed);
                    
                }

            }
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->Heldtool == 3 && plantedCrops[adjustedY][adjustedX] != nullptr && !plantedCrops[adjustedY][adjustedX]->isMature()) {
                plantedCrops[adjustedY][adjustedX]->water();
                WateredLand::waterLand(tileX, tileY, Farmmap, wateredLand);
            }
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->Heldtool == 2 && plantedCrops[adjustedY][adjustedX] != nullptr && plantedCrops[adjustedY][adjustedX]->isMature()) {

                switch (plantedCrops[adjustedY][adjustedX]->croptype) {
                case 1:
                    storage.addItem(StorageID::FANGFENGCAO, 1);
                    break;
                case 2:
                    storage.addItem(StorageID::SHUMEI, 1);
                    break;
                case 3:
                    storage.addItem(StorageID::NANGUA, 1);
                    break;
                case 4:
                    storage.addItem(StorageID::XIAOMAI, 1);
                    break;
                };
                plantedCrops[adjustedY][adjustedX]->removeFromParent();
                plantedCrops[adjustedY][adjustedX] = nullptr;
            }
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->if_holdfeiliao == 1 && plantedCrops[adjustedY][adjustedX] != nullptr && !plantedCrops[adjustedY][adjustedX]->isMature()) {
                plantedCrops[adjustedY][adjustedX]->shifei();
            }
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->Heldtool == 2 && plantedCrops[adjustedY][adjustedX] != nullptr && plantedCrops[adjustedY][adjustedX]->isDead()) {
                plantedCrops[adjustedY][adjustedX]->removeFromParent();
                plantedCrops[adjustedY][adjustedX] = nullptr;
            }
        }
    }
}


void FarmScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CalendarPanel* calendarPanel = CalendarPanel::create();

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
    case cocos2d::EventKeyboard::KeyCode::KEY_E: // 按e打开或关闭菜单
        if (menuLayer) {
            menuLayer->toggleVisibility();
        }
        isMenuActive = !isMenuActive;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F: // 按F打开日历
        // 创建并显示日历面板
        
        this->addChild(calendarPanel);
        break;
    default:
        break;
    }
}

// 设置按键状态为假，表示按键已松开
void FarmScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

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
void FarmScene::moveMap(float deltaX, float deltaY) {
    // 获取玩家当前的位置
    const cocos2d::Vec2 playerPos = mainPlayer->getPosition();

    // 计算背景移动后的玩家新位置
    const cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY);

    // 判断玩家是否碰到围墙
    if (!isColliding(newPlayerPos) && !isColliding2(newPlayerPos)) {
        // 如果没有碰到围墙，更新玩家位置
         // 如果没有碰到围墙，更新玩家位置
        const cocos2d::Vec2 newPos = Farmmap->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        Farmmap->setPosition(newPos);
        //NPC
        const cocos2d::Vec2 farmerPosition = farmer->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        farmer->setPosition(farmerPosition);
        const cocos2d::Vec2 fishermanPosition = fisherman->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        fisherman->setPosition(fishermanPosition);
        const cocos2d::Vec2 breederPosition = breeder->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        breeder->setPosition(breederPosition);
        //按钮
        const cocos2d::Vec2 buttonPosition = startButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        startButton->setPosition(buttonPosition);
        const cocos2d::Vec2 buttonPosition2 = ShopButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        ShopButton->setPosition(buttonPosition2);
        // 更新树的位置
        for (auto tree : trees) {
            const cocos2d::Vec2 newTreePos = tree->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            tree->setPosition(newTreePos);  // 设置树的新位置
        }
        //矿物
        for (auto mine : mines) {
            const cocos2d::Vec2 newMinePos = mine->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            mine->setPosition(newMinePos);  // 设置树的新位置
        }
        //建筑
        const cocos2d::Vec2 marketPosition = market->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        market->setPosition(marketPosition);
        const cocos2d::Vec2 coopPosition = coop->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        coop->setPosition(coopPosition);
    }
}

void FarmScene::setEnabledForReset(bool enabled) {
    canResetCrops = enabled;
}


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
    Clock* clock = Clock::getInstance();
    clock->onGameTimeReset([this]() {
       
        // 调用 resetAllCrops
        this->resetAllCrops();

        // 禁用 resetAllCrops 调用
        this->setEnabledForReset(false);

        //重置npc可打招呼
        farmer->isfs = false;
        fisherman->isfs = false;
        breeder->isfs = false;
        
        // 重置树、矿产
        for (auto& tree : trees) {
            tree->reset();  // 重置树为初始状态
        }
        for (auto& mine : mines) {
            mine->reset();  // 重置树为初始状态
        }
        // 设置两秒后重新启用
        this->scheduleOnce([this](float) {
            this->setEnabledForReset(true);
            }, 10.0f, "EnableReset");
        });
}

void FarmScene::resetAllCrops() {
    if (!canResetCrops) {
        return; // 如果当前禁用，直接返回
    }

    for (std::vector<Crop*>& row : plantedCrops) {
        for (Crop* crop : row) {
            if (crop != nullptr && crop->feiliao == true) {
                crop->grow();
                crop->feiliao = false;
            }
            if (crop != nullptr&&crop->watered==true) {
                crop->resetWatered();
            }
            else if (crop != nullptr && crop->watered == false&& crop->isMature() == false) {
                crop->notWatered();
            }
        }

        
    }
    int mapWidth = groundLayer->getLayerSize().width;
    int mapHeight = groundLayer->getLayerSize().height;

    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++)
        if (wateredLand[j][i] != nullptr) {
            wateredLand[j][i]->removeFromParent();
            wateredLand[j][i] = nullptr;
        }
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
    // 调整Y坐标（反转Y轴）
    const float adjustedY = Farmmap->getContentSize().height - mapSpacePos.y;

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

bool FarmScene::isColliding2(const cocos2d::Vec2& newPos) {
    // 获取玩家的边界框（Bounding Box）
    cocos2d::Rect playerBoundingBox = mainPlayer->getBoundingBox();

    // 获取瓦片的大小
    const cocos2d::Size tileSize = Farmmap->getTileSize();
    const float tileWidth = tileSize.width;
    const float tileHeight = tileSize.height;

    // 计算新位置
    const cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(newPos);  // 将屏幕坐标转换为地图坐标
    // 调整Y坐标（反转Y轴）
    const float adjustedY = Farmmap->getContentSize().height - mapSpacePos.y;

    // 获取玩家在新位置时的边界框
    playerBoundingBox.origin = cocos2d::Vec2(mapSpacePos.x, adjustedY);

    // 遍历围墙图层的所有瓦片，检查是否与玩家的边界框相交
    const int layerWidth = wallLayer2->getLayerSize().width;
    const int layerHeight = wallLayer2->getLayerSize().height;

    for (int x = 0; x < layerWidth; ++x) {
        for (int y = 0; y < layerHeight; ++y) {
            const auto tile = wallLayer2->getTileAt(cocos2d::Vec2(x, y));

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

