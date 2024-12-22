
#include "cocos2d.h"

class CalendarPanel : public cocos2d::Layer {
public:
    CalendarPanel();
    virtual ~CalendarPanel();

    bool init();
    void closePanel(cocos2d::Ref* sender);
    void checkSpecialEvent();
    void showEventPopup(const std::string& title, const std::string& message, const std::string& rewardType);
    void giveReward(const std::string& rewardType);
    static CalendarPanel* create(int currentDay, int currentMonth, int currentYear);
    std::string getGiftImagePath(const std::string& rewardType);

private:
    cocos2d::Sprite* panelBackground;
    cocos2d::Label* dayLabel;
    cocos2d::Label* monthYearLabel;
    cocos2d::Vector<cocos2d::Label*> dayLabels;
};
#pragma once
