#pragma once
// Cow.h
#include"Animal.h"
#include "cocos2d.h"
class Cow : public Animal {
public:
    Cow();
    virtual ~Cow();

    static Cow* create(const std::string& image);
    bool init(const std::string& image);

    void startProduction(float timeToProduce) override;  // 牛的生产过程
    void collectProduct() override;  // 收集奶

private:
    void produceMilk();
};
