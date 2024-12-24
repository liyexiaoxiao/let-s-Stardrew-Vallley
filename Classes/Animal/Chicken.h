#pragma once
//实现鸡的状态相关管理
#include "cocos2d.h"
#include"Animal.h"
using namespace std;

class Chicken : public Animal {
public:
    Chicken();
    virtual ~Chicken();

    static Chicken* create(const std::string& image);
    bool init(const std::string& image);

    void startProduction(float timeToProduce) override;  // 鸡的生产过程
    void collectProduct() override;  // 收集蛋

private:
    void layEgg();
};

