#include "Farmer.h"
using namespace cocos2d;

Farmer::Farmer() {
    name = "John Doe";
    profession = "Farmer";
    sprite = this;
    this->initWithFile("photo/Character/Resident1.png");  // ����ũ���ͼ��
    
    // �������� UI Ԫ���Լ�����ʼ��
    nameLabel = cocos2d::Label::createWithSystemFont("Name: ", "Arial", 24);
    this->addChild(nameLabel);
    professionLabel = cocos2d::Label::createWithSystemFont("Profession: ", "Arial", 24);
    this->addChild(professionLabel);
    romanceLabel = cocos2d::Label::createWithSystemFont("Romance: 0", "Arial", 24);
    this->addChild(romanceLabel);
    friendshipLabel = cocos2d::Label::createWithSystemFont("Friendship: 0", "Arial", 24);
    this->addChild(friendshipLabel);
    taskLabel = cocos2d::Label::createWithSystemFont("Task: ", "Arial", 24);
    this->addChild(taskLabel);
    // ���ó�ʼλ�ã����磬ȷ�����ǲ�����ʾ����Ļ�ϣ���������Ϊ͸����
    nameLabel->setVisible(false);
    professionLabel->setVisible(false);
    romanceLabel->setVisible(false);
    friendshipLabel->setVisible(false);
    taskLabel->setVisible(false);
}

Farmer::~Farmer() {}

void Farmer::offerTask() {
    CCLOG("%s is offering a task", name.c_str());
    // �����ﴴ��ũ��������߼�
}

//�������
void Farmer::showInfoPanel() {
    nameLabel->setVisible(true);
    professionLabel->setVisible(true);
    romanceLabel->setVisible(true);
    friendshipLabel->setVisible(true);
    taskLabel->setVisible(true);
    // ��������ϵ���Ϣ
    nameLabel->setString("Name: " + name);
    professionLabel->setString("Profession: " + profession);
    romanceLabel->setString("Romance: " + std::to_string(romance));
    friendshipLabel->setString("Friendship: " + std::to_string(friendship));

    // ��������������������Ϣ
    if (currentTask) {
        //taskLabel->setString("Task: " + currentTask->getTaskName());
    }
}
cocos2d::Rect Farmer::getBoundingBox() const {
    // ���ظ��º�İ�Χ��
    return cocos2d::Rect(1550, 1815, 28, 58);
}

