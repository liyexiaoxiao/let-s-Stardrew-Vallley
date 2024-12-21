#pragma once
//实现鸡的状态相关管理
#include "cocos2d.h"
using namespace std;

class Chicken : public cocos2d::Sprite {
public:
    enum class State {
        Hungry,  // 空腹
        Full,    // 饱腹
    };

    Chicken();
    ~Chicken();

    static Chicken* create(const std::string& image);
    bool init(const std::string& image);

    // 设置鸡的状态
    void setState(State newState);

    // 获取鸡的状态
    State getState() const;

    // 当鸡饱腹后启动产蛋的定时器
    void startEggProduction(float timeToLayEgg);

    // 产蛋
    void layEgg();

    // 获取是否有蛋
    bool hasEgg() const;

    // 取蛋后清空蛋
    void collectEgg();

private:
    State currentState;
    bool eggAvailable;  // 是否有蛋
    float eggProductionTime;  // 产蛋时间
    float eggTimer;  // 产蛋计时器

    cocos2d::ProgressTimer* eggBar;  // 进度条
};
