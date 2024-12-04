#pragma once
//��һ��NPC��λ��ũ����ͼ����һ��ũ��
#include "Resident.h"
#include "InteractiveElement.h" //����ʽ���

class Farmer : public Resident,public InteractiveElement{
private:
    //�������
    cocos2d::Sprite* sprite;  // ��ʾũ��ͼ��ľ���
    cocos2d::Rect boundingBox;  // ��ǰũ��İ�Χ�У�ͨ��ũ���ڵ�ͼ�ϵ�λ��ֱ��д��
    // �����صĳ�Ա����
    cocos2d::Label* nameLabel;
    cocos2d::Label* professionLabel;
    cocos2d::Label* romanceLabel;
    cocos2d::Label* friendshipLabel;
    cocos2d::Label* taskLabel;
public:
    Farmer();  // Ĭ�Ϲ��캯��
    ~Farmer();

    // ��ʾ NPC ���
    void showInfoPanel();  // ��ʾ��Ϣ���
    // ʵ�� InteractiveElement �� onClick ����
    void onClick() override {
        showInfoPanel();
    }
    //���ð�Χ�н��ж�̬�ж�
    cocos2d::Rect getBoundingBox() const override;
 
    // ũ�����е�������Ϊ
    void offerTask();  // ũ�������
};