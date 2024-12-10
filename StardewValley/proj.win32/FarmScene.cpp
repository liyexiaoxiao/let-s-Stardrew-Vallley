//农场地图功能完善
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"


// 构造析构初始化
FarmScene::FarmScene()
    : Farmmap(nullptr), mainPlayer(nullptr),
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
    //mainPlayer->setScale(2.0f);
    this->addChild(mainPlayer);

    //创建农场里面的交互性元素--初始即存在
    // 创建 Farmer NPC 
    farmer = new Farmer();
    //获取这个人物相对于地图的位置
    const cocos2d::Vec2 farmerPos = Farmmap->convertToNodeSpace(cocos2d::Vec2(1180, 1180));  // 将屏幕坐标转换为地图坐标
    std::string debugInfo1 = "farmerPos : x=" + std::to_string(farmerPos.x) +
        ", y=" + std::to_string(farmerPos.y);

    // 显示调试信息
    displayDebugInfo(debugInfo1);
    interactiveElements.push_back(farmer);
    this->addChild(farmer);  // 将 Farmer 添加到场景中

    //创建农场里面的树
    for (int i = 0; i < 10; ++i) {
        Tree* tree = Tree::create();
        // 设置树的初始位置（你可以根据实际需要调整位置）
        tree->setPosition(cocos2d::Vec2((128 + i * 128)+32, 600+32)); // 假设树的初始位置
        interactiveElements.push_back(tree);
        this->addChild(tree); // 将树添加到场景中
        trees.push_back(tree); // 将树加入列表
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

    // 创建并启动时钟
    Clock* clock = Clock::create();
    clock->setLocalZOrder(1000);
    this->addChild(clock); // 将时钟添加到场景
    clock->startClock(); // 启动时钟

    // 初始化 plantedCrops
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));


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
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    return true;
}

void FarmScene::moveMap(float deltaX, float deltaY) {
    // 获取玩家当前的位置
    const cocos2d::Vec2 playerPos = mainPlayer->getPosition();

    // 计算背景移动后的玩家新位置
    const cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY);

    // 判断玩家是否碰到围墙
    if (!isColliding(newPlayerPos)) {
        // 如果没有碰到围墙，更新玩家位置
        const cocos2d::Vec2 newPos = Farmmap->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        Farmmap->setPosition(newPos);

        const cocos2d::Vec2 farmerPosition = farmer->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        farmer->setPosition(farmerPosition);

        const cocos2d::Vec2 buttonPosition = startButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        startButton->setPosition(buttonPosition);

        // 更新树的位置
        for (auto tree : trees) {
            const cocos2d::Vec2 newTreePos = tree->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            tree->setPosition(newTreePos);  // 设置树的新位置
        }
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


// 检查与工具或其他元素的交互（类似处理）
// 鼠标点击事件处理
// 检查点击位置是否是一个实例

void FarmScene::onMouseClicked(cocos2d::Event* event) {
    // 获取鼠标点击的位置
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos); // 转换为OpenGL坐标


    // 判断点击的区域：点击土地还是其他可交互元素
    const auto tileSize = Farmmap->getTileSize();
    int tileX = clickPos.x / tileSize.width;
    int tileY = clickPos.y / tileSize.height;

    int Interacted = checkForElementInteraction(clickPos);

    // 如果点击的瓦片在土地上，调用 `onMouseClickedSoil`
    if (!Interacted && (tileX >= 0 && tileX < groundLayer->getLayerSize().width &&
        tileY >= 0 && tileY < groundLayer->getLayerSize().height)) {
        onMouseClickedSoil(event);  // 处理种植作物的逻辑
    }

}
int FarmScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // 将鼠标点击位置从屏幕坐标系转换为当前场景的坐标系
    cocos2d::Vec2 worldPos = clickPos;

    for (auto& child : interactiveElements) {
        // 获取交互元素的包围盒并检查点击是否在其范围内
        cocos2d::Rect boundingBox = child->getBoundingBox();
        if (boundingBox.containsPoint(worldPos)) {
            child->onClick();  // 触发该元素的 onClick 事件
            CCLOG("Clicked on interactive element: %s", typeid(*child).name());  // 打印调试信息
            return 1;
        }
    }
    return 0;
}

void FarmScene::onMouseClickedSoil(cocos2d::Event* event) {
    // 获取鼠标点击位置
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);

    // 获取瓦片大小和点击位置
    const auto tileSize = Farmmap->getTileSize();
    int tileX = clickPos.x / tileSize.width;
    int tileY = clickPos.y / tileSize.height;

    cocos2d::Vec2 mapPos = Farmmap->getPosition();
    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    // 确保点击在有效范围内
    if (tileX - offsetX >= 0 && tileX - offsetX < groundLayer->getLayerSize().width &&
        tileY - offsetY >= 0 && tileY - offsetY < groundLayer->getLayerSize().height) {

        // 获取点击位置的状态
        int adjustedX = tileX - offsetX;
        int adjustedY = tileY - offsetY;

        // 开垦土地
        if (/*mainPlayer->Heldtool == 1 &&*/ !tilledLand[adjustedY][adjustedX]) {
            TilledLand::tillLand(tileX, tileY, Farmmap, tilledLand);
        }
        // 种植作物
        else if (mainPlayer->Heldseed == 1) {
            Crop* crop = plantedCrops[adjustedY][adjustedX];
            if (tilledLand[adjustedY][adjustedX]&&plantedCrops[adjustedY][adjustedX]== nullptr) {
                // 调用种植方法
                Crop::plantSeed(tileX, tileY, Farmmap, plantedCrops);
            }
            else if (/*mainPlayer->Heldtool == 2 &&*/ crop != nullptr && !crop->isMature()) {
                crop->water(); // 浇水逻辑
            }
        }
    }
}


