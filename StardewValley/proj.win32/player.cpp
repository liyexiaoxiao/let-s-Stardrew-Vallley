//目前为gyx11/30测试使用！！！
#include "Player.h"

USING_NS_CC;


//玩家相关
Player::Player() : money(500), PlayerName("Dave") ,FarmName("Dave's Farm"), a_level_max(false), m_level_max(false) , f_level_max(false) , c_level_max(false) {
    // 初始化初始解锁的物品
    items[ItemID::T_Hoe] = { true, 1, ItemID::T_Hoe,ItemCategory::T };
    items[ItemID::T_WateringCan] = { true, 1, ItemID::T_WateringCan,ItemCategory::T };
    items[ItemID::A_Seed1] = { true, 5, ItemID::A_Seed1,ItemCategory::A };//初始只有一种种子
    items[ItemID::T_Axe] = { true, 1, ItemID::T_Axe,ItemCategory::T };
    items[ItemID::C_dish1] = { true, 1, ItemID::C_dish1,ItemCategory::C };
   
    //初始化未解锁的
    items[ItemID::A_Seed2] = { false, 5, ItemID::A_Seed1,ItemCategory::A };
    items[ItemID::A_Seed3] = { false, 5, ItemID::A_Seed1,ItemCategory::A };
    items[ItemID::A_Seed4] = { false, 5, ItemID::A_Seed1,ItemCategory::A };
    items[ItemID::C_dish2] = { false, 1, ItemID::C_dish2,ItemCategory::C };
    items[ItemID::C_dish3] = { false, 1, ItemID::C_dish3,ItemCategory::C };
    items[ItemID::C_dish4] = { false, 1, ItemID::C_dish4,ItemCategory::C };
    //初始化每一个技能方向的等级逻辑--示例
    //等级2
    agricultureUnlockItems[2] = { ItemID::A_Seed2};//南瓜 2级 
    cookingUnlockItems[2] = { ItemID::C_dish2 };
    //等级3
    agricultureUnlockItems[3] = { ItemID::A_Seed3,ItemID::A_Seed4 };//xx xx 三级
    cookingUnlockItems[3] = { ItemID::C_dish3};
    //等级四--满级
    cookingUnlockItems[4] = { ItemID::C_dish4};
} // 初始化玩家默认属性

Player::~Player() {}

Player* Player::create(const std::string& filename) {
    Player* ret = new Player();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Player::init(const std::string& filename) {
    if (!Sprite::init()) {
        return false;
    }

    // 设置玩家角色的图像
    this->initWithFile(filename);
    this->setVisible(true);

    return true;
}


//玩家与物品储存相关
void Player::unlockItem(ItemID itemId) {
    auto it = items.find(itemId);
    if (it != items.end()) {
        it->second.unlocked = true; // 解锁物品
    }
    else {
        // 如果物品不存在，可以选择添加新的物品--没什么用处
        // 例如，这里可以根据itemId枚举值来初始化新物品的信息
        ItemInfo newItem{ true, 0, itemId }; // 默认解锁，数量为0
        items[itemId] = newItem;
    }
}
void Player::addItem(ItemID itemId, int amount) {
    auto it = items.find(itemId);
    if (it != items.end()) {
        it->second.count += amount; // 增加物品数量
    }
    else {
        // 如果物品不存在，可以选择添加新的物品--没什么用处
        // 例如，这里可以根据itemId枚举值来初始化新物品的信息
        ItemInfo newItem{ true, amount, itemId }; // 默认解锁，初始数量为传入的数量
        items[itemId] = newItem;
    }
}
//减少物品数量
void Player::deleteItem(ItemID itemId, int amount) {
    auto it = items.find(itemId);
    if (it != items.end()&& it->second.count!=0) {
        it->second.count -= amount; // 减少物品数量
    }
}


 //玩家控制技能树逻辑相关
 void Player::upgradeSkillTree(ItemCategory category, double exp) {
     switch (category) {
     case ItemCategory::A:
         agricultureLevel += exp / 2; // 假设每100经验值增加1级
         agricultureLevel = std::min(agricultureLevel, maxlevel);
         if (agricultureLevel == maxlevel)
             a_level_max = true;
         unlockItemsForLevel(ItemCategory::A, agricultureLevel);
         break;
     case ItemCategory::M:
         miningLevel += exp / 100;
         miningLevel = std::min(miningLevel, maxlevel);
         if (miningLevel == maxlevel)
             m_level_max = true;
         unlockItemsForLevel(ItemCategory::M, miningLevel);
         break;
     case ItemCategory::F:
         fishingLevel += exp / 100;
         fishingLevel = std::min(fishingLevel, maxlevel);
         if (fishingLevel == maxlevel)
             f_level_max = true;
         unlockItemsForLevel(ItemCategory::F, fishingLevel);
         break;
     case ItemCategory::C:
         cookingLevel += exp / 100;
         cookingLevel = std::min(cookingLevel, maxlevel);
         if (cookingLevel == maxlevel)
             c_level_max = true;
         unlockItemsForLevel(ItemCategory::C, cookingLevel);
         break;
     }
 }
 //控制随着技能树升级物品的解锁
 void Player::unlockItemsForLevel(ItemCategory category, int targetLevel) {
     std::map<int, std::vector<ItemID>>& unlockItemsMap = getItemsMapByCategory(category);
     auto it = unlockItemsMap.find(targetLevel);
     if (it != unlockItemsMap.end()) {
         for (auto itemId : it->second) {
             unlockItem(itemId);
         }
     }
 }
 std::map<int, std::vector<ItemID>>& Player::getItemsMapByCategory(ItemCategory category) {
     switch (category) {
     case ItemCategory::A: return agricultureUnlockItems;
     case ItemCategory::M: return miningUnlockItems;
     case ItemCategory::F: return fishingUnlockItems;
     case ItemCategory::C: return cookingUnlockItems;
     default: return agricultureUnlockItems; // 默认返回农业解锁物品
     }
 }