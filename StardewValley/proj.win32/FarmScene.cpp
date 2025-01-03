//农场地图功能完善
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "FarmhouseScene.h"
#include "TaskBar.h" 
#include "Tools.h"
#include "ItemStorage.h"
#include "ItemIDs.h"
#include "Shop.h"
extern Player* mainPlayer; // 主玩家

// 构造析构初始化
FarmScene::FarmScene()
    : Farmmap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
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
    Tools Tool;
    // 加载地图
    Farmmap = cocos2d::TMXTiledMap::create("photo/Map/farmsoilground.tmx");
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // 计算32x32瓦片区域的中心位置
    float mapCenterX = 32 * 64 / 2;
    float mapCenterY = 32 * 64 / 2;
    // 将地图的位置设置为，使得32x32个瓦片区域的中心对齐屏幕中心
    Farmmap->setPosition(
        visibleSize.width / 2 - mapCenterX,
        visibleSize.height / 2 - mapCenterY * 3
    );
    this->addChild(Farmmap);

    // 获取不同的图层
    groundLayer = Farmmap->getLayer("layer1ground");  // 地面层
    wallLayer = Farmmap->getLayer("layer2wall");      // 围墙层
    wallLayer2 = Farmmap->getLayer("layer2wall2");//2

    // 创建玩家
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // 玩家在屏幕中心
    mainPlayer->setScale(1.0f);
    this->addChild(mainPlayer);
       
    //创建农场里面的交互性元素--初始即存在
    // 创建 Farmer NPC 
   // 实例化 Farmer NPC
    farmer = new Resident();
    farmer->init("Alex", "Farmer", "photo/Character/Resident1.png", cocos2d::Vec2(1000, 1000));
    interactiveElements.push_back(farmer); // 添加到可交互元素列表
    this->addChild(farmer);  // 将 Farmer 添加到场景中

    // 实例化 Fisherman NPC
    fisherman = new Resident();
    fisherman->init("Willy", "Fisherman", "photo/Character/Resident2.png", cocos2d::Vec2(1000, -50));
    interactiveElements.push_back(fisherman); // 添加到可交互元素列表
    this->addChild(fisherman);  // 将 Fisherman 添加到场景中

    // 实例化 Breeder NPC
    breeder = new Resident();
    breeder->init("Marnie", "Breeder", "photo/Character/Resident3.png", cocos2d::Vec2(0, -100));
    interactiveElements.push_back(breeder); // 添加到可交互元素列表
    this->addChild(breeder);  // 将 Breeder 添加到场景中


    //创建农场里面的树 冒险地图的矿物
    // 从Tiled地图的Object Layer中读取对象信息并创建对象
    auto objectGroup1 = Farmmap->getObjectGroup("Olayer1Tree");
    auto objectGroup2 = Farmmap->getObjectGroup("Olayer3mine");
    if (objectGroup1) {
        // 遍历所有的对象
        for (auto& object : objectGroup1->getObjects()) {
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

    //初始化矿物
    if (objectGroup2) {
        // 遍历所有的对象
        for (auto& object : objectGroup2->getObjects()) {
            // object 是 Value 类型，可以转化为 ValueMap
            auto obj = object.asValueMap();
           Mine* mine =Mine::create();
            // 获取树在 TileMap 坐标系中的位置
            float tileX = obj["x"].asFloat();
            float tileY = obj["y"].asFloat();

            // 将 TileMap 坐标转换为屏幕坐标
            cocos2d::Vec2 mapPosition = cocos2d::Vec2(tileX, tileY);
            cocos2d::Vec2 worldPosition = Farmmap->convertToWorldSpace(mapPosition);

            // 设置树的位置为屏幕坐标
            mine->setPosition(worldPosition);
            this->addChild(mine);
            mines.push_back(mine);//加入管理矿物的容器
            // 将树添加到可交互对象列表中
            interactiveElements.push_back(mine);
        }
    }
    int mapWidth = groundLayer->getLayerSize().width;
    int mapHeight = groundLayer->getLayerSize().height;

    //创建农舍
    coop = Coop::create();
    coop->setPosition(cocos2d::Vec2(180, 500));  // 设置鸡舍的地图坐标
    this->addChild(coop);  //加入鸡舍子节点


    //创建冒险地图相关元素
  //修复建筑
    market = RepairBuilding::create("photo/Adventure/uncompletedBuilding.png", "photo/Adventure/completedmarket.png");
    market->setPosition(cocos2d::Vec2(-1, -1300));  // 设置建筑物的位置
    this->addChild(market);  // 将建筑物添加到场景中
    interactiveElements.push_back(market);//可点击交互


    // 更新函数
    schedule([this](float deltaTime) {

        update(deltaTime);
        }, "update_key");

    //初始化时间
    
    Clock* clock = Clock::getInstance();
    clock->startClock();
   
        this->addChild(clock);

    // 初始化 plantedCrops

    // 检查并初始化 wateredLand
    if (wateredLand.size() != mapHeight || wateredLand[0].size() != mapWidth) {
        wateredLand.resize(mapHeight, std::vector<WateredLand*>(mapWidth, nullptr));
    }

    // 检查并初始化 plantedCrops
    if (plantedCrops.size() != mapHeight || plantedCrops[0].size() != mapWidth) {
        plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));
    }

    // 检查并初始化 tilledLand
    if (tilledLand.size() != mapHeight || tilledLand[0].size() != mapWidth ) {
        tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));
    }

    canResetCrops = true;

    // 创建菜单层并添加到场景中
    menuLayer = MenuLayer::create();
        this->addChild(menuLayer);

    //工具栏
    Toolbar* toolbar = Toolbar::getInstance();
    this->addChild(toolbar, 5);
    // 初始化任务栏
    TaskBar* taskbar = TaskBar::getInstance();  // 获取 TaskBar 实例
    taskbar->setVisible(false);  // 初始时隐藏任务栏
    this->addChild(taskbar, 10);  // 将任务栏添加到场景中，确保它在最上层

    // 创建任务栏按钮
    auto taskbarButton= Tool.createButton("photo/ui/taskbarbutton.png", cocos2d::Vec2(visibleSize.width - 100, visibleSize.height - 230), 4.0f);
    taskbarButton->addClickEventListener([=](cocos2d::Ref* sender) {
        if (taskbar->isVisible()) {
            taskbar->hide();  // 如果任务栏已经可见，则隐藏它
        }
        else {
            taskbar->show();  // 如果任务栏不可见，则显示它
        }
        });
    this->addChild(taskbarButton,5);
    // 初始化商店
    Shop* shop = Shop::getInstance();
    shop->setVisible(false);
    this->addChild(shop, 13);
    // 创建商店按钮
    ShopButton = Tool.createButton("photo/storage/openshop.png", cocos2d::Vec2(2200, 200), 1.0f);
    ShopButton->addClickEventListener([=](cocos2d::Ref* sender) {
        if (shop->isVisible()) {
            shop->hide();  // 如果任务栏已经可见，则隐藏它
        }
        else {
            shop->show();  // 如果任务栏不可见，则显示它
        }
        });
    this->addChild(ShopButton, 5);


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


    ItemStorage& storage = ItemStorage::getInstance();
    //钓鱼功能按钮
    FishingButton = cocos2d::ui::Button::create("photo/Farm/Fishingrod.png");
    // 设置按钮位置
    FishingButton->setPosition(cocos2d::Vec2(1700, 2300));
    // 设置按钮的 Z 值为第1层（较高的显示层级）
    FishingButton->setLocalZOrder(4);
    // 设置按钮大小，确保按钮不会超出屏幕
    FishingButton->setScale(5.0f);  // 可根据需要调整按钮大小
    FishingButton->setVisible(true);

    FishingButton->addClickEventListener([this,&storage, visibleSize](Ref* sender) {
        // 拿着钓鱼竿才能钓鱼
        if (mainPlayer->Heldtool == 6) {
            // 点击后禁用按钮，防止重复点击
            FishingButton->setEnabled(false);

            // 根据钓鱼等级决定能钓到的鱼
            int fishID = 0;  // 用于记录钓到的鱼的类型ID（不同的ID对应不同的鱼）

            if (mainPlayer->fishingLevel >= 2) {
                // 等级2时，随机钓到F_fish1或者F_fish2
                int randomFish = cocos2d::random(1, 2); // 随机生成1或2
                if (randomFish == 1) {
                    storage.addItem(StorageID::FISH_A, 1);
                    fishID = 1;  // 记录钓到鱼的ID
                }
                else {
                    storage.addItem(StorageID::FISH_B, 1);
                    fishID = 2;
                }
            }
            if (mainPlayer->fishingLevel >= 3) {
                // 等级3时，随机钓到F_fish3、F_fish2或者F_fish1
                int randomFish = cocos2d::random(1, 3); // 随机生成1、2、3
                if (randomFish == 1) {
                    storage.addItem(StorageID::FISH_A, 1);
                    fishID = 1;
                }
                else if (randomFish == 2) {
                    storage.addItem(StorageID::FISH_B, 1);
                    fishID = 2;
                }
                else {
                    storage.addItem(StorageID::FISH_C, 1);
                    fishID = 3;
                }
            }
            if (mainPlayer->fishingLevel >= 4) {
                // 等级4时，随机钓到F_fish2、F_fish2、F_fish3或者F_fish4
                int randomFish = cocos2d::random(1, 4); // 随机生成1、2、3、4
                if (randomFish == 1) {
                    storage.addItem(StorageID::FISH_A, 1);
                    fishID = 1;
                }
                else if (randomFish == 2) {
                    storage.addItem(StorageID::FISH_B, 1);
                    fishID = 2;
                }
                else if (randomFish == 3) {
                    storage.addItem(StorageID::FISH_C, 1);
                    fishID = 3;
                }
                else {
                    storage.addItem(StorageID::FISH_D, 1);
                    fishID = 4;
                }
            }

            // 延时2秒后显示 "上钩了" 提示
            this->scheduleOnce([=](float dt) {
                // 创建提示标签
                auto label = cocos2d::Label::createWithSystemFont("Got a fish!", "Arial", 40);
                label->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));  // 屏幕中心
                label->setTextColor(cocos2d::Color4B::BLACK);  // 设置文字颜色为黑色
                this->addChild(label);

                // 根据钓到的鱼类型显示不同的鱼的图片
                std::string fishImage = "";
                switch (fishID) {
                case 1:
                    fishImage = "photo/Fish/fish_a.png";  // FISH_A 对应的图片路径
                    break;
                case 2:
                    fishImage = "photo/Fish/fish_b.png";  // FISH_B 对应的图片路径
                    break;
                case 3:
                    fishImage = "photo/Fish/fish_c.png";  // FISH_C 对应的图片路径
                    break;
                case 4:
                    fishImage = "photo/Fish/fish_d.png";  // FISH_D 对应的图片路径
                    break;
                }

                // 创建鱼的精灵并显示
                auto fishSprite = cocos2d::Sprite::create(fishImage);
                if (fishSprite) {
                    fishSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 3));  // 设置显示位置
                    this->addChild(fishSprite);
                }

                // 提示显示完毕后，2秒后移除提示
                this->scheduleOnce([=](float dt) {
                    this->removeChild(label);  // 移除提示标签
                    if (fishSprite) {
                        this->removeChild(fishSprite);  // 移除鱼的精灵
                    }
                    // 启用按钮，玩家可以再次点击
                    FishingButton->setEnabled(true);
                    }, 2.0f, "remove_label");

                }, 5.0f - mainPlayer->fishingLevel, "fishing_hooked");  // 延时秒数与个人钓鱼等级有关显示提示
        }
        else {
            // 如果没有钓鱼竿，显示错误提示
            auto label = cocos2d::Label::createWithSystemFont("You need a fishing rod to fish!", "Arial", 40);
            label->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));  // 屏幕中心
            label->setTextColor(cocos2d::Color4B::RED);  // 设置文字颜色为红色
            this->addChild(label);

            // 提示显示完毕后，2秒后移除提示
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);  // 移除错误提示
                }, 2.0f, "remove_no_tool");
        }
    });

    Farmmap->addChild(FishingButton);


    return true;
}

