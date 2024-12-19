#include "Toolbar.h"
#include "Player.h"
#include "Tools.h"
extern Player* mainPlayer;

bool Toolbar::init() {
    if (!Layer::init()) {
        return false;
    }
    //���߿򱳾�
    Tools tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto ToolbarPos=cocos2d::Vec2(visibleSize.width/2, visibleSize.height / 2-250);
    auto LatticePhoto=tool.addImageToScene("photo/tools/lattice.png", ToolbarPos, 0.9f);
    auto ToolbarPhoto = tool.addImageToScene("photo/tools/LG.png", cocos2d::Vec2(ToolbarPos.x-5, ToolbarPos.y-5), 2.0f);
    this->addChild(ToolbarPhoto,4);
    this->addChild(LatticePhoto, 5);

    // �������߰�ť
    auto Pos = cocos2d::Vec2(ToolbarPos.x-143, ToolbarPos.y);
    auto Axe=tool.addImageToScene("photo/tools/Axe_1.png", Pos, 2.5f);
    this-> addChild(Axe,5);
    auto Hoe = tool.addImageToScene("photo/tools/Hoe_1.png", cocos2d::Vec2(Pos.x+57,Pos.y), 2.5f);
    this->addChild(Hoe,5);
    auto Watering_Can = tool.addImageToScene("photo/tools/Wateringcan_1.png", cocos2d::Vec2(Pos.x + 57*2, Pos.y), 2.5f);
    this->addChild(Watering_Can,5);
    auto Pickaxe = tool.addImageToScene("photo/tools/Pickaxe_1.png", cocos2d::Vec2(Pos.x + 57 * 3, Pos.y), 2.5f);
    this->addChild(Pickaxe,5);
    auto Sickle = tool.addImageToScene("photo/tools/Sickle_1.png", cocos2d::Vec2(Pos.x + 57 * 4, Pos.y), 2.5f);
    this->addChild(Sickle,5);
    auto Fish = tool.addImageToScene("photo/tools/Fish_1.png", cocos2d::Vec2(Pos.x + 57 * 5, Pos.y), 2.5f);
    this->addChild(Fish,5);

    // �����Ҫƽ�Ƶ�ͼƬ
    markerSprite = tool.addImageToScene("photo/tools/redkuang.png",Pos,1.0f); 
    markerStartX = Pos.x;
    markerY = Pos.y;
    this->addChild(markerSprite, 7);

    // ע���������¼�
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseScroll = CC_CALLBACK_1(Toolbar::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Toolbar::onMouseScroll(cocos2d::Event* event) {
    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);

    if (mouseEvent->getScrollY() > 0) {
        // �������ϣ��л�����һ������
        currentToolIndex = (currentToolIndex % 6) + 1;
    }
    else if (mouseEvent->getScrollY() < 0) {
        // �������£��л�����һ������
        currentToolIndex = (currentToolIndex - 2 + 6) % 6 + 1;
    }

    updateMarkerPosition();  // ������ͼƬ��λ��
}

void Toolbar::updateMarkerPosition() {
    // ÿ�ι����������£�x �������� 10
    float newX = markerStartX + (currentToolIndex - 1) * 57;

    // ������ͼƬ��λ��
    if (markerSprite) {
        markerSprite->setPositionX(newX);
    }

    // ������ҳ��еĹ���
    if (mainPlayer) {
        mainPlayer->setHeldTool(currentToolIndex);
        cocos2d::log("Current tool: %d, Marker X: %.2f", currentToolIndex, newX);
    }
}
