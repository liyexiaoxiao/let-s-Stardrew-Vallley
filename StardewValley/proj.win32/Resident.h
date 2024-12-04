#pragma once
#include "cocos2d.h"
#include "Task.h"//npc�������

class Resident : public cocos2d::Sprite{
protected:
    std::string name;               // NPC ������
    std::string profession;         // NPC ��ְҵ
    int romance;                    // ����ֵ
    int friendship;                 //����ֵ
    Task* currentTask;              // ��ǰ����
    bool busy;                      // �Ƿ�æµ

public:
    // NPC �Ĺ��캯������������
    Resident();
    virtual ~Resident();

    // ��׼�Ĵ����ͳ�ʼ������
    bool init(const std::string& n, const std::string& prof, const std::string& imgPath);

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
};