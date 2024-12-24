#pragma once
//ʵ�ּ���״̬��ع���
#include "cocos2d.h"
#include"Animal.h"
using namespace std;

class Chicken : public Animal {
public:
    Chicken();
    virtual ~Chicken();

    static Chicken* create(const std::string& image);
    bool init(const std::string& image);

    void startProduction(float timeToProduce) override;  // ������������
    void collectProduct() override;  // �ռ���

private:
    void layEgg();
};

