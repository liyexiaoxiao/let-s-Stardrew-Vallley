#pragma once
//ĿǰΪgyx11/30����ʹ�ã�����
#ifndef PLAYER_H
#define PLAYER_H
#include "cocos2d.h"


//Ϊ��֤ÿһ��player������Լ������̽��ȣ������������ļ���ʵ��ʵ�ֶ���Ʒ�Ĺ���
//ÿ����Ʒ��������Ϣ
enum class ItemID {
    T_Hoe = 1,      // ��ͷ
    T_WateringCan = 2, // ��ˮ��
    T_Axe = 3,       // ��ͷ
    A_Seed1 = 4,    // ����1
    A_Seed2 = 5,
    A_Seed3 = 6,
    A_Seed4 = 7,
    C_dish1,C_dish2,C_dish3,C_dish4,
    A_wood
    // ���Լ������������Ʒ����
};
//��Ʒ���������
enum class ItemCategory {
    T,     // ����
    A,     // ũ��Ʒ
    M,     // ���
    F,      // ��ҵ
    C       //����
    // ���Լ�������������
};

struct ItemInfo {
    bool unlocked; // �Ƿ����
    int count;     // ����
    ItemID id;       // ��Ʒ��ΨһID��ö�����ͣ�,ע����д��ʽ
    ItemCategory category;//��Ʒ���࣬�������ɺÿ���UI
};

class Player : public cocos2d::Sprite {
public:
    Player();  // ���캯��
    ~Player(); // ��������

    static Player* create(const std::string& filename); // ������Ҷ�
    bool init(const std::string& filename); // ��ʼ����Ҷ���
    void setPlayerName(const std::string& name) { PlayerName = name; } // ���� playername
    std::string getPlayerName() const { return PlayerName; };  // ��ȡ playername
    void setFarmName(const std::string& name) { FarmName = name; } // ���� FarmName
    std::string getFarmName() const { return FarmName; };  // ��ȡ FarmName

    //������Ԫ�ؽ������
    //��ֲ ���� �ڿ� ���� ����Ҫ�ж����Ŀǰ������Ʒ������get��������
    void setHeldTool(int tool) { Heldtool = tool; } // ���õ�ǰ���еĹ���
    void setHeldSeed(int seed) { Heldseed = seed; } // ���õ�ǰ���е�����
    int getHeldTool() { return Heldtool; } // ��ȡ��ǰ���еĹ���
    int getHeldSeed() { return Heldseed; } // ��ȡ��ǰ���е�����

    //���ӵ�вƲ����
    void setMoney(const int newmoney) { money = newmoney; }
    int getMoney() const { return money; }

    //�洢������Ʒ��Ϣ���
    void unlockItem(ItemID itemId);
    void addItem(ItemID itemId, int amount);
    void deleteItem(ItemID itemId, int amount);

    // ��ȡ��������Ʒ��Ϣ
    //����Ʒ�������� T-A-M-F--�����ֿ�UI���պ���˳������
//����category
    std::vector<std::pair<ItemID, ItemInfo>> getSortedItems() const {
        std::vector<std::pair<ItemID, ItemInfo>> sortedItems(items.begin(), items.end());
        std::sort(sortedItems.begin(), sortedItems.end(), [](const std::pair<ItemID, ItemInfo>& a, const std::pair<ItemID, ItemInfo>& b) {
            return a.second.category < b.second.category;
            });
        return sortedItems;
    }
    //��������ȡ����Ʒ��Ϣ
    std::vector<std::pair<ItemID, ItemInfo>> getItemsInfo() const {
        std::vector<std::pair<ItemID, ItemInfo>> itemsInfo;
        for (const auto& itemPair : items) {
            itemsInfo.emplace_back(itemPair.first, itemPair.second);
        }
        return itemsInfo;
    }

    //���������
    // �������ȼ�
    int agricultureLevel;
    int miningLevel;
    int fishingLevel;
    int cookingLevel;
    void upgradeSkillTree(ItemCategory category, int exp); // ���Ӿ���ֵ������������������
    void unlockItemsForLevel(ItemCategory category, int targetLevel); // �����ض��ȼ�����Ʒ
    std::map<int, std::vector<ItemID>>& getItemsMapByCategory(ItemCategory category);

    //�Ȳ���
    std::string PlayerName;
    std::string FarmName;
    int Heldtool = 0;
    //Ϊ�˲�����ʱ��˲���=1ʱ���ų�ͷ������2ʱ���Ž�ˮ��������3ʱ���Ÿ�ͷ������4ʱ�������
    int Heldseed = 0;
    //Ϊ�˲�����ʱ��˲���=1ʱ���ŷ�������ӣ�����2ʱ������ݮ���ӣ�����3ʱ�����Ϲ����ӣ�����4ʱ����С������

private:
    //��ҵȼ�
    int maxlevel = 4;//ÿһ�����ܷ���ȼ�����
    //�����ж��Ƿ���������δ�����ں������ĸ��������˲��ܿ����̵�
    bool a_level_max;
    bool m_level_max;
    bool f_level_max;
    bool c_level_max;
    //��ҽ��
    int money;
    //�����Ʒ
    std::unordered_map<ItemID, ItemInfo> items; // �洢��Ʒ��Ϣ��ӳ��

    // ÿ���ȼ���������Ʒ
    std::map<int, std::vector<ItemID>> agricultureUnlockItems;//int������ ��Ʒ int����
    std::map<int, std::vector<ItemID>> miningUnlockItems;
    std::map<int, std::vector<ItemID>> fishingUnlockItems;
    std::map<int, std::vector<ItemID>> cookingUnlockItems;

};

#endif // PLAYER_H
