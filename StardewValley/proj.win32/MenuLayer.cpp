#include "MenuLayer.h"
#include "ui/CocosGUI.h"
#include "Tools.h"
#include "Clock.h"
#include "StartupScene.h"
#include "ItemStorage.h"

extern Player* mainPlayer;

MenuLayer::MenuLayer() : isVisible(false) {}

MenuLayer::~MenuLayer() {}

bool MenuLayer::init() {
    Tools Tool;
    if (!Layer::init()) {
        return false;
    }
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    //���ò˵�����
    std::string BGImage = "photo/ui/Menu.png";
    auto BGImagePos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
    MenuBG = Tool.addImageToScene(BGImage, BGImagePos, 2.0f);
    MenuBG->setLocalZOrder(1);
    this->addChild(MenuBG);


    //�����˵��ϵ��ĸ���ť
    auto BGSize = MenuBG->getBoundingBox();
    auto BasicButtonPos = cocos2d::Vec2(BGSize.origin.x + 50, BGSize.origin.y + BGSize.size.height + 25);
    auto BasicButton = Tool.createButton("photo/ui/basic.png", BasicButtonPos, 3.2f);
    BasicButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(1);  // ��ʾ���1
        });
    this->addChild(BasicButton,2);

    auto STButtonPos = cocos2d::Vec2(BasicButtonPos.x + 50, BasicButtonPos.y);
    auto STButton = Tool.createButton("photo/ui/storage.png", STButtonPos, 3.2f);
    STButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(2);  // ��ʾ���2
        });
    this->addChild(STButton,2);

    auto SKButtonPos = cocos2d::Vec2(STButtonPos.x + 50, STButtonPos.y);
    auto SKButton = Tool.createButton("photo/ui/skill.png", SKButtonPos, 0.8f);
    SKButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(3);  // ��ʾ���3
        });
    this->addChild(SKButton,2);

    auto EXButtonPos = cocos2d::Vec2(SKButtonPos.x + 50, SKButtonPos.y);
    auto EXButton = Tool.createButton("photo/ui/exit.png", EXButtonPos, 3.2f);
    EXButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(4);  // ��ʾ���4
        });
    this->addChild(EXButton,2);

    // ��ʼʱ�˵�����
    this->setVisible(isVisible);

    // �����ĸ����
    createPanels();
    return true;
}
//�����������
void MenuLayer::createPanels() {
    // �������1
    panel1 = createPanel(1);
    this->addChild(panel1, 1);
    panel1->setVisible(true);//���1����Ĭ����ʾ
    // �������2
    panel2 = createPanel(2);
    this->addChild(panel2, 1);
    panel2->setVisible(false);
    // �������3
    panel3 = createPanel(3);
    this->addChild(panel3, 1);
    panel3->setVisible(false);
    // �������4
    panel4 = createPanel(4);
    this->addChild(panel4, 1);
    panel4->setVisible(false);

}
//չʾָ�����
void MenuLayer::showPanel(int index) {
    // �����������
    panel1->setVisible(false);
    panel2->setVisible(false);
    panel3->setVisible(false);
    panel4->setVisible(false);

    if (index == 1) {
        this->removeChild(panel1);
        panel1 = nullptr;
    }
    else if (index == 2) {
        this->removeChild(panel2);
        panel2 = nullptr;
    }
    else if (index == 3) {
        this->removeChild(panel3);
        panel3 = nullptr;
    }
    else if (index == 4) {
        this->removeChild(panel4);
        panel4 = nullptr;
    }

    // ���´�����Ӧ�����
    if (index == 1) {
        panel1 = createPanel(1);  // �����������1
        this->addChild(panel1,2);
        panel1->setVisible(true);
    }
    else if (index == 2) {
        panel2 = createPanel(2);  // �����������2
        this->addChild(panel2,2);
        panel2->setVisible(true);
    }
    else if (index == 3) {
        panel3 = createPanel(3);  // �����������3
        this->addChild(panel3,2);
        panel3->setVisible(true);
    }
    else if (index == 4) {
        panel4 = createPanel(4);  // �����������4
        this->addChild(panel4,2);
        panel4->setVisible(true);
    }
}
//�����������
cocos2d::Layer* MenuLayer::createPanel(int panelIndex) {
    Tools Tool;
    auto panel = cocos2d::Layer::create();
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    Clock* clock = Clock::getInstance();

    if (panelIndex == 1) {
        //�����ұ���������
        auto CharacterGroundPos = cocos2d::Vec2(visibleSize.width / 2 - 180, visibleSize.height / 2);
        auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterGroundPos, 1.1f);
        panel->addChild(CharacterGround, 5);
        cocos2d::Vec2 CharacterPos = CharacterGround->getPosition();
        auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterPos, 1.2f);
        panel->addChild(PlayerPhoto, 5);
        //����������
        auto NameLabelPos = cocos2d::Vec2(CharacterPos.x, CharacterPos.y - 130);
        auto NameLabel = Tool.createLabel(mainPlayer->PlayerName, "fonts/Marker Felt.ttf", 32, NameLabelPos);
        panel->addChild(NameLabel, 5);
        //���ũ������
        auto FarmLabelPos = cocos2d::Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 + 100);
        auto FarmLabel = Tool.createLabel(mainPlayer->FarmName, "fonts/Marker Felt.ttf", 32, FarmLabelPos);
        panel->addChild(FarmLabel, 5);
        //���Ǯ
        auto MoneyLabelPos = cocos2d::Vec2(FarmLabelPos.x, FarmLabelPos.y - 80);
        std::string label_1 = "Money you have:";
        std::string AllMoneyLabel = label_1 + std::to_string(mainPlayer->getMoney());
        auto MoneyLabel = Tool.createLabel(AllMoneyLabel, "fonts/Marker Felt.ttf", 32, MoneyLabelPos);
        panel->addChild(MoneyLabel, 5);
        //���ʱ��
        std::string seasonshow = clock->getSeason();
        std::string AllTimeLabel = "year: " + std::to_string(clock->getYear()) + " day: " + std::to_string(clock->getDay()) + " " + seasonshow;
        auto TimeLabelPos = cocos2d::Vec2(MoneyLabelPos.x, MoneyLabelPos.y - 80);
        auto TimeLabel = Tool.createLabel(AllTimeLabel, "fonts/Marker Felt.ttf", 32, TimeLabelPos);
        panel->addChild(TimeLabel, 5);
    }
    else if (panelIndex == 2) {
        auto stolatticePos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 120);
        for (int i = 0; i < 5; i++) {
            auto stolattice = Tool.addImageToScene("photo/storage/StorageLattice.png", cocos2d::Vec2(stolatticePos.x, stolatticePos.y - 60 * i), 0.9f);
            panel->addChild(stolattice, 5);
        }
        showStorage(panel);
    }
    else if (panelIndex == 3) {
        //�����ұ���������
        auto CharacterGroundPos = cocos2d::Vec2(visibleSize.width / 2 - 220, visibleSize.height / 2);
        auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterGroundPos, 1.1f);
        panel->addChild(CharacterGround, 5);
        cocos2d::Vec2 CharacterPos = CharacterGround->getPosition();
        auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterPos, 1.2f);
        panel->addChild(PlayerPhoto, 5);
        //����������
        auto NameLabelPos = cocos2d::Vec2(CharacterPos.x, CharacterPos.y - 130);
        auto NameLabel = Tool.createLabel(mainPlayer->PlayerName, "fonts/Marker Felt.ttf", 32, NameLabelPos);
        panel->addChild(NameLabel, 5);
        //��Ӽ�����
        //ũҵ
        auto ALabelPos = cocos2d::Vec2(visibleSize.width / 2 + 40, visibleSize.height / 2 + 80);
        auto ALabel = Tool.createLabel("Agriculture", "fonts/Marker Felt.ttf", 32, ALabelPos);
        panel->addChild(ALabel, 5);
        auto APhotoPos = cocos2d::Vec2(ALabelPos.x - 90, ALabelPos.y);
        auto APhoto = Tool.addImageToScene("photo/ui/skill_agriculture.png", APhotoPos, 4.5f);
        panel->addChild(APhoto, 5);
        //�ڿ�
        auto MLabelPos = cocos2d::Vec2(ALabelPos.x, ALabelPos.y - 50);
        auto MLabel = Tool.createLabel("Mining", "fonts/Marker Felt.ttf", 32, MLabelPos);
        panel->addChild(MLabel, 5);
        auto MPhotoPos = cocos2d::Vec2(APhotoPos.x, APhotoPos.y - 50);
        auto MPhoto = Tool.addImageToScene("photo/ui/skill_mining.png", MPhotoPos, 4.5f);
        panel->addChild(MPhoto, 5);
        //����
        auto FLabelPos = cocos2d::Vec2(MLabelPos.x, MLabelPos.y - 50);
        auto FLabel = Tool.createLabel("Fishing", "fonts/Marker Felt.ttf", 32, FLabelPos);
        panel->addChild(FLabel, 5);
        auto FPhotoPos = cocos2d::Vec2(MPhotoPos.x, MPhotoPos.y - 50);
        auto FPhoto = Tool.addImageToScene("photo/ui/skill_fishing.png", FPhotoPos, 4.5f);
        panel->addChild(FPhoto, 5);
        //���
        auto CLabelPos = cocos2d::Vec2(FLabelPos.x, FLabelPos.y - 50);
        auto CLabel = Tool.createLabel("Cooking", "fonts/Marker Felt.ttf", 32, CLabelPos);
        panel->addChild(CLabel, 5);
        auto CPhotoPos = cocos2d::Vec2(FPhotoPos.x, FPhotoPos.y - 70);
        auto CPhoto = Tool.addImageToScene("photo/ui/skill_cooking.png", CPhotoPos, 3.8f);
        panel->addChild(CPhoto, 5);

        auto ALevelPos = cocos2d::Vec2(ALabelPos.x + 100, ALabelPos.y);
        auto MLevelPos = cocos2d::Vec2(ALevelPos.x, ALevelPos.y - 50);
        auto FLevelPos = cocos2d::Vec2(MLevelPos.x, MLevelPos.y - 50);
        auto CLevelPos = cocos2d::Vec2(FLevelPos.x, FLevelPos.y - 50);
        for (int i = 0; i < mainPlayer->agricultureLevel; i++) {
            auto currentPos = cocos2d::Vec2(ALevelPos.x + i * 30, ALevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
        for (int i = 0; i < mainPlayer->miningLevel; i++) {
            auto currentPos = cocos2d::Vec2(MLevelPos.x + i * 30, MLevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
        for (int i = 0; i < mainPlayer->fishingLevel; i++) {
            auto currentPos = cocos2d::Vec2(FLevelPos.x + i * 30, FLevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
        for (int i = 0; i < mainPlayer->cookingLevel; i++) {
            auto currentPos = cocos2d::Vec2(CLevelPos.x + i * 30, CLevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
    }
    else if (panelIndex == 4) {
        //��������ʼ����
        auto BacktoStart = Tool.createButton("photo/ui/back_1.png", cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50), 0.8);
        BacktoStart->addClickEventListener([=](Ref* sender) {
            // �л�����Ϸ����
            auto transition = cocos2d::TransitionFade::create(1.0f, StartupScene::create(), cocos2d::Color3B::WHITE);
            cocos2d::Director::getInstance()->replaceScene(transition);
            });
        BacktoStart->setLocalZOrder(5);
        panel->addChild(BacktoStart);
        //�˳���Ϸ
        auto ExitButton = Tool.createButton("photo/ui/back_2.png", cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50), 0.8);
        ExitButton->addClickEventListener([=](Ref* sender) {
            //�˳�
            cocos2d::Director::getInstance()->end();
            });
        ExitButton->setLocalZOrder(5);
        panel->addChild(ExitButton);
    }
    return panel;
}

MenuLayer* MenuLayer::create() {
    MenuLayer* layer = new MenuLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

void MenuLayer::toggleVisibility() {
    isVisible = !isVisible;
    this->setVisible(isVisible);  // ���ݵ�ǰ״̬���ò˵���ʾ������
}

void MenuLayer::showStorage(Layer* panel) {
    Tools Tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto Ref_Pos = cocos2d::Vec2(visibleSize.width / 2 - 320, visibleSize.height / 2 + 120);

    ItemStorage& storage = ItemStorage::getInstance();
    //ѭ�������洢��Ʒ���������飬�����Ʒ������Ϊ0���������Ʒͼ��
    for (int i = 0; i < static_cast<int>(StorageID::MAX_STORAGE_ID); i++) {
        if (storage.getItemQuantity(i)) {
            int newX = Ref_Pos.x + i % 12 * 58;
            int newY = Ref_Pos.y - i / 12 * 58;
            std::string photopath = storage.getItemIconPath(i);
            if (photopath != "") {
                auto itemIcon = Tool.addImageToScene(photopath, cocos2d::Vec2(newX, newY), 2.8f);
                panel->addChild(itemIcon, 5);
            }
            auto itemLabel = Tool.createLabel(std::to_string(storage.getItemQuantity(i)), "fonts/Marker Felt.ttf", 20, cocos2d::Vec2(newX + 25, newY - 25));
            panel->addChild(itemLabel, 5);
        }
    }
}