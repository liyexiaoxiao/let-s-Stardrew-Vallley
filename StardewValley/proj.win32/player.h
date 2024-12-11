#pragma once
//ĿǰΪgyx11/30����ʹ�ã�����
#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
class Player : public cocos2d::Sprite {
public:
    Player();  // ���캯��
    ~Player(); // ��������

    static Player* create(const std::string& filename); // ������Ҷ���

    bool init(const std::string& filename); // ��ʼ����Ҷ���

    void move(const cocos2d::Vec2& direction, float distance); // ����ƶ�����

    void setHealth(int health);   // ��������ֵ
    int getHealth() const;        // ��ȡ����ֵ

    void setSpeed(float speed);   // �����ƶ��ٶ�
    float getSpeed() const;       // ��ȡ�ƶ��ٶ�
    int Heldtool = 1;
    //Ϊ�˲�����ʱ��˲���=1ʱ���ų�ͷ������2ʱ���Ž�ˮ��
    int Heldseed =2;
    //Ϊ�˲�����ʱ��˲���=1ʱ���ŷ�������ӣ�����2ʱ������ݮ���ӣ�����3ʱ�����Ϲ����ӣ�����4ʱ����С������

    std::string PlayerName;
    std::string FarmName;
    void setPlayerName(const std::string& name) { PlayerName = name; } // ���� playername
    std::string getPlayerName() const { return PlayerName; };  // ��ȡ playername
    void setFarmName(const std::string& name) { FarmName = name; } // ���� FarmName
    std::string getFarmName() const { return FarmName; };  // ��ȡ FarmName

    int money;
    void setMoney(const int newmoney) { money = newmoney; }
    int getMoney() const { return money; };
    
private:
    int health;   // ����ֵ
    float speed;  // �ƶ��ٶ�
    
};

#endif // PLAYER_H
