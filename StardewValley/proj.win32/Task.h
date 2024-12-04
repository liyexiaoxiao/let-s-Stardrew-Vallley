#pragma once
#include "cocos2d.h"
class Task {
public:
    std::string taskName;      // 任务名称
    std::string description;   // 任务描述
    bool isCompleted;          // 任务是否完成
    int reward;                // 任务奖励（例如金币）

    Task(std::string name, std::string desc, int r)
        : taskName(name), description(desc), isCompleted(false), reward(r) {}

    // 标记任务为完成
    void completeTask() {
        isCompleted = true;
        CCLOG("Task %s completed!", taskName.c_str());
    }

    // 获取任务奖励
    void giveReward() {
        if (isCompleted) {
            CCLOG("You received %d as reward for completing the task.", reward);
        }
    }
};
