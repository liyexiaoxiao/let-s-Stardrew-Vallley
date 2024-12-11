#pragma once
//目前为gyx11/30测试使用！！！
#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
class Player : public cocos2d::Sprite {
public:
    Player();  // 构造函数
    ~Player(); // 析构函数

    static Player* create(const std::string& filename); // 创建玩家对象

    bool init(const std::string& filename); // 初始化玩家对象

    void move(const cocos2d::Vec2& direction, float distance); // 玩家移动方法

    void setHealth(int health);   // 设置生命值
    int getHealth() const;        // 获取生命值

    void setSpeed(float speed);   // 设置移动速度
    float getSpeed() const;       // 获取移动速度
    int Heldtool = 1;
    //为了测试暂时设此参数=1时拿着锄头，等于2时拿着浇水壶
    int Heldseed =2;
    //为了测试暂时设此参数=1时拿着防风草种子，等于2时拿着树莓种子，等于3时拿着南瓜种子，等于4时拿着小麦种子

    std::string PlayerName;
    std::string FarmName;
    void setPlayerName(const std::string& name) { PlayerName = name; } // 设置 playername
    std::string getPlayerName() const { return PlayerName; };  // 获取 playername
    void setFarmName(const std::string& name) { FarmName = name; } // 设置 FarmName
    std::string getFarmName() const { return FarmName; };  // 获取 FarmName

    int money;
    void setMoney(const int newmoney) { money = newmoney; }
    int getMoney() const { return money; };
    
private:
    int health;   // 生命值
    float speed;  // 移动速度
    
};

#endif // PLAYER_H
