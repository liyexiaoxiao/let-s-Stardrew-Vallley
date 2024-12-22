#pragma once
//�����кü��ֶ������һ�����������д���
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
    virtual void startProduction(float timeToProduce) = 0;  // ÿ�ֶ��ﲻͬ����������
    virtual void updateProgressBar(float dt);  // ���½�����

    void setState(State newState);
    State getState() const;

    bool hasProduct() const;
    virtual void collectProduct() = 0;  // ÿ�ֶ�����ռ�����

protected:
    State currentState;
    bool productAvailable;
    float productionTimer;  // ������ʱ����
    cocos2d::ProgressTimer* progressBar;  // ����Ľ�����
};

