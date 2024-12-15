#pragma once
#include "cocos2d.h"
#include "Task.h"//npc�������
#include "InteractiveElement.h" //����ʽ���
#include"NPCinfo.h"//չʾNPC���
class Resident : public cocos2d::Sprite,public InteractiveElement {
protected:
    std::string name;               // NPC ������
    std::string profession;         // NPC ��ְҵ
    int romance;                    // ����ֵ
    int friendship;                 //����ֵ
    Task* currentTask;              // ��ǰ����
    bool busy;                      // �Ƿ�æµ
    // �����صĳ�Ա����
    cocos2d::Label* nameLabel;

public:
 
    // NPC �Ĺ��캯������������
    Resident();
    virtual ~Resident();

    // ��׼�Ĵ����ͳ�ʼ������
    bool init(const std::string& n, const std::string& prof, const std::string& imgPath, const cocos2d::Vec2& site);

   // ���� Resident ��س�Ա����
    // ��ȡ NPC �Ļ�����Ϣ
    const std::string& getName() const { return name; }
    const std::string& getProfession() const { return profession; }

    // ����ֵ����ֵ�������
    //get�������ڶ���ӿ�
    int getFriendship() const { return friendship; }
    int getRomance() const { return romance; }
    void increaseFriendship() { friendship++; }
    void increaseRomance() { romance++; }
    //���ӷ�ʽ����һ���ģ�����ѡ���ڸ���ʵ��
    // �������ʱ��������ֵ
    virtual void completeTask() {
        if (currentTask && !currentTask->isCompleted) {
            currentTask->isCompleted = true;
            increaseFriendship();
        }
    }
    // ���Ͱ���ʱ��������ֵ
    virtual void giveLove() {
        increaseRomance();
    }

    // ���úͻ�ȡ����
    void setTask(Task* task);
    Task* getCurrentTask() const;

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