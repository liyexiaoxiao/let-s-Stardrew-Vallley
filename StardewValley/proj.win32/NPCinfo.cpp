//没有处理点击向下传递
#include"NPCinfo.h"

bool NPCInfo::init() {
    if (!Layer::init()) {
        return false;
    }

    // 创建背景
    background = cocos2d::Sprite::create("photo/ui/Menu.png");
    background->setScale(2.2f);
    // 获取游戏窗口的宽度和高度
    const float width = cocos2d::Director::getInstance()->getVisibleSize().width;
    const float height = cocos2d::Director::getInstance()->getVisibleSize().height;
    // 将背景图片居中显示
    background->setPosition(cocos2d::Vec2(width / 2, height / 2));
    // 将背景添加到当前层
    this->addChild(background);

    // 创建标签显示NPC的名字
    nameLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 24);
    nameLabel->setPosition(cocos2d::Vec2(width / 2, height - 250));
    this->addChild(nameLabel);

    // 创建标签显示NPC的职业
    professionLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 18);
    professionLabel->setPosition(cocos2d::Vec2(width / 2,height - 300));
    this->addChild(professionLabel);

    // 创建标签显示友谊值
    friendshipLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 18);
    friendshipLabel->setPosition(cocos2d::Vec2(width / 2,height - 350));
    this->addChild(friendshipLabel);

    // 创建标签显示浪漫值
    romanceLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 18);
    romanceLabel->setPosition(cocos2d::Vec2(width / 2, height - 400));
    this->addChild(romanceLabel);
    // 设置默认不可见
    this->setVisible(false);

    //关闭面板按钮
     // 创建关闭按钮
    closeButton = cocos2d::ui::Button::create("photo/startup_p/ExitButton.png", "photo/startup_p/ExitButtonPressed.png");
    closeButton->setPosition(cocos2d::Vec2(width - closeButton->getContentSize().width / 2, closeButton->getContentSize().height / 2));
    closeButton->addClickEventListener([this](cocos2d::Ref* sender) {
        this->closePanel();
        });
    this->addChild(closeButton);

    return true;
}
NPCInfo* NPCInfo::create() {
    auto ret = new(std::nothrow) NPCInfo();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
//显示NPC个人信息
void NPCInfo::showResidentInfo(const std::string& name, const std::string& profession, int friendship, int romance) {
    // 更新NPC的名字
    if (nameLabel) {
        nameLabel->setString(name);
    }

    // 更新NPC的职业
    if (professionLabel) {
        professionLabel->setString(profession);
    }

    // 更新友谊值
    if (friendshipLabel) {
        std::string friendshipStr = "Friendship: " + std::to_string(friendship);
        friendshipLabel->setString(friendshipStr);
    }

    // 更新浪漫值
    if (romanceLabel) {
        std::string romanceStr = "Romance: " + std::to_string(romance);
        romanceLabel->setString(romanceStr);
    }

    // 显示面板
    this->setVisible(true);
}
//关闭面板
void NPCInfo::closePanel() {
    this->removeFromParent();
}