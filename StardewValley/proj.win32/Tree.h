//ĿǰΪgyx11/30����ʹ��
#pragma once

#include "InteractiveElement.h" //����ʽ���
#include "cocos2d.h"

class Tree : public cocos2d::Sprite,public InteractiveElement {
public:
    Tree();
    ~Tree();
    //��ʼ��
    static Tree* create();
    bool init();

    //��ع���
    void removeTree(); // �Ƴ��Ӳ�
    bool isRemoved() const { return removed; }

    // ʵ�� InteractiveElement �� onClick ����
    void onClick() override {
        removeTree();
    }
    //���ð�Χ�н��ж�̬�ж�
    cocos2d::Rect getBoundingBox() const override;

private:
    bool removed; // ����Ӳ��Ƿ��ѱ��Ƴ�
};

