#include "MenuLayer.h"
#include "ui/CocosGUI.h"
#include "Tools.h"
#include "Clock.h"
#include "StartupScene.h"
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
    BasicButton->setLocalZOrder(2);
    BasicButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(1);  // ��ʾ���1
        });
    this->addChild(BasicButton);

    auto STButtonPos = cocos2d::Vec2(BasicButtonPos.x + 50, BasicButtonPos.y);
    auto STButton = Tool.createButton("photo/ui/storage.png", STButtonPos, 3.2f);
    STButton->setLocalZOrder(2);
    STButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(2);  // ��ʾ���2
        });
    this->addChild(STButton);

    auto SKButtonPos = cocos2d::Vec2(STButtonPos.x + 50, STButtonPos.y);
    auto SKButton = Tool.createButton("photo/ui/skill.png", SKButtonPos, 0.8f);
    SKButton->setLocalZOrder(2);
    SKButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(3);  // ��ʾ���3
        });
    this->addChild(SKButton);

    auto EXButtonPos = cocos2d::Vec2(SKButtonPos.x + 50, SKButtonPos.y);
    auto EXButton = Tool.createButton("photo/ui/exit.png", EXButtonPos, 3.2f);
    EXButton->setLocalZOrder(2);
    EXButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(4);  // ��ʾ���4
        });
    this->addChild(EXButton);

    // ��ʼʱ�˵�����
    this->setVisible(isVisible);

    // �����ĸ����
    createPanels();
    return true;
}

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

void MenuLayer::showPanel(int index) {
    // �����������
    panel1->setVisible(false);
    panel2->setVisible(false);
    panel3->setVisible(false);
    panel4->setVisible(false);

    // ����������ʾ��Ӧ�����
    if (index == 1) {
        panel1->setVisible(true);
    }
    else if (index == 2) {
        panel2->setVisible(true);
    }
    else if (index == 3) {
        panel3->setVisible(true);
    }
    else if (index == 4) {
        panel4->setVisible(true);
    }
}

cocos2d::Layer* MenuLayer::createPanel(int panelIndex) {
    Tools Tool;
    auto panel = cocos2d::Layer::create();
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    Clock* clock = Clock::getInstance();
    //// ��ӱ���ͼƬ
    //auto background = cocos2d::Sprite::create("photo/ui/Menu.png");
    //if (background) {
    //    background->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2)); // ��������
    //    this->addChild(background, 1);
    //}
    if (panelIndex == 1) {
        //�����ұ���������
        auto CharacterGroundPos = cocos2d::Vec2(visibleSize.width / 2-180, visibleSize.height / 2);
        auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterGroundPos, 1.1f);
        CharacterGround->setLocalZOrder(5);
        panel->addChild(CharacterGround);
        cocos2d::Vec2 CharacterPos = CharacterGround->getPosition();
        auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterPos, 1.2f);
        PlayerPhoto->setLocalZOrder(5);
        panel->addChild(PlayerPhoto);
        //����������
        auto NameLabelPos = cocos2d::Vec2(CharacterPos.x, CharacterPos.y - 130);
        auto NameLabel = Tool.createLabel(mainPlayer->PlayerName, "fonts/Marker Felt.ttf", 32, NameLabelPos);
        NameLabel->setLocalZOrder(5);
        panel->addChild(NameLabel);
        //���ũ������
        auto FarmLabelPos = cocos2d::Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 + 100);
        auto FarmLabel = Tool.createLabel(mainPlayer->FarmName, "fonts/Marker Felt.ttf", 32, FarmLabelPos);
        FarmLabel->setLocalZOrder(5);
        panel->addChild(FarmLabel);
        //���Ǯ
        auto MoneyLabelPos = cocos2d::Vec2(FarmLabelPos.x, FarmLabelPos.y - 80);
        std::string label_1 = "Money you have:";
        std::string AllMoneyLabel = label_1 + std::to_string(mainPlayer->getMoney());
        auto MoneyLabel = Tool.createLabel(AllMoneyLabel, "fonts/Marker Felt.ttf", 32, MoneyLabelPos);
        MoneyLabel->setLocalZOrder(5);
        panel->addChild(MoneyLabel);
        //���ʱ��
        std::string seasonshow = clock->getSeason();
        std::string AllTimeLabel = "year: " + std::to_string(clock->getYear())  + " day: " + std::to_string(clock->getDay()) + " " + seasonshow;
        auto TimeLabelPos = cocos2d::Vec2(MoneyLabelPos.x, MoneyLabelPos.y - 80);
        auto TimeLabel = Tool.createLabel(AllTimeLabel, "fonts/Marker Felt.ttf", 32, TimeLabelPos);
        TimeLabel->setLocalZOrder(5);
        panel->addChild(TimeLabel);
    }
    else if (panelIndex == 2) {

    }
    else if (panelIndex == 3) {
        //�����ұ���������
        auto CharacterGroundPos = cocos2d::Vec2(visibleSize.width / 2 - 220, visibleSize.height / 2);
        auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterGroundPos, 1.1f);
        CharacterGround->setLocalZOrder(5);
        panel->addChild(CharacterGround);
        cocos2d::Vec2 CharacterPos = CharacterGround->getPosition();
        auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterPos, 1.2f);
        PlayerPhoto->setLocalZOrder(5);
        panel->addChild(PlayerPhoto);
        //����������
        auto NameLabelPos = cocos2d::Vec2(CharacterPos.x, CharacterPos.y - 130);
        auto NameLabel = Tool.createLabel(mainPlayer->PlayerName, "fonts/Marker Felt.ttf", 32, NameLabelPos);
        NameLabel->setLocalZOrder(5);
        panel->addChild(NameLabel);
        //��Ӽ�����
        //ũҵ
        auto ALabelPos = cocos2d::Vec2(visibleSize.width / 2+40, visibleSize.height / 2 + 80);
        auto ALabel = Tool.createLabel("Agriculture", "fonts/Marker Felt.ttf", 32, ALabelPos);
        ALabel->setLocalZOrder(5);
        panel->addChild(ALabel);
        auto APhotoPos = cocos2d::Vec2(ALabelPos.x-90, ALabelPos.y);
        auto APhoto = Tool.addImageToScene("photo/ui/skill_agriculture.png", APhotoPos, 4.5f);
        APhoto->setLocalZOrder(5);
        panel->addChild(APhoto);
        //�ڿ�
        auto MLabelPos = cocos2d::Vec2(ALabelPos.x, ALabelPos.y-50);
        auto MLabel = Tool.createLabel("Mining", "fonts/Marker Felt.ttf", 32, MLabelPos);
        MLabel->setLocalZOrder(5);
        panel->addChild(MLabel);
        auto MPhotoPos = cocos2d::Vec2(APhotoPos.x, APhotoPos.y-50);
        auto MPhoto = Tool.addImageToScene("photo/ui/skill_mining.png", MPhotoPos, 4.5f);
        MPhoto->setLocalZOrder(5);
        panel->addChild(MPhoto);
        //����
        auto FLabelPos = cocos2d::Vec2(MLabelPos.x, MLabelPos.y - 50);
        auto FLabel = Tool.createLabel("Fishing", "fonts/Marker Felt.ttf", 32, FLabelPos);
        FLabel->setLocalZOrder(5);
        panel->addChild(FLabel);
        auto FPhotoPos = cocos2d::Vec2(MPhotoPos.x, MPhotoPos.y - 50);
        auto FPhoto = Tool.addImageToScene("photo/ui/skill_fishing.png", FPhotoPos, 4.5f);
        FPhoto->setLocalZOrder(5);
        panel->addChild(FPhoto);
        //���
        auto CLabelPos = cocos2d::Vec2(FLabelPos.x, FLabelPos.y - 50);
        auto CLabel = Tool.createLabel("Cooking", "fonts/Marker Felt.ttf", 32, CLabelPos);
        CLabel->setLocalZOrder(5);
        panel->addChild(CLabel);
        auto CPhotoPos = cocos2d::Vec2(FPhotoPos.x, FPhotoPos.y - 70);
        auto CPhoto = Tool.addImageToScene("photo/ui/skill_cooking.png", CPhotoPos, 3.8f);
        CPhoto->setLocalZOrder(5);
        panel->addChild(CPhoto);

        auto ALevelPos = cocos2d::Vec2(ALabelPos.x+100, ALabelPos.y);
        auto MLevelPos = cocos2d::Vec2(ALevelPos.x, ALevelPos.y - 50);
        auto FLevelPos = cocos2d::Vec2(MLevelPos.x, MLevelPos.y - 50);
        auto CLevelPos = cocos2d::Vec2(FLevelPos.x, FLevelPos.y - 50);
        for (int i = 0; i < mainPlayer->agricultureLevel; i++) {
            auto currentPos = cocos2d::Vec2(ALevelPos.x + i * 10, ALevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
        for (int i = 0; i < mainPlayer->miningLevel; i++) {
            auto currentPos = cocos2d::Vec2(MLevelPos.x + i * 10, MLevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
        for (int i = 0; i < mainPlayer->fishingLevel; i++) {
            auto currentPos = cocos2d::Vec2(FLevelPos.x + i * 10, FLevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
        for (int i = 0; i < mainPlayer->cookingLevel; i++) {
            auto currentPos = cocos2d::Vec2(CLevelPos.x + i * 10, CLevelPos.y);
            auto point = Tool.addImageToScene("photo/ui/point.png", currentPos, 1.0f);
            point->setLocalZOrder(5);
            panel->addChild(point);
        }
    }
    else if (panelIndex == 4) {
        //��������ʼ����
        auto BacktoStart=Tool.createButton("photo/ui/back_1.png", cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50), 0.8);
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