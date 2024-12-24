#pragma once
//目前为gyx11/30测试使用！！！
#ifndef PLAYER_H
#define PLAYER_H
#include "cocos2d.h"




//每个物品包含的信息
enum class ItemID {
    T_Axe = 1,       // 斧头
    T_Hoe = 2,      // 锄头
    T_WateringCan = 3, // 浇水壶
    T_Pickaxe = 4,//镐子
    T_Sickle = 5,//镰刀
    T_Fish = 6,
} 


class Player : public cocos2d::Sprite {
public:
    Player();  // 构造函数
    ~Player(); // 析构函数

    static Player* create(const std::string& filename); // 创建玩家对
    bool init(const std::string& filename); // 初始化玩家对象
    void setPlayerName(const std::string& name) { PlayerName = name; } // 设置 playername
    std::string getPlayerName() const { return PlayerName; };  // 获取 playername
    void setFarmName(const std::string& name) { FarmName = name; } // 设置 FarmName
    std::string getFarmName() const { return FarmName; };  // 获取 FarmName

    //与其他元素交互相关
    //种植 砍树 挖矿 钓鱼 当需要判断玩家目前所拿物品，调用get函数即可
    void setHeldTool(int tool) { Heldtool = tool; } // 设置当前持有的工具
    void setHeldSeed(int seed) { Heldseed = seed; } // 设置当前持有的种子
    int getHeldTool() { return Heldtool; } // 获取当前持有的工具
    int getHeldSeed() { return Heldseed; } // 获取当前持有的种子
    void setPrestige(int add) { prestige += add; } //增加声望值
    int getPrestige() { return prestige ; } //获取声望值
    //玩家拥有财产相关
    void setMoney(const int newmoney) { money += newmoney; }
    int getMoney() const { return money; }

    //技能树相关
    // 技能树等级
    double agricultureLevel=1;
    double miningLevel=1;
    double fishingLevel=1;
    double cookingLevel=1;
    void upgradeSkillTree(int ID, double exp); // 增加经验值，并可能升级技能树

    //先不改
    std::string PlayerName;
    std::string FarmName;
   
private:
    //玩家等级
    double maxlevel = 4;//每一个技能方向等级上限
    //用于判断是否满级，还未添加入口函数，四个都满级了才能开启商店
    bool a_level_max;
    bool m_level_max;
    bool f_level_max;
    bool c_level_max;
    //玩家金币
    int money;
    //玩家声望
    int prestige = 10;
    std::vector<int> agricultureItems;  // 农业技能对应的物品ID集合
    std::vector<int> miningItems;       // 采矿技能对应的物品ID集合
    std::vector<int> fishingItems;      // 钓鱼技能对应的物品ID集合
    std::vector<int> cookingItems;      // 烹饪技能对应的物品ID集合
    //玩家所持物品
	 int Heldtool;
    int Heldseed;
    bool if_holdfeiliao; 

};

#endif // PLAYER_H
