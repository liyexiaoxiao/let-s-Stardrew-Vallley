#include "ExploreScene.h"
#include "Clock.h"
#include "cocos2d.h"
using namespace cocos2d;
extern Player* mainPlayer;

//���̺�������---------------------------------
// ����빤�߻�����Ԫ�صĽ��������ƴ���
// ������¼�����
// �����λ���Ƿ���һ��ʵ��

void ExploreScene::onMouseClicked(cocos2d::Event* event) {
    // ��ȡ�������λ��
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos); // ת��ΪOpenGL����


    // �жϵ�������򣺵�����ػ��������ɽ���Ԫ��
    const auto tileSize = Exploremap->getTileSize();
    const int tileX = clickPos.x / (tileSize.width);
    const int tileY = clickPos.y / (tileSize.height);

    int Interacted = checkForElementInteraction(clickPos);
}
int ExploreScene::checkForElementInteraction(const cocos2d::Vec2& clickPos) {
    // �������λ�ô���Ļ����ϵת��Ϊ��ǰ����������ϵ
    cocos2d::Vec2 worldPos = clickPos;
    for (auto& child : interactiveElements) {
        // ��ȡ����Ԫ�صİ�Χ�в�������Ƿ����䷶Χ��
        cocos2d::Rect boundingBox = child->getBoundingBox();
        if (boundingBox.containsPoint(worldPos)) {
            int choosenextstep = child->onClick();  // ������Ԫ�ص� onClick �¼� ͨ������ֵ���к�������
            //����ֵΪ1�������˿������
            mainPlayer->upgradeSkillTree(ItemCategory::A, 1);//ũҵ����ֵ��һ
            mainPlayer->addItem(ItemID::A_wood, 1);//ľ��������һ
            return 1;
        }
    }
    return 0;
}

// ���ð���״̬Ϊ�棬��ʾ����������
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
// ���ð���״̬Ϊ�٣���ʾ�������ɿ�
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
//��ͼ��ʾ���----------------------------------
void ExploreScene::moveMap(float deltaX, float deltaY) {
    // ��ȡ��ҵ�ǰ��λ��
    const cocos2d::Vec2 playerPos = mainPlayer->getPosition();

    // ���㱳���ƶ���������λ��
    const cocos2d::Vec2 newPlayerPos = playerPos - cocos2d::Vec2(deltaX, deltaY);

    // �ж�����Ƿ�����Χǽ
    if (!isColliding(newPlayerPos)) {
        // ���û������Χǽ���������λ��
        const cocos2d::Vec2 newPos = Exploremap->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        Exploremap->setPosition(newPos);
        const cocos2d::Vec2 buttonPosition = returnButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        returnButton->setPosition(buttonPosition);
    }
}
void ExploreScene::update(float deltaTime) {
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
bool ExploreScene::isColliding(const cocos2d::Vec2& newPos) {
    // ��ȡ��ҵı߽��Bounding Box��
    cocos2d::Rect playerBoundingBox = mainPlayer->getBoundingBox();

    // ��ȡ��Ƭ�Ĵ�С
    const cocos2d::Size tileSize = Exploremap->getTileSize();
    const float tileWidth = tileSize.width;
    const float tileHeight = tileSize.height;

    // ������λ��
    const cocos2d::Vec2 mapSpacePos = Exploremap->convertToNodeSpace(newPos);  // ����Ļ����ת��Ϊ��ͼ����
    // ����Y���꣨��תY�ᣩ
    const float adjustedY = Exploremap->getContentSize().height - mapSpacePos.y;

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
