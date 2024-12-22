//ũ����ͼ��������
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "FarmhouseScene.h"
#include"ExploreScene.h"

extern Player* mainPlayer; // �����


// ����������ʼ��
FarmScene::FarmScene()
    : Farmmap(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
    /*�ͷ�������Դ
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

    // ���ص�ͼ
    Farmmap = cocos2d::TMXTiledMap::create("photo/Map/farmsoilground.tmx");
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // ����32x32��Ƭ���������λ��
    float mapCenterX = 32 * 64 / 2;
    float mapCenterY = 32 * 64 / 2;
    // ����ͼ��λ������Ϊ��ʹ��32x32����Ƭ��������Ķ�����Ļ����
    Farmmap->setPosition(
        visibleSize.width / 2 - mapCenterX,
        visibleSize.height / 2 - mapCenterY * 3
    );
    this->addChild(Farmmap);

    // ��ȡ��ͬ��ͼ��
    groundLayer = Farmmap->getLayer("layer1ground");  // �����
    wallLayer = Farmmap->getLayer("layer2wall");      // Χǽ��
    wallLayer2 = Farmmap->getLayer("layer2wall2");//2


    // �������
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // �������Ļ����
    mainPlayer->setScale(1.0f);
    this->addChild(mainPlayer);

    //����ũ������Ľ�����Ԫ��--��ʼ������
    // ���� Farmer NPC 
    //1.ũ��
    farmer = new Resident();
    farmer->init("Alex", "Farmer", "photo/Character/Resident1.png", cocos2d::Vec2(1000, 1000));
    interactiveElements.push_back(farmer);//�ɵ������
    this->addChild(farmer);  // �� Farmer ��ӵ�������
    //2.���
    fisherman = new Resident();
    fisherman->init("Willy", "Fisherman", "photo/Character/Resident2.png", cocos2d::Vec2(1000, -50));
    interactiveElements.push_back(fisherman);//�ɵ������
    this->addChild(fisherman);  // ��  fisherman ��ӵ�������
    //3.������
    breeder = new Resident();
    breeder->init("Marnie", "Breeder", "photo/Character/Resident3.png", cocos2d::Vec2(0, -100));
    interactiveElements.push_back(breeder);//�ɵ������
    this->addChild(breeder);  // ��  fisherman ��ӵ�������

    //����ũ���������
    // ��Tiled��ͼ��Object Layer�ж�ȡ������Ϣ����������
    auto objectGroup = Farmmap->getObjectGroup("Olayer1Tree");
    if (objectGroup) {
        // �������еĶ���
        for (auto& object : objectGroup->getObjects()) {
            // object �� Value ���ͣ�����ת��Ϊ ValueMap
            auto obj = object.asValueMap();

            // ���� "type" �ֶ��ж϶�������
            if (obj["type"].asString() == "tree") {
                Tree* tree = Tree::create();
                // ��ȡ���� TileMap ����ϵ�е�λ��
                float tileX = obj["x"].asFloat();
                float tileY = obj["y"].asFloat();

                // �� TileMap ����ת��Ϊ��Ļ����
                cocos2d::Vec2 mapPosition = cocos2d::Vec2(tileX, tileY);
                cocos2d::Vec2 worldPosition = Farmmap->convertToWorldSpace(mapPosition);

                // ��������λ��Ϊ��Ļ����
                tree->setPosition(worldPosition);
                this->addChild(tree);
                trees.push_back(tree);//���������������
                // ������ӵ��ɽ��������б���
                interactiveElements.push_back(tree);
            }
            // ������Ӹ������͵Ķ���
        }
    }
    // ��ʼ����������δ����
    int mapWidth = groundLayer->getLayerSize().width;
    int mapHeight = groundLayer->getLayerSize().height;

    //��������
    coop = Coop::create();
    coop->setPosition(cocos2d::Vec2(1900, 300));  // ���ü���ĵ�ͼ����
    this->addChild(coop);  //���뼦���ӽڵ�


    //����ð�յ�ͼ���Ԫ��
  //�޸�����
    market = RepairBuilding::create("photo/Adventure/uncompletedBuilding.png", "photo/Adventure/completedmarket.png");
    market->setPosition(cocos2d::Vec2(-1, -1300));  // ���ý������λ��
    this->addChild(market);  // ����������ӵ�������
    interactiveElements.push_back(market);//�ɵ������


    // ���º���
    schedule([this](float deltaTime) {

        update(deltaTime);
        }, "update_key");

    //��ʼ��ʱ��
    Clock* clock = Clock::getInstance();
    clock->startClock();
    this->addChild(clock);

    // ��ʼ�� plantedCrops

    // ��鲢��ʼ�� wateredLand
    if (wateredLand.size() != mapHeight || wateredLand[0].size() != mapWidth) {
        wateredLand.resize(mapHeight, std::vector<WateredLand*>(mapWidth, nullptr));
    }

    // ��鲢��ʼ�� plantedCrops
    if (plantedCrops.size() != mapHeight || plantedCrops[0].size() != mapWidth) {
        plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));
    }

    // ��鲢��ʼ�� tilledLand
    if (tilledLand.size() != mapHeight || tilledLand[0].size() != mapWidth || clock->getGameTime() == 0) {
        tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));
    }

    canResetCrops = true;

    // �����˵��㲢��ӵ�������
    menuLayer = MenuLayer::create();
    this->addChild(menuLayer);
    //������
    Toolbar* toolbar = Toolbar::getInstance();
    this->addChild(toolbar, 5);

    // ������������
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);


    //���������
    auto Mouselistener = cocos2d::EventListenerMouse::create();
    Mouselistener->onMouseDown = CC_CALLBACK_1(FarmScene::onMouseClicked, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);


    //������������
     //������ť���������ڳ����������ť�����Ǹ�����ͼ�꣬player����--���Ͻǣ���������ӽ������ڳ�����
    startButton = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");
    // ���ð�ťλ��
    startButton->setPosition(cocos2d::Vec2(1, 1020));
    // ���ð�ť�� Z ֵΪ��1�㣨�ϸߵ���ʾ�㼶��
    startButton->setLocalZOrder(1);
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton->setScale(0.8f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť����¼������ӵ��ڶ������棺���ڣ�����
    startButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmhouseScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    startButton2 = cocos2d::ui::Button::create("photo/startup_p/enterhome.png");//�����ø�
    // ���ð�ťλ��
    startButton2->setPosition(cocos2d::Vec2(1180, 1000));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton2->setScale(0.8f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť�� Z ֵΪ��1�㣨�ϸߵ���ʾ�㼶��
    startButton->setLocalZOrder(1);
    // ���ð�ť����¼������ӵ��ڶ������棺ð�գ�����
    startButton2->addClickEventListener([=](Ref* sender) {
        // �л��� ExploreScene ����
        //onExit();
        auto exploreScene = ExploreScene::create();  // �����³���
        auto transition = cocos2d::TransitionFade::create(1.0f, exploreScene, cocos2d::Color3B::WHITE);  // �����л�����Ч��
        cocos2d::Director::getInstance()->replaceScene(transition);  // ִ�г����滻
        });
    this->addChild(startButton2);

    //���㹦�ܰ�ť
    FishingButton = cocos2d::ui::Button::create("photo/Farm/Fishingrod.png");
    // ���ð�ťλ��
    FishingButton->setPosition(cocos2d::Vec2(1700, 200));
    // ���ð�ť�� Z ֵΪ��1�㣨�ϸߵ���ʾ�㼶��
    FishingButton->setLocalZOrder(1);
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    FishingButton->setScale(5.0f);  // �ɸ�����Ҫ������ť��С
    FishingButton->setVisible(true);

    /*FishingButton->addClickEventListener([=](Ref* sender) {
        // ���ŵ���Ͳ��ܵ���
        if (mainPlayer->Heldtool == 6) {
            // �������ð�ť����ֹ�ظ����
            FishingButton->setEnabled(false);

            // ���ݵ���ȼ������ܵ�������
            int fishID = 0;  // ���ڼ�¼�������������ID����ͬ��ID��Ӧ��ͬ���㣩

            if (mainPlayer->fishingLevel >= 2) {
                // �ȼ�2ʱ���������F_fish1����F_fish2
                int randomFish = cocos2d::random(1, 2); // �������1��2
                if (randomFish == 1) {
                    storage.addItem(StorageID::FISH_A, 1);
                    fishID = 1;  // ��¼�������ID
                }
                else {
                    storage.addItem(StorageID::FISH_B, 1);
                    fishID = 2;
                }
            }
            if (mainPlayer->fishingLevel >= 3) {
                // �ȼ�3ʱ���������F_fish3��F_fish2����F_fish1
                int randomFish = cocos2d::random(1, 3); // �������1��2��3
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
                // �ȼ�4ʱ���������F_fish2��F_fish2��F_fish3����F_fish4
                int randomFish = cocos2d::random(1, 4); // �������1��2��3��4
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

            // ��ʱ2�����ʾ "�Ϲ���" ��ʾ
            this->scheduleOnce([=](float dt) {
                // ������ʾ��ǩ
                auto label = cocos2d::Label::createWithSystemFont("Got a fish!", "Arial", 40);
                label->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));  // ��Ļ����
                label->setTextColor(cocos2d::Color4B::BLACK);  // ����������ɫΪ��ɫ
                this->addChild(label);

                // ���ݵ�������������ʾ��ͬ�����ͼƬ
                std::string fishImage = "";
                switch (fishID) {
                case 1:
                    fishImage = "photo/Fish/fish_a.png";  // FISH_A ��Ӧ��ͼƬ·��
                    break;
                case 2:
                    fishImage = "photo/Fish/fish_b.png";  // FISH_B ��Ӧ��ͼƬ·��
                    break;
                case 3:
                    fishImage = "photo/Fish/fish_c.png";  // FISH_C ��Ӧ��ͼƬ·��
                    break;
                case 4:
                    fishImage = "photo/Fish/fish_d.png";  // FISH_D ��Ӧ��ͼƬ·��
                    break;
                }

                // ������ľ��鲢��ʾ
                auto fishSprite = cocos2d::Sprite::create(fishImage);
                if (fishSprite) {
                    fishSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 3));  // ������ʾλ��
                    this->addChild(fishSprite);
                }

                // ��ʾ��ʾ��Ϻ�2����Ƴ���ʾ
                this->scheduleOnce([=](float dt) {
                    this->removeChild(label);  // �Ƴ���ʾ��ǩ
                    if (fishSprite) {
                        this->removeChild(fishSprite);  // �Ƴ���ľ���
                    }
                    // ���ð�ť����ҿ����ٴε��
                    FishingButton->setEnabled(true);
                    }, 2.0f, "remove_label");

                }, 5.0f - mainPlayer->fishingLevel, "fishing_hooked");  // ��ʱ��������˵���ȼ��й���ʾ��ʾ
        }
        else {
            // ���û�е���ͣ���ʾ������ʾ
            auto label = cocos2d::Label::createWithSystemFont("You need a fishing rod to fish!", "Arial", 40);
            label->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));  // ��Ļ����
            label->setTextColor(cocos2d::Color4B::RED);  // ����������ɫΪ��ɫ
            this->addChild(label);

            // ��ʾ��ʾ��Ϻ�2����Ƴ���ʾ
            this->scheduleOnce([=](float dt) {
                this->removeChild(label);  // �Ƴ�������ʾ
                }, 2.0f, "remove_no_tool");
        }
    });*/

    Farmmap->addChild(FishingButton);


    return true;
}

////��Դ����--�ֶ�
//void FarmScene::onExit() {
//    if (mainPlayer) {
//        this->removeChild(mainPlayer);
//    }

//    // ������Ԫ��
//    for (auto element : interactiveElements) {
//        delete element;  // �ֶ�ɾ������Ԫ��
//    }
//    interactiveElements.clear();  // �������

//    // �Ƴ��¼�������
//    _eventDispatcher->removeEventListenersForTarget(this);

//    // ����������Դ���繤�ߡ�����
//    for (auto tree : trees) {
//        delete tree;  // �ֶ�ɾ����
//    }
//    trees.clear();  // ������б�

//    // ����ж�ʱ����������Ҫȡ������
//    this->unscheduleAllCallbacks();  // ȡ�����ж�ʱ��

//    // ���û���� onExit ����
//    Scene::onExit();
//    
//}
