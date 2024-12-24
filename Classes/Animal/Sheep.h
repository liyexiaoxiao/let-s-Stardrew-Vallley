#pragma once
#include "cocos2d.h"
#include"Animal.h"
class Sheep : public Animal {
public:
    Sheep();
    virtual ~Sheep();

    static Sheep* create(const std::string& image);
    bool init(const std::string& image);

    void startProduction(float timeToProduce) override;  // 羊的生产过程
    void collectProduct() override;  // 收集羊毛

private:
    void produceWool();
};
