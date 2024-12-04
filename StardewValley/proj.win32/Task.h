#pragma once
#include "cocos2d.h"
class Task {
public:
    std::string taskName;      // ��������
    std::string description;   // ��������
    bool isCompleted;          // �����Ƿ����
    int reward;                // �������������ң�

    Task(std::string name, std::string desc, int r)
        : taskName(name), description(desc), isCompleted(false), reward(r) {}

    // �������Ϊ���
    void completeTask() {
        isCompleted = true;
        CCLOG("Task %s completed!", taskName.c_str());
    }

    // ��ȡ������
    void giveReward() {
        if (isCompleted) {
            CCLOG("You received %d as reward for completing the task.", reward);
        }
    }
};
