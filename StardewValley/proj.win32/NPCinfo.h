#ifndef __NPC_INFO_H__
#define __NPC_INFO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NPCInfo : public cocos2d::Layer {
public:
    NPCInfo() {};
    ~NPCInfo() {};

    // ��ʼ��NPC��Ϣ����
    bool init();
    static NPCInfo* create();

    // ��ʾNPC��Ϣ���
    void showResidentInfo(const std::string& name, const std::string& profession, int friendship, int romance);

    // �ر����
    void closePanel();
private:
    cocos2d::Sprite* background; // ����ͼƬ
    cocos2d::Label* nameLabel;   // NPC������
    cocos2d::Label* professionLabel; // NPC��ְҵ
    cocos2d::Label* friendshipLabel; // ����ֵ
    cocos2d::Label* romanceLabel;    // ����ֵ
    // ����UI���...
    cocos2d::ui::Button* closeButton;    // �رհ�ť
};

#endif  // __NPC_INFO_H__