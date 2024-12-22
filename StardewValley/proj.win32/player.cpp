//ĿǰΪgyx11/30����ʹ�ã�����
#include "Player.h"
#include"vector"
USING_NS_CC;


//������
Player::Player() : money(500), PlayerName("Dave") ,FarmName("Dave's Farm"), a_level_max(false), m_level_max(false) , f_level_max(false) , c_level_max(false) {
    agricultureItems = {0};
    miningItems = { 26 };     
    fishingItems = { 15,16,17,18 };    
    cookingItems = { 4001, 4002, 4003 };   
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


 //��ҿ��Ƽ������߼����
 void Player::upgradeSkillTree(int ID,double exp) {
     if (std::find(agricultureItems.begin(), agricultureItems.end(), ID) != agricultureItems.end()) {
         agricultureLevel += exp / 4; // ����ÿ100����ֵ����1��
         agricultureLevel = std::min(agricultureLevel, maxlevel);
         if (agricultureLevel == maxlevel)
             a_level_max = true;
     }
     else if (std::find(miningItems.begin(), miningItems.end(), ID) != miningItems.end()) {
         miningLevel += exp / 100;
         miningLevel = std::min(miningLevel, maxlevel);
         if (miningLevel == maxlevel)
             m_level_max = true;
     }
     else if (std::find(fishingItems.begin(), fishingItems.end(), ID) != fishingItems.end()) {
         fishingLevel += exp / 100;
         fishingLevel = std::min(fishingLevel, maxlevel);
         if (fishingLevel == maxlevel)
             f_level_max = true;
     }
     else if (std::find(cookingItems.begin(), cookingItems.end(), ID) != cookingItems.end()) {
         cookingLevel += exp / 100;
         cookingLevel = std::min(cookingLevel, maxlevel);
         if (cookingLevel == maxlevel)
             c_level_max = true;
     }
 }
