//#include "Toolbar.h"
//#include "Player.h"
//extern Player* mainPlayer;
//
//bool Toolbar::init() {
//    if (!Layer::init()) {
//        return false;
//    }
//
//    // ��������������
//    auto toolbarContainer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150), 640, 100);
//    toolbarContainer->setPosition(0, 0);  // ���ù�����λ��
//    this->addChild(toolbarContainer);
//
//    // �������߰�ť
//    createToolButton("Axe", 50, 50, 0);    // ��ͷ
//    createToolButton("Hoe", 150, 50, 1);    // ��ͷ
//    createToolButton("Watering Can", 250, 50, 2);  // ��ˮ��
//    createToolButton("Pickaxe", 350, 50, 3);  // ʮ�ָ�
//    createToolButton("Sickle", 450, 50, 4);    // ����
//    createToolButton("Fish", 550, 50, 5);    // �����
//
//    // �����������¼�
//    auto listener = cocos2d::EventListenerMouse::create();
//    listener->onMouseScroll = CC_CALLBACK_1(Toolbar::onMouseScroll, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//
//    return true;
//}
//
//void Toolbar::createToolButton(const std::string& label, float x, float y, int index) {
//    // ������ť
//    auto button = cocos2d::MenuItemLabel::create(
//        cocos2d::Label::createWithSystemFont(label, "Arial", 24),
//        [this, index](cocos2d::Ref* sender) {
//            onToolButtonClicked(index);
//        }
//    );
//    button->setPosition(x, y);
//
//    // �����˵�����Ӱ�ť
//    auto menu = cocos2d::Menu::create(button, nullptr);
//    menu->setPosition(0, 0);
//    this->addChild(menu);
//}
//
//// ������߰�ťʱ���л���ǰ����
//void Toolbar::onToolButtonClicked(int index) {
//    // ���� Player �ĵ�ǰ����
//    mainPlayer->setHeldTool(index);
//    updateCurrentTool();
//}
//
//// ���µ�ǰѡ��Ĺ���
//void Toolbar::updateCurrentTool() {
//    // ������Ը��� mainPlayer->getHeldTool() ������ UI ������״̬
//    cocos2d::log("Current tool: %d", mainPlayer->getHeldTool());
//}
//
//// �������¼����л�����
//void Toolbar::onMouseScroll(cocos2d::Event* event) {
//    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
//    if (mouseEvent->getScrollY() > 0) {
//        // ���Ϲ������л�����һ������
//        int newTool = (mainPlayer->getHeldTool() + 1) % 6;  // �ܹ���6�����ߣ�����ʱ��0��5ѭ��
//        mainPlayer->setHeldTool(newTool);
//    }
//    else {
//        // ���¹������л�����һ������
//        int newTool = (mainPlayer->getHeldTool() - 1 + 6) % 6;  // ȷ����ֵѭ��
//        mainPlayer->setHeldTool(newTool);
//    }
//
//    updateCurrentTool();  // ���¹���״̬
//}
