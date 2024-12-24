#include "calendar.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Clock.h"
#include "Tools.h"
#include "StartupScene.h"
#include "ItemStorage.h"
#include "Toolbar.h"

CalendarPanel::CalendarPanel() : panelBackground(nullptr) {
}

CalendarPanel::~CalendarPanel() {
}

bool CalendarPanel::init() {
    if (!Layer::init()) {
        return false;
    }
    Clock* clock = Clock::getInstance();

    // 设置面板背景
    panelBackground = cocos2d::Sprite::create("photo/ui/calendar.png");
    panelBackground->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(panelBackground);

    // 创建关闭按钮
    auto closeButton = cocos2d::ui::Button::create("photo/ui/out.png");
    closeButton->setPosition(cocos2d::Vec2(panelBackground->getContentSize().width - 30, panelBackground->getContentSize().height - 30));
    closeButton->addClickEventListener(CC_CALLBACK_1(CalendarPanel::closePanel, this));
    panelBackground->addChild(closeButton);

    int day = clock->getDay();
    int week = day / 8;
    int dayinweek = day % 7;
    if (dayinweek == 0) {
        dayinweek = 7;
    }

    // 创建当日
    auto dayImage = cocos2d::Sprite::create("photo/ui/dayimage.png"); // 图片路径
    int posx = 335 + dayinweek * 74;
    int posy = 430 - week * 74;
    dayImage->setPosition(cocos2d::Vec2(posx, posy));
    dayImage->setScale(0.9f);
    this->addChild(dayImage);

    // 创建节日
    auto holidayImage = cocos2d::Sprite::create("photo/ui/flag.png"); // 图片路径
    holidayImage->setPosition(cocos2d::Vec2(628 - 74, 280));
    holidayImage->setScale(1.2f);
    this->addChild(holidayImage);

    auto holidayImage2 = cocos2d::Sprite::create("photo/ui/flag.png"); // 图片路径
    holidayImage2->setPosition(cocos2d::Vec2(628 + 74, 280 + 74));
    holidayImage2->setScale(1.2f);
    this->addChild(holidayImage2);

    auto holidayImage3 = cocos2d::Sprite::create("photo/ui/flag.png"); // 图片路径
    holidayImage3->setPosition(cocos2d::Vec2(628 + 2 * 74, 280 - 74));
    holidayImage3->setScale(1.2f);
    this->addChild(holidayImage3);

    // 根据日期判断节日和奖励
    if (clock->getDay() == 12) { // 这里判断12日
        showEventPopup("HAPPY HOLIDAYS!", "Please enjoy    from us!", "fenshuijing");
        giveReward("fenshuijing");
    }
    if (clock->getDay() == 17) { // 这里判断17日
        showEventPopup("HAPPY HOLIDAYS!", "Please enjoy    from us!", "qicaikuangshi");
        giveReward("qicaikuangshi");
    }
    if (clock->getDay() == 27) { // 这里判断27日
        showEventPopup("HAPPY HOLIDAYS!", "Please enjoy    from us!", "zuanshi");
        giveReward("zuanshi");
    }

    return true;
}

void CalendarPanel::showEventPopup(const std::string& title, const std::string& message, const std::string& rewardType) {
    // 创建一个半透明背景
    auto overlay = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 128));
    this->addChild(overlay);

    // 创建弹窗背景
    auto popupBackground = cocos2d::Sprite::create("photo/ui/letterground.png");
    popupBackground->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    popupBackground->setScale(2.0f);
    this->addChild(popupBackground);

    // 添加标题
    auto titleLabel = cocos2d::Label::createWithSystemFont(title, "fonts/Marker Felt.ttf", 32);
    titleLabel->setPosition(cocos2d::Vec2(popupBackground->getContentSize().width / 2, popupBackground->getContentSize().height - 50));
    popupBackground->addChild(titleLabel);
    titleLabel->setTextColor(cocos2d::Color4B::BLACK);
    titleLabel->enableOutline(cocos2d::Color4B::WHITE, 2);

    // 添加信息文本
    auto messageLabel = cocos2d::Label::createWithSystemFont(message, "fonts/Marker Felt.ttf", 24);
    messageLabel->setPosition(cocos2d::Vec2(popupBackground->getContentSize().width / 2, popupBackground->getContentSize().height / 2 - 15));
    messageLabel->setTextColor(cocos2d::Color4B::BLACK);
    popupBackground->addChild(messageLabel);

    // 添加礼物图片
    std::string giftImagePath = getGiftImagePath(rewardType);
    auto giftImage = cocos2d::Sprite::create(giftImagePath); // 图片路径
    giftImage->setPosition(cocos2d::Vec2(682, 330));
    giftImage->setScale(4.5f);
    this->addChild(giftImage);

    // 创建确认按钮
    auto confirmButton = cocos2d::ui::Button::create("photo/ui/out.png");
    confirmButton->setPosition(cocos2d::Vec2(popupBackground->getContentSize().width / 2, 20));
    confirmButton->addClickEventListener([overlay, popupBackground, giftImage](cocos2d::Ref* sender) {
        // 点击确认按钮后，移除弹窗和半透明背景
        overlay->removeFromParentAndCleanup(true);     // 移除背景
        popupBackground->removeFromParentAndCleanup(true);  // 移除弹窗本身
        giftImage->removeFromParentAndCleanup(true);
        });
    confirmButton->setScale(0.6f);
    popupBackground->addChild(confirmButton);
}

void CalendarPanel::giveReward(const std::string& rewardType) {
    ItemStorage& storage = ItemStorage::getInstance();

    // 根据奖励类型发放不同的物品
    if (rewardType == "fenshuijing") {
        storage.addItem(StorageID::FENSHUIJING, 1);
        cocos2d::log("奖励已发放：粉水晶 ×1");
    }
    else if (rewardType == "qicaikuangshi") {
        storage.addItem(StorageID::QICAIKUANGSHI, 1);
        cocos2d::log("奖励已发放：七彩矿石 ×1");
    }
    else if (rewardType == "zuanshi") {
        storage.addItem(StorageID::ZUANSHI, 1);
        cocos2d::log("奖励已发放：钻石 ×1");
    }
}

std::string CalendarPanel::getGiftImagePath(const std::string& rewardType) {

    if (rewardType == "fenshuijing") {
        return "photo/storage/fenshuijing.png";
    }
    else if (rewardType == "qicaikuangshi") {
        return "photo/storage/qicaikuangshi.png";
    }
    else if (rewardType == "zuanshi") {
        return "photo/storage/zuanshi.png";
    }

    return "";
}


CalendarPanel* CalendarPanel::create() {
    CalendarPanel* panel = new CalendarPanel();
    if (panel && panel->init()) {
        panel->autorelease();
        return panel;
    }
    CC_SAFE_DELETE(panel);
    return nullptr;
}

void CalendarPanel::closePanel(cocos2d::Ref* sender) {
    this->removeFromParentAndCleanup(true);
}
