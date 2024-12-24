#pragma once
#include "cocos2d.h"
#include "InteractiveElement.h" //����ʽ���
#include"NPCinfo.h"//չʾNPC���
class Resident : public cocos2d::Sprite,public InteractiveElement {
protected:
    std::string name;               // NPC ������
    std::string profession;         // NPC ��ְҵ
    int romance;                    // ����ֵ
    int cureentDay;
    int friendship;                 //����ֵ
    bool busy;                      // �Ƿ�æµ
    // �����صĳ�Ա����
    cocos2d::Label* nameLabel;
    //���к���ť
        //���Ӱ�ť����npc���к�������ֵ����
    // ������ť������ NPC �Ա�
    cocos2d::MenuItemImage* button;


public:
    bool isfs = false;                      //�����жϽ����Ƿ��Ѿ���������ֵ��

    // NPC �Ĺ��캯������������
    Resident();
    virtual ~Resident();

    bool init(const std::string& n, const std::string& prof, const std::string& imgPath, const cocos2d::Vec2& site);

   // ���� Resident ��س�Ա����
    // ��ȡ NPC �Ļ�����Ϣ
    const std::string& getName() const { return name; }
    const std::string& getProfession() const { return profession; }

    // ����ֵ����ֵ�������
    // ���к�����ʵ��
    void onButtonClick(cocos2d::Ref* sender);
    //get�������ڶ���ӿ�
    int getFriendship() const { return friendship; }
    int getRomance() const { return romance; }
    void increaseFriendship() { friendship++; }
    void increaseRomance() { romance++; }
 

    // ���úͻ�ȡæµ״̬
    bool isBusy() const { return busy; }
    void setBusy(bool busyStatus);

    //��̬��Ӧ���
     // ��ʾ NPC ���
    void showInfoPanel();  // ��ʾ��Ϣ���
    // ʵ�� InteractiveElement �� onClick ����
    int onClick() override {
        showInfoPanel();
        return 0;//0������ֵûʲô��
    }
    //���ð�Χ�н��ж�̬�ж�
    cocos2d::Rect getBoundingBox() const override;
};