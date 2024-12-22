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
    if (/*!Interacted && */(tileX >= -groundLayer->getLayerSize().width && tileX < groundLayer->getLayerSize().width &&
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
    ItemStorage& storage = ItemStorage::getInstance();

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

    // ����ʵ�ʵ���Ƭ���꣬ƫ������Ҫ��ȥ
    int adjustedX = tileX - offsetX;
    int adjustedY = tileY - offsetY;

    // ȷ���������Ч��Χ��
<<<<<<< Updated upstream
    if (adjustedX >= 0 && adjustedX < groundLayer->getLayerSize().width &&
        adjustedY >= 0 && adjustedY < groundLayer->getLayerSize().height) {
=======
    if (tileX - offsetX >= -groundLayer->getLayerSize().width && tileX - offsetX < groundLayer->getLayerSize().width &&
        tileY - offsetY >= 0 && tileY - offsetY < groundLayer->getLayerSize().height) {
>>>>>>> Stashed changes

        // ��ȡ���λ�õ�״̬
        int adjustedX = tileX - offsetX;
        int adjustedY = tileY - offsetY;
        const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
        // ��������
        if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT&&mainPlayer->Heldtool == 1 && !tilledLand[adjustedY][adjustedX]) {
            TilledLand::tillLand(tileX, tileY, Farmmap, tilledLand);
        }
        // ��ֲ����
        else if (mainPlayer->Heldseed > 0) {
            const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT) {
                // ������Ҽ����
                Crop* crop = plantedCrops[adjustedY][adjustedX];
                if (tilledLand[adjustedY][adjustedX] && plantedCrops[adjustedY][adjustedX] == nullptr) {
                    // ������ֲ����
                    Crop::plantSeed(tileX, tileY, Farmmap, plantedCrops, mainPlayer->Heldseed);
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
                }

            }
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->Heldtool == 3 && plantedCrops[adjustedY][adjustedX] != nullptr && !plantedCrops[adjustedY][adjustedX]->isMature()) {
                plantedCrops[adjustedY][adjustedX]->water();
                WateredLand::waterLand(tileX, tileY, Farmmap, wateredLand);
            }
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->Heldtool == 1 && plantedCrops[adjustedY][adjustedX] != nullptr && plantedCrops[adjustedY][adjustedX]->isMature()) {

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
            if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT && mainPlayer->Heldtool == 1 && plantedCrops[adjustedY][adjustedX] != nullptr && plantedCrops[adjustedY][adjustedX]->isDead()) {
                plantedCrops[adjustedY][adjustedX]->removeFromParent();
                plantedCrops[adjustedY][adjustedX] = nullptr;
            }
        }
    }
}


void FarmScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // ��ǰ��ʼ�����ڱ���
    int currentDay = 15;   // ���赱ǰ������15
    int currentMonth = 12; // ���赱ǰ�·���12��
    int currentYear = 2024;
    CalendarPanel* calendarPanel = CalendarPanel::create(currentDay, currentMonth, currentYear);

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
    case cocos2d::EventKeyboard::KeyCode::KEY_E: // ��e�򿪻�رղ˵�
        if (menuLayer) {
            menuLayer->toggleVisibility();
        }
        isMenuActive = !isMenuActive;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_F: // ��F������
        // ��������ʾ�������
        
        this->addChild(calendarPanel);
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
    if (!isColliding(newPlayerPos) && !isColliding2(newPlayerPos)) {
        // ���û������Χǽ���������λ��
         // ���û������Χǽ���������λ��
        const cocos2d::Vec2 newPos = Farmmap->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        Farmmap->setPosition(newPos);
        //NPC
        const cocos2d::Vec2 farmerPosition = farmer->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        farmer->setPosition(farmerPosition);
        const cocos2d::Vec2 fishermanPosition = fisherman->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        fisherman->setPosition(fishermanPosition);
        const cocos2d::Vec2 breederPosition = breeder->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        breeder->setPosition(breederPosition);
        //��ť
        const cocos2d::Vec2 buttonPosition = startButton->getPosition() + cocos2d::Vec2(deltaX, deltaY);
        startButton->setPosition(buttonPosition);

        // ��������λ��
        for (auto tree : trees) {
            const cocos2d::Vec2 newTreePos = tree->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            tree->setPosition(newTreePos);  // ����������λ��
        }
        //����
        for (auto mine : mines) {
            const cocos2d::Vec2 newMinePos = mine->getPosition() + cocos2d::Vec2(deltaX, deltaY);
            mine->setPosition(newMinePos);  // ����������λ��
        }
        //����
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
    Clock* clock = Clock::getInstance();
    clock->onGameTimeReset([this]() {
       
        // ���� resetAllCrops
        this->resetAllCrops();

        // ���� resetAllCrops ����
        this->setEnabledForReset(false);


        // �����������������
        this->scheduleOnce([this](float) {
            this->setEnabledForReset(true);
            }, 10.0f, "EnableReset");
        });
}

void FarmScene::resetAllCrops() {
    if (!canResetCrops) {
        return; // �����ǰ���ã�ֱ�ӷ���
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

bool FarmScene::isColliding2(const cocos2d::Vec2& newPos) {
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
    const int layerWidth = wallLayer2->getLayerSize().width;
    const int layerHeight = wallLayer2->getLayerSize().height;

    for (int x = 0; x < layerWidth; ++x) {
        for (int y = 0; y < layerHeight; ++y) {
            const auto tile = wallLayer2->getTileAt(cocos2d::Vec2(x, y));

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

