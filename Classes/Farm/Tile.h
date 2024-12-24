#ifndef __TILE_H__
#define __TILE_H__

#include "cocos2d.h"
#include "Crop.h"

class Tile {
public:
    Tile(); // ���캯��
    void plow(); // ����
    void plant(Crop* crop); // ��ֲ����
    void water(); // ��ˮ
    bool isPlanted() const; // �Ƿ�����ֲ����
    bool isHarvestable() const; // �Ƿ�����ջ�
    Crop* getCrop() const; // ��ȡ����

private:
    bool plowed; // �Ƿ��Ѹ���
    bool watered; // �Ƿ��ѽ�ˮ
    Crop* crop; // �����ϵ�����
};

#endif
