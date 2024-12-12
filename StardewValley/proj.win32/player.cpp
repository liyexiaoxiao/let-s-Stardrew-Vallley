//ĿǰΪgyx11/30����ʹ�ã�����
#include "Player.h"

USING_NS_CC;


//������
Player::Player() : money(500), PlayerName("Dave") ,FarmName("Dave's Farm") {
    // ��ʼ����ʼ��������Ʒ
    items[ItemID::T_Hoe] = { true, 1, ItemID::T_Hoe,ItemCategory::T };
    items[ItemID::T_WateringCan] = { true, 1, ItemID::T_WateringCan,ItemCategory::T };
    items[ItemID::A_Seed] = { true, 5, ItemID::A_Seed,ItemCategory::A };
    items[ItemID::T_Axe] = { true, 1, ItemID::T_Axe,ItemCategory::T };

    //��ʼ��ÿһ�����ܷ���ĵȼ��߼�--ʾ��
    agricultureUnlockItems[2] = { ItemID::T_Hoe };
    agricultureUnlockItems[3] = { ItemID::T_WateringCan };
    miningUnlockItems[2] = { ItemID::T_Axe };
    miningUnlockItems[3] = { ItemID::A_Seed };
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
    if (it != items.end()&& it->second.count��=0) {
        it->second.count -= amount; // ������Ʒ����
    }
}


 //��ҿ��Ƽ������߼����
 void Player::upgradeSkillTree(ItemCategory category, int exp) {
     switch (category) {
     case ItemCategory::A:
         agricultureLevel += exp / 100; // ����ÿ100����ֵ����1��
         unlockItemsForLevel(ItemCategory::A, agricultureLevel);
         break;
     case ItemCategory::M:
         miningLevel += exp / 100;
         unlockItemsForLevel(ItemCategory::M, miningLevel);
         break;
     case ItemCategory::F:
         fishingLevel += exp / 100;
         unlockItemsForLevel(ItemCategory::F, fishingLevel);
         break;
     case ItemCategory::C:
         cookingLevel += exp / 100;
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