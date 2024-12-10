//ũ����ͼ��������
#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "Crop.h"
#include "cocos2d.h"


// ����������ʼ��
FarmScene::FarmScene()
    : Farmmap(nullptr), mainPlayer(nullptr),
    movingUp(false), movingDown(false),
    movingLeft(false), movingRight(false) {
}

FarmScene::~FarmScene() {
    // �ͷ�������Դ
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

    // ���ص�ͼ
    Farmmap = cocos2d::TMXTiledMap::create("photo/Map/0farmsoilground2048x2048.tmx");
    Farmmap->setContentSize(cocos2d::Size(2048, 2048));//���ô�С
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Farmmap->setPosition(visibleSize.width / 2 - Farmmap->getContentSize().width / 2,
        visibleSize.height / 2 - Farmmap->getContentSize().height / 2);
    this->addChild(Farmmap);

    // ��ȡ��ͬ��ͼ��
    groundLayer = Farmmap->getLayer("layer1ground");  // �����
    wallLayer = Farmmap->getLayer("layer2wall");      // Χǽ��


    // �������
    mainPlayer = Player::create("photo/Character/PlayerFront1.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // �������Ļ����
    //mainPlayer->setScale(2.0f);
    this->addChild(mainPlayer);

    //����ũ������Ľ�����Ԫ��--��ʼ������
    // ���� Farmer NPC 
    farmer = new Farmer();
    //��ȡ�����������ڵ�ͼ��λ��
    const cocos2d::Vec2 farmerPos = Farmmap->convertToNodeSpace(cocos2d::Vec2(1180, 1180));  // ����Ļ����ת��Ϊ��ͼ����
    std::string debugInfo1 = "farmerPos : x=" + std::to_string(farmerPos.x) +
        ", y=" + std::to_string(farmerPos.y);

    // ��ʾ������Ϣ
    displayDebugInfo(debugInfo1);
    interactiveElements.push_back(farmer);
    this->addChild(farmer);  // �� Farmer ��ӵ�������

    //����ũ���������
    for (int i = 0; i < 10; ++i) {
        Tree* tree = Tree::create();
        // �������ĳ�ʼλ�ã�����Ը���ʵ����Ҫ����λ�ã�
        tree->setPosition(cocos2d::Vec2((128 + i * 128)+32, 600+32)); // �������ĳ�ʼλ��
        interactiveElements.push_back(tree);
        this->addChild(tree); // ������ӵ�������
        trees.push_back(tree); // ���������б�
    }

    // ��ʼ����������δ����
    int mapWidth = groundLayer->getLayerSize().width;
    int mapHeight = groundLayer->getLayerSize().height;
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));
    tilledLand.resize(mapHeight, std::vector<TilledLand*>(mapWidth, nullptr));


    // ���º���
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // ����������ʱ��
    Clock* clock = Clock::create();
    clock->setLocalZOrder(1000);
    this->addChild(clock); // ��ʱ����ӵ�����
    clock->startClock(); // ����ʱ��

    // ��ʼ�� plantedCrops
    plantedCrops.resize(mapHeight, std::vector<Crop*>(mapWidth, nullptr));


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
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton->setScale(0.8f);  // �ɸ�����Ҫ������ť��С
    // ���ð�ť����¼������ӵ��ڶ������棺���ڣ�����
    startButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    return true;
}

void FarmScene::moveMap(float deltaX, float deltaY) {
    // ��ȡ��ҵ�ǰ��λ��
    const cocos2d::Vec2 playerPos = mainPlayer->getPosition();

    // ���㱳���ƶ���������λ��
    const cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY);

    // �ж�����Ƿ�����Χǽ
    if (!isColliding(newPlayerPos)) {
        // ���û������Χǽ���������λ��
        const cocos2d::Vec2 newPos = Farmmap->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        Farmmap->setPosition(newPos);

        const cocos2d::Vec2 farmerPosition = farmer->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        farmer->setPosition(farmerPosition);

        const cocos2d::Vec2 buttonPosition = startButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        startButton->setPosition(buttonPosition);

        // ��������λ��
        for (auto tree : trees) {
            const cocos2d::Vec2 newTreePos = tree->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            tree->setPosition(newTreePos);  // ����������λ��
        }
    }
}

// ��ͼ��ʾ���
void FarmScene::update(float deltaTime) {
    // ÿ֡���£�����Ƿ��а����������������ƶ���ͼ
    if (movingUp) {
        moveMap(0, -10.0f); // ���ϳ����ƶ�
    }
    if (movingDown) {
        moveMap(0, +10.0f); // ���³����ƶ�
    }
    if (movingLeft) {
        moveMap(+10.0f, 0); // ��������ƶ�
    }
    if (movingRight) {
        moveMap(-10.0f, 0); // ���ҳ����ƶ�
    }
}

void FarmScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // ���ð���״̬Ϊ�棬��ʾ����������
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
    // ���ð���״̬Ϊ�٣���ʾ�������ɿ�
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
    // ��ȡ��ҵı߽��Bounding Box��
    cocos2d::Rect playerBoundingBox = mainPlayer->getBoundingBox();

    // ��ȡ��Ƭ�Ĵ�С
    const cocos2d::Size tileSize = Farmmap->getTileSize();
    const float tileWidth = tileSize.width;
    const float tileHeight = tileSize.height;

    // ������λ��
    const cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(newPos);  // ����Ļ����ת��Ϊ��ͼ����
    // ����Y���꣨��תY�ᣩ
    const float adjustedY = Farmmap->getContentSize().height - mapSpacePos.y;

    // ��ȡ�������λ��ʱ�ı߽��
    playerBoundingBox.origin = cocos2d::Vec2(mapSpacePos.x, adjustedY);

    // ����Χǽͼ���������Ƭ������Ƿ�����ҵı߽���ཻ
    const int layerWidth = wallLayer->getLayerSize().width;
    const int layerHeight = wallLayer->getLayerSize().height;

    for (int x = 0; x < layerWidth; ++x) {
        for (int y = 0; y < layerHeight; ++y) {
            const auto tile = wallLayer->getTileAt(cocos2d::Vec2(x, y));

            if (tile) {
                // ��ȡ��Ƭ�ı߽��
                const cocos2d::Rect tileBoundingBox(x * tileWidth, y * tileHeight, tileWidth, tileHeight);

                // �ж���Ƭ�ı߽���Ƿ�����ҵı߽���ص�
                if (playerBoundingBox.intersectsRect(tileBoundingBox)) {
                    // ����ص�����ʾ�����Χǽ������ײ
                    return true;
                }
            }
        }
    }

    // û����ײ
    return false;
}


// ����빤�߻�����Ԫ�صĽ��������ƴ���
// ������¼�����
// �����λ���Ƿ���һ��ʵ��

void FarmScene::onMouseClicked(cocos2d::Event* event) {
    // ��ȡ�������λ��
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos); // ת��ΪOpenGL����


    // �жϵ�������򣺵�����ػ��������ɽ���Ԫ��
    const auto tileSize = Farmmap->getTileSize();
    int tileX = clickPos.x / tileSize.width;
    int tileY = clickPos.y / tileSize.height;

    int Interacted = checkForElementInteraction(clickPos);

    // ����������Ƭ�������ϣ����� `onMouseClickedSoil`
    if (!Interacted && (tileX >= 0 && tileX < groundLayer->getLayerSize().width &&
        tileY >= 0 && tileY < groundLayer->getLayerSize().height)) {
        onMouseClickedSoil(event);  // ������ֲ������߼�
    }

}
int FarmScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // �������λ�ô���Ļ����ϵת��Ϊ��ǰ����������ϵ
    cocos2d::Vec2 worldPos = clickPos;

    for (auto& child : interactiveElements) {
        // ��ȡ����Ԫ�صİ�Χ�в�������Ƿ����䷶Χ��
        cocos2d::Rect boundingBox = child->getBoundingBox();
        if (boundingBox.containsPoint(worldPos)) {
            child->onClick();  // ������Ԫ�ص� onClick �¼�
            CCLOG("Clicked on interactive element: %s", typeid(*child).name());  // ��ӡ������Ϣ
            return 1;
        }
    }
    return 0;
}

void FarmScene::onMouseClickedSoil(cocos2d::Event* event) {
    // ��ȡ�����λ��
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);

    // ��ȡ��Ƭ��С�͵��λ��
    const auto tileSize = Farmmap->getTileSize();
    int tileX = clickPos.x / tileSize.width;
    int tileY = clickPos.y / tileSize.height;

    cocos2d::Vec2 mapPos = Farmmap->getPosition();
    int offsetX = static_cast<int>(std::round(mapPos.x / tileSize.width));
    int offsetY = static_cast<int>(std::round(mapPos.y / tileSize.height));

    // ȷ���������Ч��Χ��
    if (tileX - offsetX >= 0 && tileX - offsetX < groundLayer->getLayerSize().width &&
        tileY - offsetY >= 0 && tileY - offsetY < groundLayer->getLayerSize().height) {

        // ��ȡ���λ�õ�״̬
        int adjustedX = tileX - offsetX;
        int adjustedY = tileY - offsetY;

        // ��������
        if (/*mainPlayer->Heldtool == 1 &&*/ !tilledLand[adjustedY][adjustedX]) {
            TilledLand::tillLand(tileX, tileY, Farmmap, tilledLand);
        }
        // ��ֲ����
        else if (mainPlayer->Heldseed == 1) {
            Crop* crop = plantedCrops[adjustedY][adjustedX];
            if (tilledLand[adjustedY][adjustedX]&&plantedCrops[adjustedY][adjustedX]== nullptr) {
                // ������ֲ����
                Crop::plantSeed(tileX, tileY, Farmmap, plantedCrops);
            }
            else if (/*mainPlayer->Heldtool == 2 &&*/ crop != nullptr && !crop->isMature()) {
                crop->water(); // ��ˮ�߼�
            }
        }
    }
}


