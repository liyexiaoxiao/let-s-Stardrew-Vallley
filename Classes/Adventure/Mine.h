#pragma once
#ifndef MINE_H
#define MINE_H

// ȷ����������������ͬ��������ͷ�ļ���ͻ
#pragma once
#include "InteractiveElement.h" //����ʽ���
#include "cocos2d.h"

class Mine : public cocos2d::Sprite, public InteractiveElement {
public:
    Mine();
    ~Mine();
    // ��ʼ��
    static Mine* create();
    bool init();

    // ��ع���
    void removeMine(); // �Ƴ�����
    bool isRemoved() const { return removed; }
    // ÿ�ո���
    void reset();
    // ʵ�� InteractiveElement �� onClick ����
    int onClick() override;

    // ���ð�Χ�н��ж�̬�ж�
    cocos2d::Rect getBoundingBox() const override;

private:
    bool removed; // ��ǿ����Ƿ��ѱ��Ƴ�
    // ���ѡ��Ŀ���ͼƬ·��
    std::vector<std::string> mineImages = {
        "photo/Adventure/mine1.png",  // ��һ�ֿ���ͼ��
        "photo/Adventure/mine2.png",  // �ڶ��ֿ���ͼ��
        "photo/Adventure/mine3.png"   // �����ֿ���ͼ��
    };
};

#endif // MINE_H