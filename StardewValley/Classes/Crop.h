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
    int growthTime;   // �ɳ�����ʱ��
    int currentAge;   // ��ǰ�����׶�
};

#endif
#pragma once
