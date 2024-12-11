#include "MenuLayer.h"
#include "ui/CocosGUI.h"
#include "Tools.h"
#include "Clock.h"

extern Player* mainPlayer;

MenuLayer::MenuLayer() : isVisible(false) {}

MenuLayer::~MenuLayer() {}

bool MenuLayer::init() {
    Tools Tool;
    if (!Layer::init()) {
        return false;
    }
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    //放置菜单背景
    std::string BGImage = "photo/ui/Menu.png";
    auto BGImagePos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
    MenuBG = Tool.addImageToScene(BGImage, BGImagePos, 2.0f);
    MenuBG->setLocalZOrder(1);
    this->addChild(MenuBG);


    //创建菜单上的四个按钮
    auto BGSize = MenuBG->getBoundingBox();
    auto BasicButtonPos = cocos2d::Vec2(BGSize.origin.x + 50, BGSize.origin.y + BGSize.size.height + 25);
    auto BasicButton = Tool.createButton("photo/ui/basic.png", BasicButtonPos, 3.2f);
    BasicButton->setLocalZOrder(2);
    BasicButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(1);  // 显示面板1
        });
    this->addChild(BasicButton);

    auto STButtonPos = cocos2d::Vec2(BasicButtonPos.x + 50, BasicButtonPos.y);
    auto STButton = Tool.createButton("photo/ui/storage.png", STButtonPos, 3.2f);
    STButton->setLocalZOrder(2);
    STButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(2);  // 显示面板2
        });
    this->addChild(STButton);

    auto SKButtonPos = cocos2d::Vec2(STButtonPos.x + 50, STButtonPos.y);
    auto SKButton = Tool.createButton("photo/ui/skill.png", SKButtonPos, 3.2f);
    SKButton->setLocalZOrder(2);
    SKButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(3);  // 显示面板3
        });
    this->addChild(SKButton);

    auto EXButtonPos = cocos2d::Vec2(SKButtonPos.x + 50, SKButtonPos.y);
    auto EXButton = Tool.createButton("photo/ui/exit.png", EXButtonPos, 3.2f);
    EXButton->setLocalZOrder(2);
    EXButton->addClickEventListener([this](Ref* sender) {
        this->showPanel(4);  // 显示面板4
        });
    this->addChild(EXButton);

    // 初始时菜单隐藏
    this->setVisible(isVisible);

    // 创建四个面板
    createPanels();

    return true;
}

void MenuLayer::createPanels() {
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 Middle = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
    // 创建面板1
    panel1 = createPanel(1);
    panel1->setPosition(Middle);
    this->addChild(panel1, 1);

    // 创建面板2
    panel2 = createPanel(2);
    panel2->setPosition(Middle);
    this->addChild(panel2, 1);

    // 创建面板3
    panel3 = createPanel(3);
    panel3->setPosition(Middle);
    this->addChild(panel3, 1);

    // 创建面板4
    panel4 = createPanel(4);
    panel4->setPosition(Middle);
    this->addChild(panel4, 1);

    // 默认隐藏其他面板,显示第一个面板
    panel1->setVisible(true);
    panel2->setVisible(false);
    panel3->setVisible(false);
    panel4->setVisible(false);
}

void MenuLayer::showPanel(int index) {
    // 隐藏所有面板
    panel1->setVisible(false);
    panel2->setVisible(false);
    panel3->setVisible(false);
    panel4->setVisible(false);

    // 根据索引显示相应的面板
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
    //// 添加背景图片
    //auto background = cocos2d::Sprite::create("photo/ui/Menu.png");
    //if (background) {
    //    background->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2)); // 背景居中
    //    this->addChild(background, 1);
    //}
    if (panelIndex == 1) {
        auto CharacterGroundPos = cocos2d::Vec2(visibleSize.width / 2-180, visibleSize.height / 2);
        auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterGroundPos, 1.1f);
        CharacterGround->setLocalZOrder(5);
        this->addChild(CharacterGround);
        cocos2d::Vec2 CharacterPos = CharacterGround->getPosition();
        auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterPos, 1.2f);
        PlayerPhoto->setLocalZOrder(5);
        this->addChild(PlayerPhoto);

        auto NameLabelPos = cocos2d::Vec2(CharacterPos.x, CharacterPos.y - 130);
        auto NameLabel = Tool.createLabel(mainPlayer->PlayerName, "fonts/Marker Felt.ttf", 32, NameLabelPos);
        NameLabel->setLocalZOrder(5);
        this->addChild(NameLabel);

        auto FarmLabelPos = cocos2d::Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 + 100);
        auto FarmLabel = Tool.createLabel(mainPlayer->FarmName, "fonts/Marker Felt.ttf", 32, FarmLabelPos);
        FarmLabel->setLocalZOrder(5);
        this->addChild(FarmLabel);

        auto MoneyLabelPos = cocos2d::Vec2(FarmLabelPos.x, FarmLabelPos.y - 80);
        std::string label_1 = "Money you have:";
        std::string AllMoneyLabel = label_1 + std::to_string(mainPlayer->getMoney());
        auto MoneyLabel = Tool.createLabel(AllMoneyLabel, "fonts/Marker Felt.ttf", 32, MoneyLabelPos);
        MoneyLabel->setLocalZOrder(5);
        this->addChild(MoneyLabel);

        std::string seasonshow = clock->getSeason();
        std::string AllTimeLabel = "year: " + std::to_string(clock->getYear())  + " day: " + std::to_string(clock->getDay()) + " " + seasonshow;
        auto TimeLabelPos = cocos2d::Vec2(MoneyLabelPos.x, MoneyLabelPos.y - 80);
        auto TimeLabel = Tool.createLabel(AllTimeLabel, "fonts/Marker Felt.ttf", 32, TimeLabelPos);
        TimeLabel->setLocalZOrder(5);
        this->addChild(TimeLabel);
    }
    else if (panelIndex == 2) {

    }
    else if (panelIndex == 3) {

    }
    else if (panelIndex == 4) {

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
    this->setVisible(isVisible);  // 根据当前状态设置菜单显示或隐藏
}