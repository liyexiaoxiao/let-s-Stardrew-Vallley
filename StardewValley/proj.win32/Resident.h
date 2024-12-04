#pragma once
#include "cocos2d.h"
#include "Task.h"//npc任务相关

class Resident : public cocos2d::Sprite{
protected:
    std::string name;               // NPC 的名字
    std::string profession;         // NPC 的职业
    int romance;                    // 浪漫值
    int friendship;                 //友谊值
    Task* currentTask;              // 当前任务
    bool busy;                      // 是否忙碌

public:
    // NPC 的构造函数和析构函数
    Resident();
    virtual ~Resident();

    // 标准的创建和初始化方法
    bool init(const std::string& n, const std::string& prof, const std::string& imgPath);

   // 其他 Resident 相关成员函数
    // 获取 NPC 的基本信息
    const std::string& getName() const { return name; }
    const std::string& getProfession() const { return profession; }

    // 友谊值浪漫值相关内容
    //get函数用于对外接口
    int getFriendship() const { return friendship; }
    int getRomance() const { return romance; }
    void increaseFriendship() { friendship++; }
    void increaseRomance() { romance++; }
    //增加方式都是一样的，所以选择在父类实现
    // 完成任务时增加友谊值
    virtual void completeTask() {
        if (currentTask && !currentTask->isCompleted) {
            currentTask->isCompleted = true;
            increaseFriendship();
        }
    }
    // 赠送爱心时增加浪漫值
    virtual void giveLove() {
        increaseRomance();
    }

    // 设置和获取任务
    void setTask(Task* task);
    Task* getCurrentTask() const;

    // 设置和获取忙碌状态
    bool isBusy() const { return busy; }
    void setBusy(bool busyStatus);
};