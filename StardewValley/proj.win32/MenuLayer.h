#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "player.h"
class MenuLayer : public cocos2d::Layer {
public:
    MenuLayer();
    ~MenuLayer();

    // �����˵�����
    bool init();
    static MenuLayer* create();

    cocos2d::Layer* MenuLayer::createPanel(int panelIndex);
    // �л��˵���ʾ״̬
    void toggleVisibility();
    void createPanels(); //�����ĸ����
    void showPanel(int index);
private:
    bool isVisible;  // ���Ʋ˵���ʾ״̬
    cocos2d::Sprite* MenuBG;
    cocos2d::Layer* panel1;  // ���1��ũ����Ϣ
    cocos2d::Layer* panel2;  // ���2���ֿ�洢
    cocos2d::Layer* panel3;  // ���3�����＼��
    cocos2d::Layer* panel4;  // ���4���˳���Ϸ
};

#endif  // __MENU_LAYER_H__

