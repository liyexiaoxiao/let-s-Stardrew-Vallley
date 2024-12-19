#include "FarmScene.h"
#include "Clock.h"
#include "tilledLand.h"
#include "WateredLand.h"
#include "Crop.h"
#include "cocos2d.h"
#include "MenuLayer.h"
using namespace cocos2d;
extern Player* mainPlayer;

//���̺�������---------------------------------
// ����빤�߻�����Ԫ�صĽ��������ƴ���
// ������¼�����
// �����λ���Ƿ���һ��ʵ��

void FarmScene::onMouseClicked(cocos2d::Event* event) {
    if (isMenuActive) {
        // ����˵��������������¼�
        return;
    }
    // ��ȡ�������λ��
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    cocos2d::Vec2 clickPos = mouseEvent->getLocation();
    clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos); // ת��ΪOpenGL����


    // �жϵ�������򣺵�����ػ��������ɽ���Ԫ��
    const auto tileSize = Farmmap->getTileSize();
    const int tileX = clickPos.x / (tileSize.width);
    const int tileY = clickPos.y / (tileSize.height);

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
            int choosenextstep = child->onClick();  // ������Ԫ�ص� onClick �¼� ͨ������ֵ���к�������
            //����ֵΪ1�������˿�������
            mainPlayer->upgradeSkillTree(ItemCategory::A, 1);//ũҵ����ֵ��һ
            mainPlayer->addItem(ItemID::A_wood, 1);//ľ��������һ
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
    int tileX = clickPos.x / (tileSize.width );
    int tileY = clickPos.y / (tileSize.height);

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
        else if (mainPlayer->Heldseed > 0) {
            Crop* crop = plantedCrops[adjustedY][adjustedX];
            if (tilledLand[adjustedY][adjustedX] && plantedCrops[adjustedY][adjustedX] == nullptr) {
                // ������ֲ����
                Crop::plantSeed(tileX, tileY, Farmmap, plantedCrops, mainPlayer->Heldseed);
            }
            
        }
        if (/*mainPlayer->Heldtool == 2 &&*/ plantedCrops[adjustedY][adjustedX] != nullptr && !plantedCrops[adjustedY][adjustedX]->isMature()) {


            plantedCrops[adjustedY][adjustedX]->water();
            WateredLand::waterLand(tileX, tileY, Farmmap, wateredLand);
        }
    }
}


// ���ð���״̬Ϊ�棬��ʾ����������
void FarmScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

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
        case cocos2d::EventKeyboard::KeyCode::KEY_E://��e�򿪻�رղ˵�
            if (menuLayer) {
                menuLayer->createPanels();
                menuLayer->toggleVisibility();
            }
            isMenuActive = !isMenuActive;
            break;
        default:
            break;
    }
}
// ���ð���״̬Ϊ�٣���ʾ�������ɿ�
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

//��ͼ��ʾ���----------------------------------
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
        const cocos2d::Vec2 fishermanPosition = fisherman->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        fisherman->setPosition(fishermanPosition);
        const cocos2d::Vec2 breederPosition = breeder->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        breeder->setPosition(breederPosition);

        const cocos2d::Vec2 buttonPosition = startButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        startButton->setPosition(buttonPosition);
        const cocos2d::Vec2 buttonPosition2 = startButton2->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        startButton2->setPosition(buttonPosition2);

        // ��������λ��
        for (auto tree : trees) {
            const cocos2d::Vec2 newTreePos = tree->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            tree->setPosition(newTreePos);  // ����������λ��
        }
    }
}
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
