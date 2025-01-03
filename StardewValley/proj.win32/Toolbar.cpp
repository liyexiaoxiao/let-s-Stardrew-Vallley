#include "Toolbar.h"
#include "Player.h"
#include "Tools.h"
extern Player* mainPlayer;

Toolbar* Toolbar::instance = nullptr;
bool Toolbar::init() {
    if (!Layer::init()) {
        return false;
    }
    //工具框背景
    Tools tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto ToolbarPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300);
    auto LatticePhoto = tool.addImageToScene("photo/tools/lattice.png", ToolbarPos, 0.9f);
    auto ToolbarPhoto = tool.addImageToScene("photo/tools/LG.png", cocos2d::Vec2(ToolbarPos.x - 5, ToolbarPos.y - 5), 2.0f);
    this->addChild(ToolbarPhoto, 4);
    this->addChild(LatticePhoto, 5);

    // 创建工具
    auto Pos = cocos2d::Vec2(ToolbarPos.x - 143, ToolbarPos.y);
    Axe = tool.addImageToScene("photo/tools/Axe_1.png", Pos, 2.5f);
    this->addChild(Axe, 5);
    Hoe = tool.addImageToScene("photo/tools/Hoe_1.png", cocos2d::Vec2(Pos.x + 57, Pos.y), 2.5f);
    this->addChild(Hoe, 5);
    Watering_Can = tool.addImageToScene("photo/tools/Wateringcan_1.png", cocos2d::Vec2(Pos.x + 57 * 2, Pos.y), 2.5f);
    this->addChild(Watering_Can, 5);
    Pickaxe = tool.addImageToScene("photo/tools/Pickaxe_1.png", cocos2d::Vec2(Pos.x + 57 * 3, Pos.y), 2.5f);
    this->addChild(Pickaxe, 5);
    Sickle = tool.addImageToScene("photo/tools/Sickle_1.png", cocos2d::Vec2(Pos.x + 57 * 4, Pos.y), 2.5f);
    this->addChild(Sickle, 5);
    Fish = tool.addImageToScene("photo/tools/Fish_1.png", cocos2d::Vec2(Pos.x + 57 * 5, Pos.y), 2.5f);
    this->addChild(Fish, 5);

    // 添加需要平移的图片
    markerSprite = tool.addImageToScene("photo/tools/redkuang.png", Pos, 1.0f);
    markerStartX = Pos.x;
    markerY = Pos.y;
    this->addChild(markerSprite, 7);

    //种子包
    auto SeedBagGround = tool.addImageToScene("photo/tools/SeedGround.png", cocos2d::Vec2(ToolbarPos.x + 57 * 6, ToolbarPos.y), 0.35f);
    SeedButton = tool.createButton("photo/tools/seed_crop1.png", cocos2d::Vec2(ToolbarPos.x + 57 * 6, ToolbarPos.y), 1.0f);
    SeedButton->addClickEventListener([this](Ref* sender) {
        createSeedSelectionPanel();
        });
    this->addChild(SeedButton, 3);
    this->addChild(SeedBagGround, 2);

    //肥料选择红框
    auto feiliaoRedBox = tool.addImageToScene("photo/tools/redkuang.png", cocos2d::Vec2(ToolbarPos.x + 58 * 7, ToolbarPos.y), 1.0f);
    feiliaoRedBox->setVisible(false);
    this->addChild(feiliaoRedBox, 8);
    //肥料
    auto feiliaoGround = tool.addImageToScene("photo/tools/SeedGround.png", cocos2d::Vec2(ToolbarPos.x + 58 * 7, ToolbarPos.y), 0.35f);
    auto feiliaoButton = tool.createButton("photo/tools/feiliao.png", cocos2d::Vec2(ToolbarPos.x + 58 * 7, ToolbarPos.y), 2.7f);
    feiliaoButton->addClickEventListener([this, feiliaoRedBox](Ref* sender) {
        if (mainPlayer->if_holdfeiliao == 0) {
            // 如果当前没有持有肥料，显示红框
            feiliaoRedBox->setVisible(true);
            mainPlayer->if_holdfeiliao = 1;
        }
        else {
            // 如果当前已经持有肥料，隐藏红框
            feiliaoRedBox->setVisible(false);
            mainPlayer->if_holdfeiliao = 0;
        }
        });
    this->addChild(feiliaoButton, 3);
    this->addChild(feiliaoGround, 2);

    // 注册鼠标滚轮事件
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseScroll = CC_CALLBACK_1(Toolbar::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
// 鼠标滚轮事件处理函数
void Toolbar::onMouseScroll(cocos2d::Event* event) {
    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);

    if (mouseEvent->getScrollY() > 0) {
        // 滚轮向上，切换到下一个工具
        currentToolIndex = (currentToolIndex % 6) + 1;
    }
    else if (mouseEvent->getScrollY() < 0) {
        // 滚轮向下，切换到上一个工具
        currentToolIndex = (currentToolIndex - 2 + 6) % 6 + 1;
    }

    updateMarkerPosition();  // 更新新图片的位置
}
//更新工具及红框图片
void Toolbar::updateMarkerPosition() {
    // 每次工具索引更新，x 坐标增加 10
    float newX = markerStartX + (currentToolIndex - 1) * 57;

    // 更新新图片的位置
    if (markerSprite) {
        markerSprite->setPositionX(newX);
    }

    // 更新玩家持有的工具
    if (mainPlayer) {
        mainPlayer->setHeldTool(currentToolIndex);
        cocos2d::log("Current tool: %d, Marker X: %.2f", currentToolIndex, newX);
    }
}
// 更新工具的图标
void Toolbar::updateToolIcons() {
    // 判断主玩家的等级，更新工具图标
    int agricultureLevel = mainPlayer->agricultureLevel; // 获取玩家的农业等级
    int miningLevel = mainPlayer->miningLevel;
    int fishingLevel = mainPlayer->fishingLevel;
    int cookingLevel = mainPlayer->cookingLevel;
    // 根据农业等级更新图标
    if (agricultureLevel == 1) {
        // 更新图标为1级图标
        Axe->setTexture("photo/tools/Axe_1.png");
        Hoe->setTexture("photo/tools/Hoe_1.png");
        Watering_Can->setTexture("photo/tools/Wateringcan_1.png");
    }
    else if (agricultureLevel == 2) {
        // 更新图标为2级图标
        Axe->setTexture("photo/tools/Axe_2.png");
        Hoe->setTexture("photo/tools/Hoe_2.png");
        Watering_Can->setTexture("photo/tools/Wateringcan_2.png");
    }
    else if (agricultureLevel == 3) {
        // 更新图标为3级图标
        Axe->setTexture("photo/tools/Axe_3.png");
        Hoe->setTexture("photo/tools/Hoe_3.png");
        Watering_Can->setTexture("photo/tools/Wateringcan_3.png");
    }
    else if (agricultureLevel == 4) {
        // 更新图标为4级图标
        Axe->setTexture("photo/tools/Axe_4.png");
        Hoe->setTexture("photo/tools/Hoe_4.png");
        Watering_Can->setTexture("photo/tools/Wateringcan_4.png");
    }
    // 根据挖矿等级更新图标
    if (miningLevel == 1) {
        Pickaxe->setTexture("photo/tools/pickaxe_1.png");
    }
    else if (miningLevel == 2) {
        Pickaxe->setTexture("photo/tools/pickaxe_2.png");
    }
    else if (miningLevel == 3) {
        Pickaxe->setTexture("photo/tools/pickaxe_3.png");
    }
    else if (miningLevel == 4) {
        Pickaxe->setTexture("photo/tools/pickaxe_4.png");
    }
    // 根据钓鱼等级更新图标
    if (fishingLevel == 1) {
        Fish->setTexture("photo/tools/fish_1.png");
    }
    else if (fishingLevel == 2) {
        Fish->setTexture("photo/tools/fish_2.png");
    }
    else if (fishingLevel == 3) {
        Fish->setTexture("photo/tools/fish_3.png");
    }
    else if (fishingLevel == 4) {
        Fish->setTexture("photo/tools/fish_4.png");
    }
}
// 弹出种子选择面板
void Toolbar::createSeedSelectionPanel() {
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // 创建一个面板
    Tools Tool;
    auto panel = cocos2d::Layer::create();
    this->addChild(panel, 10);
    panel->setName("SeedSelectionPanel");

    //放置底部背景
    auto MenuBG = Tool.addImageToScene("photo/tools/LG.png", cocos2d::Vec2(visibleSize.width / 2 + 350, visibleSize.height / 2 - 300), 1.5f);
    panel->addChild(MenuBG, 11);

    auto Seed1_Pos = cocos2d::Vec2(visibleSize.width / 2 + 250, visibleSize.height / 2 - 300);
    auto Seed1_Button = Tool.createButton("photo/tools/seed_crop1.png", Seed1_Pos, 0.8f);
    Seed1_Button->addClickEventListener([this](Ref* sender) {
        mainPlayer->setHeldSeed(1);
        onSeedSelected(sender, 1);
        });
    panel->addChild(Seed1_Button, 12);

    auto Seed2_Pos = cocos2d::Vec2(Seed1_Pos.x + 50, Seed1_Pos.y);
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

    //放置关闭按钮
    auto ok_Pos = cocos2d::Vec2(Seed4_Pos.x + 50, Seed3_Pos.y);
    auto ok_Button = Tool.createButton("photo/tools/ok_button.png", ok_Pos, 0.8f);
    ok_Button->addClickEventListener([this](Ref* sender) {
        closeSeedPanel(sender);  // 点击关闭面板
        });
    panel->addChild(ok_Button, 12);
}
// 选择种子后的处理
void Toolbar::onSeedSelected(cocos2d::Ref* sender, int seedType) {
    // 根据选择的种子类型改变SeedButton的图标
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

    // 关闭面板
    closeSeedPanel(nullptr);
}
// 关闭种子选择面板
void Toolbar::closeSeedPanel(cocos2d::Ref* sender) {
    // 移除面板
    this->removeChildByName("SeedSelectionPanel");
}