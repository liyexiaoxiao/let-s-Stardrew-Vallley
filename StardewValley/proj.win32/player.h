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

    A_Seed = 7,
    A_Seed1=8,
    A_Seed2,
    A_Seed3,
    A_Seed4,
    C_dish1,C_dish2,C_dish3,C_dish4,
    A_wood,
    F_fish1, F_fish2, F_fish3, F_fish4
    // 可以继续添加其他物品类型
};
//物品的类别属性
enum class ItemCategory {
    T,     // 工具
    A,     // 农产品
    M,     // 矿产
    F,      // 渔业
    C       //菜谱
    // 可以继续添加其他类别
};


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
    int Heldtool = 1;
    //为了测试暂时设此参数=1时拿着锄头，等于2时拿着浇水壶，等于3时拿着斧头，等于4时拿着鱼竿
    int Heldseed = 1;
    //为了测试暂时设此参数=1时拿着防风草种子，等于2时拿着树莓种子，等于3时拿着南瓜种子，等于4时拿着小麦种子
    
    bool if_holdfeiliao = 0;
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

};

#endif // PLAYER_H
