#pragma once
//鉴于有好几种动物，设置一个动物基类进行处理
// Animal.h
#include"cocos2d.h"

class Animal : public cocos2d::Sprite {
public:
    enum class State {
        Hungry,
        Full
    };

    Animal();
    virtual bool init(const std::string& image);
    virtual ~Animal();
    virtual void startProduction(float timeToProduce) = 0;  // 每种动物不同的生产过程
    virtual void updateProgressBar(float dt);  // 更新进度条

    void setState(State newState);
    State getState() const;

    bool hasProduct() const;
    virtual void collectProduct() = 0;  // 每种动物的收集操作

protected:
    State currentState;
    bool productAvailable;
    float productionTimer;  // 用来计时生产
    cocos2d::ProgressTimer* progressBar;  // 动物的进度条
};

