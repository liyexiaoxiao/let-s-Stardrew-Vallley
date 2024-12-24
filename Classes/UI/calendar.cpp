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

    // ������屳��
    panelBackground = cocos2d::Sprite::create("photo/ui/calendar.png");
    panelBackground->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(panelBackground);

    // �����رհ�ť
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

    // ��������
    auto dayImage = cocos2d::Sprite::create("photo/ui/dayimage.png"); // ͼƬ·��
    int posx = 335 + dayinweek * 74;
    int posy = 430 - week * 74;
    dayImage->setPosition(cocos2d::Vec2(posx, posy));
    dayImage->setScale(0.9f);
    this->addChild(dayImage);

    // ��������
    auto holidayImage = cocos2d::Sprite::create("photo/ui/flag.png"); // ͼƬ·��
    holidayImage->setPosition(cocos2d::Vec2(628 - 74, 280));
    holidayImage->setScale(1.2f);
    this->addChild(holidayImage);

    auto holidayImage2 = cocos2d::Sprite::create("photo/ui/flag.png"); // ͼƬ·��
    holidayImage2->setPosition(cocos2d::Vec2(628 + 74, 280 + 74));
    holidayImage2->setScale(1.2f);
    this->addChild(holidayImage2);

    auto holidayImage3 = cocos2d::Sprite::create("photo/ui/flag.png"); // ͼƬ·��
    holidayImage3->setPosition(cocos2d::Vec2(628 + 2 * 74, 280 - 74));
    holidayImage3->setScale(1.2f);
    this->addChild(holidayImage3);

    // ���������жϽ��պͽ���
    if (clock->getDay() == 12) { // �����ж�12��
        showEventPopup("HAPPY HOLIDAYS!", "Please enjoy    from us!", "fenshuijing");
        giveReward("fenshuijing");
    }
    if (clock->getDay() == 17) { // �����ж�17��
        showEventPopup("HAPPY HOLIDAYS!", "Please enjoy    from us!", "qicaikuangshi");
        giveReward("qicaikuangshi");
    }
    if (clock->getDay() == 27) { // �����ж�27��
        showEventPopup("HAPPY HOLIDAYS!", "Please enjoy    from us!", "zuanshi");
        giveReward("zuanshi");
    }

    return true;
}

void CalendarPanel::showEventPopup(const std::string& title, const std::string& message, const std::string& rewardType) {
    // ����һ����͸������
    auto overlay = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 128));
    this->addChild(overlay);

    // ������������
    auto popupBackground = cocos2d::Sprite::create("photo/ui/letterground.png");
    popupBackground->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    popupBackground->setScale(2.0f);
    this->addChild(popupBackground);

    // ��ӱ���
    auto titleLabel = cocos2d::Label::createWithSystemFont(title, "fonts/Marker Felt.ttf", 32);
    titleLabel->setPosition(cocos2d::Vec2(popupBackground->getContentSize().width / 2, popupBackground->getContentSize().height - 50));
    popupBackground->addChild(titleLabel);
    titleLabel->setTextColor(cocos2d::Color4B::BLACK);
    titleLabel->enableOutline(cocos2d::Color4B::WHITE, 2);

    // �����Ϣ�ı�
    auto messageLabel = cocos2d::Label::createWithSystemFont(message, "fonts/Marker Felt.ttf", 24);
    messageLabel->setPosition(cocos2d::Vec2(popupBackground->getContentSize().width / 2, popupBackground->getContentSize().height / 2 - 15));
    messageLabel->setTextColor(cocos2d::Color4B::BLACK);
    popupBackground->addChild(messageLabel);

    // �������ͼƬ
    std::string giftImagePath = getGiftImagePath(rewardType);
    auto giftImage = cocos2d::Sprite::create(giftImagePath); // ͼƬ·��
    giftImage->setPosition(cocos2d::Vec2(682, 330));
    giftImage->setScale(4.5f);
    this->addChild(giftImage);

    // ����ȷ�ϰ�ť
    auto confirmButton = cocos2d::ui::Button::create("photo/ui/out.png");
    confirmButton->setPosition(cocos2d::Vec2(popupBackground->getContentSize().width / 2, 20));
    confirmButton->addClickEventListener([overlay, popupBackground, giftImage](cocos2d::Ref* sender) {
        // ���ȷ�ϰ�ť���Ƴ������Ͱ�͸������
        overlay->removeFromParentAndCleanup(true);     // �Ƴ�����
        popupBackground->removeFromParentAndCleanup(true);  // �Ƴ���������
        giftImage->removeFromParentAndCleanup(true);
        });
    confirmButton->setScale(0.6f);
    popupBackground->addChild(confirmButton);
}

void CalendarPanel::giveReward(const std::string& rewardType) {
    ItemStorage& storage = ItemStorage::getInstance();

    // ���ݽ������ͷ��Ų�ͬ����Ʒ
    if (rewardType == "fenshuijing") {
        storage.addItem(StorageID::FENSHUIJING, 1);
        cocos2d::log("�����ѷ��ţ���ˮ�� ��1");
    }
    else if (rewardType == "qicaikuangshi") {
        storage.addItem(StorageID::QICAIKUANGSHI, 1);
        cocos2d::log("�����ѷ��ţ��߲ʿ�ʯ ��1");
    }
    else if (rewardType == "zuanshi") {
        storage.addItem(StorageID::ZUANSHI, 1);
        cocos2d::log("�����ѷ��ţ���ʯ ��1");
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
