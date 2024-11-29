#ifndef __CROP_H__
#define __CROP_H__

#include <string>

class Crop {
public:
    Crop(const std::string& name, int growthTime);
    void grow();
    bool isMature() const;
    std::string getName() const;

private:
    std::string name;
    int growthTime;   // 成长所需时间
    int currentAge;   // 当前生长阶段
};

#endif
#pragma once
