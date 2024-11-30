//ũ����ͼ��������
#include "FarmScene.h"
#include "cocos2d.h"

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
    // ��ȡ��Ļ�ߴ�
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ���ص�ͼ
    Farmmap = cocos2d::Sprite::create("photo/Map/FarmInit.png");
    Farmmap->setPosition(visibleSize.width / 2, visibleSize.height / 2); // ��ʼʱ��ͼ����
    FarmmapSize = Farmmap->getContentSize();  // ��ͼ���ܴ�С
    this->addChild(Farmmap);

    // �������
    mainPlayer = Player::create("photo/Character/mainPlayer.png");
    mainPlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2); // �������Ļ����
    this->addChild(mainPlayer);

    // ���º���
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // ������������
    auto Keyboardlistener = cocos2d::EventListenerKeyboard::create();
    Keyboardlistener->onKeyPressed = CC_CALLBACK_2(FarmScene::onKeyPressed, this);
    Keyboardlistener->onKeyReleased = CC_CALLBACK_2(FarmScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

    return true;
}

#include "FarmScene.h"
#include "Player.h"
#include "cocos2d.h"


// �������״̬
bool isKeyPressed[4] = { false, false, false, false }; // �����ж��Ƿ�����ĳ������ļ�
// �������ӳ�䣺�ϡ��¡�����
enum Direction { UP, DOWN, LEFT, RIGHT };
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
// ��ͼ�ƶ��������
void FarmScene::moveMap(float deltaX, float deltaY) {
    // �����µĵ�ͼλ��
    cocos2d::Vec2 newPosition = Farmmap->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    // ��ֹ��ͼ�����߽�
    if (newPosition.x > FarmmapSize.width / 2) {
        newPosition.x = FarmmapSize.width / 2;  // �����ұ߽�
    }
    if (newPosition.x < -FarmmapSize.width / 2 + cocos2d::Director::getInstance()->getVisibleSize().width) {
        newPosition.x = -FarmmapSize.width / 2 + cocos2d::Director::getInstance()->getVisibleSize().width;  // ������߽�
    }
    if (newPosition.y > FarmmapSize.height / 2) {
        newPosition.y = FarmmapSize.height / 2;  // �����ϱ߽�
    }
    if (newPosition.y < -FarmmapSize.height / 2 + cocos2d::Director::getInstance()->getVisibleSize().height) {
        newPosition.y = -FarmmapSize.height / 2 + cocos2d::Director::getInstance()->getVisibleSize().height;  // �����±߽�
    }

    // ���µ�ͼλ��
    Farmmap->setPosition(newPosition);
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

