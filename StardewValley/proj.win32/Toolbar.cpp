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
    auto ToolbarPos=cocos2d::Vec2(visibleSize.width/2, visibleSize.height / 2-300);
    auto LatticePhoto=tool.addImageToScene("photo/tools/lattice.png", ToolbarPos, 0.9f);
    auto ToolbarPhoto = tool.addImageToScene("photo/tools/LG.png", cocos2d::Vec2(ToolbarPos.x-5, ToolbarPos.y-5), 2.0f);
    this->addChild(ToolbarPhoto,4);
    this->addChild(LatticePhoto, 5);

    // ��������
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

    //���Ӱ�
    auto SeedBagGround = tool.addImageToScene("photo/tools/SeedBagGround.png", cocos2d::Vec2(ToolbarPos.x + 57 * 6, ToolbarPos.y), 2.5f);
    SeedButton = tool.createButton("photo/tools/seed_crop1.png", cocos2d::Vec2(ToolbarPos.x + 57 * 6, ToolbarPos.y), 1.0f);
    SeedButton->addClickEventListener([this](Ref* sender) {
        createSeedSelectionPanel();
        });
    this->addChild(SeedButton, 3);
    this->addChild(SeedBagGround, 2);

    // ע���������¼�
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseScroll = CC_CALLBACK_1(Toolbar::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
// �������¼�������
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
//���¹��߼����ͼƬ
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
// ��������ѡ�����
void Toolbar::createSeedSelectionPanel() {
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // ����һ�����
    Tools Tool;
    auto panel = cocos2d::Layer::create();
    this->addChild(panel, 10);
    panel->setName("SeedSelectionPanel");

    //���õײ�����
    auto MenuBG = Tool.addImageToScene("photo/tools/LG.png", cocos2d::Vec2(visibleSize.width / 2 + 350, visibleSize.height / 2 - 300), 1.5f);
    panel->addChild(MenuBG,11);

    auto Seed1_Pos = cocos2d::Vec2(visibleSize.width / 2 + 250, visibleSize.height / 2 - 300);
    auto Seed1_Button = Tool.createButton("photo/tools/seed_crop1.png", Seed1_Pos, 0.8f);
    Seed1_Button->addClickEventListener([this](Ref* sender) {
        mainPlayer->setHeldSeed(1);
        onSeedSelected(sender, 1);
        });
    panel->addChild(Seed1_Button, 12);

    auto Seed2_Pos = cocos2d::Vec2(Seed1_Pos.x+50, Seed1_Pos.y);
    auto Seed2_Button = Tool.createButton("photo/tools/seed_crop2.png", Seed2_Pos, 0.8f);
    Seed2_Button->addClickEventListener([this](Ref* sender) {
        mainPlayer->setHeldSeed(2);
        onSeedSelected(sender, 2);
        });
    panel->addChild(Seed2_Button, 12);

    auto Seed3_Pos = cocos2d::Vec2(Seed2_Pos.x + 50, Seed2_Pos.y);
    auto Seed3_Button = Tool.createButton("photo/tools/seed_crop3.png", Seed3_Pos, 0.8f);
    Seed3_Button->addClickEventListener([this](Ref* sender) {
        mainPlayer->setHeldSeed(3);
        onSeedSelected(sender, 3);
        });
    panel->addChild(Seed3_Button, 12);

    auto Seed4_Pos = cocos2d::Vec2(Seed3_Pos.x + 50, Seed3_Pos.y);
    auto Seed4_Button = Tool.createButton("photo/tools/seed_crop4.png", Seed4_Pos, 0.8f);
    Seed4_Button->addClickEventListener([this](Ref* sender) {
        mainPlayer->setHeldSeed(4);
        onSeedSelected(sender, 4);
        });
    panel->addChild(Seed4_Button, 12);

    //���ùرհ�ť
    auto ok_Pos = cocos2d::Vec2(Seed4_Pos.x + 50, Seed3_Pos.y);
    auto ok_Button = Tool.createButton("photo/tools/ok_button.png", ok_Pos, 0.8f);
    ok_Button->addClickEventListener([this](Ref* sender) {
        closeSeedPanel(sender);  // ����ر����
        });
    panel->addChild(ok_Button, 12);
}
// ѡ�����Ӻ�Ĵ���
void Toolbar::onSeedSelected(cocos2d::Ref* sender, int seedType) {
    // ����ѡ����������͸ı�SeedButton��ͼ��
    switch (seedType) {
        case 1:
            SeedButton->loadTextureNormal("photo/tools/seed_crop1.png");
            break;
        case 2:
            SeedButton->loadTextureNormal("photo/tools/seed_crop2.png");
            break;
        case 3:
            SeedButton->loadTextureNormal("photo/tools/seed_crop3.png");
            break;
        case 4:
            SeedButton->loadTextureNormal("photo/tools/seed_crop4.png");
            break;
        default:
            break;
    }

    // �ر����
    closeSeedPanel(nullptr);
}

// �ر�����ѡ�����
void Toolbar::closeSeedPanel(cocos2d::Ref* sender) {
    // �Ƴ����
    this->removeChildByName("SeedSelectionPanel");
}
