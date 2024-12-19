#include "Toolbar.h"
#include "Player.h"
#include "Tools.h"
extern Player* mainPlayer;

bool Toolbar::init() {
    if (!Layer::init()) {
        return false;
    }
    //工具框背景
    Tools tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto ToolbarPos=cocos2d::Vec2(visibleSize.width/2, visibleSize.height / 2-250);
    auto LatticePhoto=tool.addImageToScene("photo/tools/lattice.png", ToolbarPos, 0.9f);
    auto ToolbarPhoto = tool.addImageToScene("photo/tools/LG.png", cocos2d::Vec2(ToolbarPos.x-5, ToolbarPos.y-5), 2.0f);
    this->addChild(ToolbarPhoto,4);
    this->addChild(LatticePhoto, 5);

    // 创建工具按钮
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

    // 添加需要平移的图片
    markerSprite = tool.addImageToScene("photo/tools/redkuang.png",Pos,1.0f); 
    markerStartX = Pos.x;
    markerY = Pos.y;
    this->addChild(markerSprite, 7);

    // 注册鼠标滚轮事件
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseScroll = CC_CALLBACK_1(Toolbar::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

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
