#pragma once
#ifndef __REPAIRBUILDING_H__
#define __REPAIRBUILDING_H__

#include "cocos2d.h"
#include "InteractiveElement.h" //����ʽ���

class RepairBuilding : public cocos2d::Sprite, public InteractiveElement {
public:
    RepairBuilding(const std::string& brokenImage, const std::string& fixedImage);  // ���캯������·��
    ~RepairBuilding();

    static RepairBuilding* create(const std::string& brokenImage, const std::string& fixedImage);  // ��̬��������
    bool init();  // ��ʼ������

    void startRepair();  // ��ʼ�޸�
    void completeRepair();  // ����޸�

    // ʵ�� InteractiveElement �� onClick ����
    int onClick() override {
        // �ڵ��ʱ���Դ�����΢�Ŵ󲢻ָ���Ч��
        this->runAction(cocos2d::Sequence::create(
            cocos2d::ScaleTo::create(0.1f, 1.1f),  // �Ŵ� 10%
            cocos2d::ScaleTo::create(0.1f, 1.0f),  // �ָ���ԭ��С
            nullptr));  // �������������ִ��
        if (isready) startRepair();
        return 2;//��δ�涨
    }
    //���ð�Χ�н��ж�̬�ж�
    cocos2d::Rect getBoundingBox() const override;

    bool isready = true;//�����Ƿ��㹻�޸�

private:
    std::string brokenImage;  // ������ͼ��·��
    std::string fixedImage;  // �޸���Ľ���ͼ��·��
    bool isRepairing;  // �Ƿ������޸�
    bool isRepaired;//�Ƿ��Ѿ��޸�
    float repairProgress;  // �޸�����
    float repairTime;  // �޸�ʱ��

    cocos2d::ProgressTimer* repairProgressBar;  // ������
    // �������ܵĳ�Ա����
};

#endif // __REPAIRBUILDING_H__

