//#include "Toolbar.h"
//#include "Player.h"
//extern Player* mainPlayer;
//
//bool Toolbar::init() {
//    if (!Layer::init()) {
//        return false;
//    }
//
//    // 创建工具栏容器
//    auto toolbarContainer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150), 640, 100);
//    toolbarContainer->setPosition(0, 0);  // 设置工具栏位置
//    this->addChild(toolbarContainer);
//
//    // 创建工具按钮
//    createToolButton("Axe", 50, 50, 0);    // 斧头
//    createToolButton("Hoe", 150, 50, 1);    // 锄头
//    createToolButton("Watering Can", 250, 50, 2);  // 洒水壶
//    createToolButton("Pickaxe", 350, 50, 3);  // 十字镐
//    createToolButton("Sickle", 450, 50, 4);    // 镰刀
//    createToolButton("Fish", 550, 50, 5);    // 钓鱼竿
//
//    // 监听鼠标滚轮事件
//    auto listener = cocos2d::EventListenerMouse::create();
//    listener->onMouseScroll = CC_CALLBACK_1(Toolbar::onMouseScroll, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//
//    return true;
//}
//
//void Toolbar::createToolButton(const std::string& label, float x, float y, int index) {
//    // 创建按钮
//    auto button = cocos2d::MenuItemLabel::create(
//        cocos2d::Label::createWithSystemFont(label, "Arial", 24),
//        [this, index](cocos2d::Ref* sender) {
//            onToolButtonClicked(index);
//        }
//    );
//    button->setPosition(x, y);
//
//    // 创建菜单并添加按钮
//    auto menu = cocos2d::Menu::create(button, nullptr);
//    menu->setPosition(0, 0);
//    this->addChild(menu);
//}
//
//// 点击工具按钮时，切换当前工具
//void Toolbar::onToolButtonClicked(int index) {
//    // 设置 Player 的当前工具
//    mainPlayer->setHeldTool(index);
//    updateCurrentTool();
//}
//
//// 更新当前选择的工具
//void Toolbar::updateCurrentTool() {
//    // 这里可以根据 mainPlayer->getHeldTool() 来更新 UI 或其他状态
//    cocos2d::log("Current tool: %d", mainPlayer->getHeldTool());
//}
//
//// 鼠标滚轮事件，切换工具
//void Toolbar::onMouseScroll(cocos2d::Event* event) {
//    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
//    if (mouseEvent->getScrollY() > 0) {
//        // 向上滚动，切换到下一个工具
//        int newTool = (mainPlayer->getHeldTool() + 1) % 6;  // 总共有6个工具，滚动时从0到5循环
//        mainPlayer->setHeldTool(newTool);
//    }
//    else {
//        // 向下滚动，切换到上一个工具
//        int newTool = (mainPlayer->getHeldTool() - 1 + 6) % 6;  // 确保负值循环
//        mainPlayer->setHeldTool(newTool);
//    }
//
//    updateCurrentTool();  // 更新工具状态
//}
