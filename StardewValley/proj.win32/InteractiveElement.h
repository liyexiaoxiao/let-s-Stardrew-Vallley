#pragma once
#include "cocos2d.h"
//�йؽ���Ԫ�صĲ��� ���ڷ������ִ�н�Ϊ���򲻷��ڸ��ļ���
//Ŀǰ���ڣ����������--ʵ�ֲ�ͬ����Ĳ�ͬ����
class InteractiveElement {
public:
    virtual ~InteractiveElement() {}

    // ���麯�������н���Ԫ�ض�����ʵ�ִ˺���
    virtual void onClick() = 0;
    // ���ذ�Χ�У������������д�˷������Զ���ȡ��Χ��
    virtual cocos2d::Rect getBoundingBox() const = 0;
};
