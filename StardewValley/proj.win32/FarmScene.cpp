//ũ����ͼ��������
#include "FarmScene.h"
#include "cocos2d.h"
#include "Clock.h"
#include "Player.h"

// ����������ʼ��
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
    mainPlayer->setScale(2.0f);
    this->addChild(mainPlayer);

    // ���º���
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // ����������ʱ��
    Clock* clock = Clock::create();
    clock->setLocalZOrder(1000);
    this->addChild(clock); // ��ʱ����ӵ�����
    clock->startClock(); // ����ʱ��

    // ������������
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

    return true;
}

void FarmScene::moveMap(float deltaX, float deltaY) {
    // ��ȡ��ҵ�ǰ��λ��
    cocos2d::Vec2 playerPos = mainPlayer->getPosition();
    // ���㱳���ƶ���������λ��
    cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY); 
    //���µ�ͼ�ƶ�
    cocos2d::Vec2 newPos = Farmmap ->getPosition() + cocos2d::Vec2(deltaX, deltaY);
    // �ж�����Ƿ�����Χǽ
    if (!isColliding(newPlayerPos)) {
        // ���û������Χǽ���������λ��
        Farmmap->setPosition(newPos);
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
    cocos2d::Size tileSize = Farmmap->getTileSize();
    float tileWidth = tileSize.width;
    float tileHeight = tileSize.height;

    // ������λ��
    cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(newPos);  // ����Ļ����ת��Ϊ��ͼ����

    // ��ȡ�������λ��ʱ�ı߽��
    playerBoundingBox.origin = mapSpacePos;

    // ����Χǽͼ���������Ƭ������Ƿ�����ҵı߽���ཻ
    int layerWidth = wallLayer->getLayerSize().width;
    int layerHeight = wallLayer->getLayerSize().height;

    for (int x = 0; x < layerWidth; ++x) {
        for (int y = 0; y < layerHeight; ++y) {
            auto tile = wallLayer->getTileAt(cocos2d::Vec2(x, y));

            if (tile) {
                // ��ȡ��Ƭ�ı߽��
                cocos2d::Rect tileBoundingBox(x * tileWidth, y * tileHeight, tileWidth, tileHeight);

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
void FarmScene::onMouseClicked(cocos2d::Event* event) {
    // ��ȡ���������Ļλ��
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();

    // ��������Ԫ�صĽ���
    checkForElementInteraction(clickPos);
}
// �����λ���Ƿ���Ԫ���ص�
void FarmScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // ����Ļ����ת��Ϊ��ͼ����
    cocos2d::Vec2 mapSpacePos = Farmmap->convertToNodeSpace(clickPos);

    // ������Ƿ����Ӳ��ص�
    for (auto weed : weeds) {
        if (!weed->isRemoved() && weed->getBoundingBox().containsPoint(mapSpacePos)) {
            weed->removeWeed();
            break;
        }
    }
}

