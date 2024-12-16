#include "cocos2d.h"

class Toolbar : public cocos2d::Layer {
public:
    Toolbar() : currentToolIndex(0) {}
    ~Toolbar() {}

    static Toolbar* create();
    bool init();

    void createToolButton(const std::string& label, float x, float y, int index);

    // ������߰�ťʱ���л���ǰ����
    void onToolButtonClicked(int index);

    // ���µ�ǰѡ��Ĺ���
    void updateCurrentTool();

    // �������¼����л�����
    void onMouseScroll(cocos2d::Event* event);

private:
    int currentToolIndex;  // ��ǰ���еĹ�������
};
#pragma once
