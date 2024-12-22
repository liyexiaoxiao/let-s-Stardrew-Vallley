#include "Resident.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Clock.h"
//增加每天只能增加一次友谊值

Resident::Resident()
    : name("Unknown"), profession("Unknown"), romance(0), friendship(0),busy(false) {
    nameLabel = cocos2d::Label::createWithSystemFont("Name: ", "Arial", 24);
    this->addChild(nameLabel);
    nameLabel->setVisible(false);
}

Resident::~Resident() {}

bool Resident::init(const std::string& n, const std::string& prof, const std::string& imgPath, const cocos2d::Vec2& site) {
    name = n;
    profession = prof;
    romance = 0;   // 默认浪漫值
    busy = false;
    this->initWithFile(imgPath);  // 使用 Cocos2d 的方法来加载图像
    this->setPosition(site);//初始生成位置--屏幕坐标

    //增加按钮，给npc打招呼，友谊值增加
    // 创建按钮，放在 NPC 旁边
    auto button = cocos2d::MenuItemImage::create(
        "photo/ui/basic.png",  // 按钮正常状态的图片
        "photo/ui/basic2.png", // 按钮按下状态的图片
        CC_CALLBACK_1(Resident::onButtonClick, this) // 按钮点击事件
    );
    button->setScale(4.0f);
    button->setPosition(cocos2d::Vec2(80, 0));  // 相对于 NPC 左上角 (0, 0) 的偏移
    auto menu = cocos2d::Menu::create(button, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    menu->setLocalZOrder(10);  // 确保按钮位于其它元素之上
    this->addChild(menu);
    return true;
}

//打招呼按钮回调事件

void Resident::onButtonClick(cocos2d::Ref* sender) {
    // NPC 说话的逻辑
    auto talkLabel =cocos2d:: Label::createWithSystemFont("Hello, I'm " + name + "!", "Arial", 40);
    talkLabel->setPosition(this->getPosition() + cocos2d::Vec2(0, 50)); // 话语显示在 NPC 上方
    this->getParent()->addChild(talkLabel);
    // 延迟 2 秒后删除显示的文字
    auto delay = cocos2d::DelayTime::create(2.0f);
    auto removeAction = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, removeAction, nullptr);
    talkLabel->runAction(sequence);
    // 增加友谊值
    if (!isfs) {
        increaseFriendship();
        // 显示友谊值增加的提示（可以使用 Label 来显示）
        auto friendshipLabel = cocos2d::Label::createWithSystemFont("Friendship +1", "Arial", 40);
        friendshipLabel->setPosition(this->getPosition() + cocos2d::Vec2(0, -10));
        this->getParent()->addChild(friendshipLabel, 1);

        // 2秒后移除友谊值提示
        friendshipLabel->runAction(cocos2d::Sequence::create(
            cocos2d::DelayTime::create(2.0f),
            cocos2d::RemoveSelf::create(),
            nullptr
        ));
        isfs = true;
    }
    else {
        auto friendshipLabel = cocos2d::Label::createWithSystemFont("Please wait for tomorrow", "Arial", 35);
        friendshipLabel->setPosition(this->getPosition() + cocos2d::Vec2(0, -10));
        this->getParent()->addChild(friendshipLabel, 1);

        // 2秒后移除友谊值提示
        friendshipLabel->runAction(cocos2d::Sequence::create(
            cocos2d::DelayTime::create(2.0f),
            cocos2d::RemoveSelf::create(),
            nullptr
        ));
    }
}

void Resident::setBusy(bool busyStatus) {
    busy = busyStatus;
}


//点击交互相关
cocos2d::Rect Resident::getBoundingBox() const {
    // 动态返回当前 Resident 的包围盒
    auto position = this->getPosition();  // 当前 Resident 的世界坐标
    auto contentSize = this->getContentSize();
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,
        position.y - contentSize.height * this->getAnchorPoint().y,
        contentSize.width,
        contentSize.height
    );
}
//展示面板测试
void Resident::showInfoPanel() {
    NPCInfo* npcLayer = NPCInfo::create(); // 创建NPCInfo实例
    npcLayer->showResidentInfo(name, profession, friendship, romance); // 显示NPC信息
    this->getParent()->addChild(npcLayer); // 将面板添加到父节点
}