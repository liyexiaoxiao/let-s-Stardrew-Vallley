#pragma once
//目前为gyx11/30测试使用！！！
#ifndef PLAYER_H
#define PLAYER_H
#include "cocos2d.h"


//为保证每一个player管理好自己的流程进度，我们在人物文件中实现实现对物品的管理
//每个物品包含的信息
enum class ItemID {
    T_Axe = 1,       // 斧头
    T_Hoe = 2,      // 锄头
    T_WateringCan = 3, // 浇水壶
    T_Pickaxe = 4,//镐子
    T_Sickle = 5,//镰刀
    T_Fish = 6,//钓鱼竿

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

struct ItemInfo {
    bool unlocked; // 是否解锁
    int count;     // 数量
    ItemID id;       // 物品的唯一ID（枚举类型）,注意书写方式
    ItemCategory category;//物品种类，便于生成好看的UI
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

    //玩家拥有财产相关
    void setMoney(const int newmoney) { money = newmoney; }
    int getMoney() const { return money; }

    //存储解锁物品信息相关
    void unlockItem(ItemID itemId);
    void addItem(ItemID itemId, int amount);
    void deleteItem(ItemID itemId, int amount);

    // 获取排序后的物品信息
    //对物品进行排序 T-A-M-F--辅助仓库UI按照合理顺序生成
//基于category
    std::vector<std::pair<ItemID, ItemInfo>> getSortedItems() const {
        std::vector<std::pair<ItemID, ItemInfo>> sortedItems(items.begin(), items.end());
        std::sort(sortedItems.begin(), sortedItems.end(), [](const std::pair<ItemID, ItemInfo>& a, const std::pair<ItemID, ItemInfo>& b) {
            return a.second.category < b.second.category;
            });
        return sortedItems;
    }
    //供给外界获取到物品信息
    std::vector<std::pair<ItemID, ItemInfo>> getItemsInfo() const {
        std::vector<std::pair<ItemID, ItemInfo>> itemsInfo;
        for (const auto& itemPair : items) {
            itemsInfo.emplace_back(itemPair.first, itemPair.second);
        }
        return itemsInfo;
    }

    //技能树相关
    // 技能树等级
    double agricultureLevel=1;
    double miningLevel=1;
    double fishingLevel=1;
    double cookingLevel=1;
    void upgradeSkillTree(ItemCategory category, double exp); // 增加经验值，并可能升级技能树
    void unlockItemsForLevel(ItemCategory category, int targetLevel); // 解锁特定等级的物品
    std::map<int, std::vector<ItemID>>& getItemsMapByCategory(ItemCategory category);

    //先不改
    std::string PlayerName;
    std::string FarmName;
    int Heldtool = 1;
    //此参数=1时拿着斧头，等于2时锄头，等于3时浇水壶，等于4时镐子，等于5时镰刀，等于6时钓鱼竿
    int Heldseed = 2;
    //设此参数=1时拿着防风草种子，等于2时拿着树莓种子，等于3时拿着南瓜种子，等于4时拿着小麦种子
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
    //玩家物品
    std::unordered_map<ItemID, ItemInfo> items; // 存储物品信息的映射

    // 每个等级解锁的物品
    std::map<int, std::vector<ItemID>> agricultureUnlockItems;//int级解锁 物品 int个数
    std::map<int, std::vector<ItemID>> miningUnlockItems;
    std::map<int, std::vector<ItemID>> fishingUnlockItems;
    std::map<int, std::vector<ItemID>> cookingUnlockItems;

};

#endif // PLAYER_H
