//ĿǰΪgyx11/30����ʹ�ã�����
#include "Player.h"

USING_NS_CC;


//������
Player::Player() : money(500), PlayerName("Dave") ,FarmName("Dave's Farm"), a_level_max(false), m_level_max(false) , f_level_max(false) , c_level_max(false) {
    // ��ʼ����ʼ��������Ʒ
    items[ItemID::T_Hoe] = { true, 1, ItemID::T_Hoe,ItemCategory::T };
    items[ItemID::T_WateringCan] = { true, 1, ItemID::T_WateringCan,ItemCategory::T };
    items[ItemID::A_Seed1] = { true, 5, ItemID::A_Seed1,ItemCategory::A };//��ʼֻ��һ������
    items[ItemID::T_Axe] = { true, 1, ItemID::T_Axe,ItemCategory::T };
    items[ItemID::C_dish1] = { true, 1, ItemID::C_dish1,ItemCategory::C };
   
    //��ʼ��δ������
    items[ItemID::A_Seed2] = { false, 5, ItemID::A_Seed1,ItemCategory::A };
    items[ItemID::A_Seed3] = { false, 5, ItemID::A_Seed1,ItemCategory::A };
    items[ItemID::A_Seed4] = { false, 5, ItemID::A_Seed1,ItemCategory::A };
    items[ItemID::C_dish2] = { false, 1, ItemID::C_dish2,ItemCategory::C };
    items[ItemID::C_dish3] = { false, 1, ItemID::C_dish3,ItemCategory::C };
    items[ItemID::C_dish4] = { false, 1, ItemID::C_dish4,ItemCategory::C };
    //��ʼ��ÿһ�����ܷ���ĵȼ��߼�--ʾ��
    //�ȼ�2
    agricultureUnlockItems[2] = { ItemID::A_Seed2};//�Ϲ� 2�� 
    cookingUnlockItems[2] = { ItemID::C_dish2 };
    //�ȼ�3
    agricultureUnlockItems[3] = { ItemID::A_Seed3,ItemID::A_Seed4 };//xx xx ����
    cookingUnlockItems[3] = { ItemID::C_dish3};
    //�ȼ���--����
    cookingUnlockItems[4] = { ItemID::C_dish4};
} // ��ʼ�����Ĭ������

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

    // ������ҽ�ɫ��ͼ��
    this->initWithFile(filename);
    this->setVisible(true);

    return true;
}


//�������Ʒ�������
void Player::unlockItem(ItemID itemId) {
    auto it = items.find(itemId);
    if (it != items.end()) {
        it->second.unlocked = true; // ������Ʒ
    }
    else {
        // �����Ʒ�����ڣ�����ѡ������µ���Ʒ--ûʲô�ô�
        // ���磬������Ը���itemIdö��ֵ����ʼ������Ʒ����Ϣ
        ItemInfo newItem{ true, 0, itemId }; // Ĭ�Ͻ���������Ϊ0
        items[itemId] = newItem;
    }
}
void Player::addItem(ItemID itemId, int amount) {
    auto it = items.find(itemId);
    if (it != items.end()) {
        it->second.count += amount; // ������Ʒ����
    }
    else {
        // �����Ʒ�����ڣ�����ѡ������µ���Ʒ--ûʲô�ô�
        // ���磬������Ը���itemIdö��ֵ����ʼ������Ʒ����Ϣ
        ItemInfo newItem{ true, amount, itemId }; // Ĭ�Ͻ�������ʼ����Ϊ���������
        items[itemId] = newItem;
    }
}
//������Ʒ����
void Player::deleteItem(ItemID itemId, int amount) {
    auto it = items.find(itemId);
    if (it != items.end()&& it->second.count!=0) {
        it->second.count -= amount; // ������Ʒ����
    }
}


 //��ҿ��Ƽ������߼����
 void Player::upgradeSkillTree(ItemCategory category, double exp) {
     switch (category) {
     case ItemCategory::A:
         agricultureLevel += exp / 2; // ����ÿ100����ֵ����1��
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
 //�������ż�����������Ʒ�Ľ���
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
     default: return agricultureUnlockItems; // Ĭ�Ϸ���ũҵ������Ʒ
     }
 }