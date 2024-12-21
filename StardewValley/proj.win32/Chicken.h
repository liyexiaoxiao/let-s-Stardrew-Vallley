#pragma once
//ʵ�ּ���״̬��ع���
#include "cocos2d.h"
using namespace std;

class Chicken : public cocos2d::Sprite {
public:
    enum class State {
        Hungry,  // �ո�
        Full,    // ����
    };

    Chicken();
    ~Chicken();

    static Chicken* create(const std::string& image);
    bool init(const std::string& image);

    // ���ü���״̬
    void setState(State newState);

    // ��ȡ����״̬
    State getState() const;

    // �������������������Ķ�ʱ��
    void startEggProduction(float timeToLayEgg);

    // ����
    void layEgg();

    // ��ȡ�Ƿ��е�
    bool hasEgg() const;

    // ȡ������յ�
    void collectEgg();

private:
    State currentState;
    bool eggAvailable;  // �Ƿ��е�
    float eggProductionTime;  // ����ʱ��
    float eggTimer;  // ������ʱ��

    cocos2d::ProgressTimer* eggBar;  // ������
};
