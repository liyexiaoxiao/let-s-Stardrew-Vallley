//ĿǰΪgyx11/30����ʹ��
#pragma once
#ifndef __WEED_H__
#define __WEED_H__

#include "cocos2d.h"

class Weed : public cocos2d::Sprite {
public:
    Weed();
    ~Weed();

    static Weed* create();
    bool init();

    void removeWeed(); // �Ƴ��Ӳ�

    bool isRemoved() const { return removed; }

private:
    bool removed; // ����Ӳ��Ƿ��ѱ��Ƴ�
};

#endif // __WEED_H__
