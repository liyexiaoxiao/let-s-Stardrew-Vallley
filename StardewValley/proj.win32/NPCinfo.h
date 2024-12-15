#ifndef __NPC_INFO_H__
#define __NPC_INFO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NPCInfo : public cocos2d::Layer {
public:
    NPCInfo() {};
    ~NPCInfo() {};

    // 初始化NPC信息界面
    bool init();
    static NPCInfo* create();

    // 显示NPC信息面板
    void showResidentInfo(const std::string& name, const std::string& profession, int friendship, int romance);

    // 关闭面板
    void closePanel();
private:
    cocos2d::Sprite* background; // 背景图片
    cocos2d::Label* nameLabel;   // NPC的名字
    cocos2d::Label* professionLabel; // NPC的职业
    cocos2d::Label* friendshipLabel; // 友谊值
    cocos2d::Label* romanceLabel;    // 浪漫值
    // 其他UI组件...
    cocos2d::ui::Button* closeButton;    // 关闭按钮
};

#endif  // __NPC_INFO_H__