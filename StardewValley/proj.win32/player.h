#pragma once
//ĿǰΪgyx11/30����ʹ�ã�����
#ifndef PLAYER_H
#define PLAYER_H
#include "cocos2d.h"




//ÿ����Ʒ��������Ϣ
enum class ItemID {
    T_Axe = 1,       // ��ͷ
    T_Hoe = 2,      // ��ͷ
    T_WateringCan = 3, // ��ˮ��
    T_Pickaxe = 4,//����
    T_Sickle = 5,//����
    T_Fish = 6,

    A_Seed = 7,
    A_Seed1=8,
    A_Seed2,
    A_Seed3,
    A_Seed4,
    C_dish1,C_dish2,C_dish3,C_dish4,
    A_wood,
    F_fish1, F_fish2, F_fish3, F_fish4
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
    void setPrestige(int add) { prestige += add; } //��������ֵ
    int getPrestige() { return prestige ; } //��ȡ����ֵ
    //���ӵ�вƲ����
    void setMoney(const int newmoney) { money += newmoney; }
    int getMoney() const { return money; }

    //���������
    // �������ȼ�
    double agricultureLevel=1;
    double miningLevel=1;
    double fishingLevel=1;
    double cookingLevel=1;
    void upgradeSkillTree(int ID, double exp); // ���Ӿ���ֵ������������������

    //�Ȳ���
    std::string PlayerName;
    std::string FarmName;
    int Heldtool = 1;
    //Ϊ�˲�����ʱ��˲���=1ʱ���ų�ͷ������2ʱ���Ž�ˮ��������3ʱ���Ÿ�ͷ������4ʱ�������
    int Heldseed = 1;
    //Ϊ�˲�����ʱ��˲���=1ʱ���ŷ�������ӣ�����2ʱ������ݮ���ӣ�����3ʱ�����Ϲ����ӣ�����4ʱ����С������
    
    bool if_holdfeiliao = 0;
private:
    //��ҵȼ�
    double maxlevel = 4;//ÿһ�����ܷ���ȼ�����
    //�����ж��Ƿ���������δ�����ں������ĸ��������˲��ܿ����̵�
    bool a_level_max;
    bool m_level_max;
    bool f_level_max;
    bool c_level_max;
    //��ҽ��
    int money;
    //�������
    int prestige = 10;
    std::vector<int> agricultureItems;  // ũҵ���ܶ�Ӧ����ƷID����
    std::vector<int> miningItems;       // �ɿ��ܶ�Ӧ����ƷID����
    std::vector<int> fishingItems;      // ���㼼�ܶ�Ӧ����ƷID����
    std::vector<int> cookingItems;      // ��⿼��ܶ�Ӧ����ƷID����

};

#endif // PLAYER_H
