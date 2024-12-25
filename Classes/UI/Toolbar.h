#include "cocos2d.h"
#include "ui/CocosGUI.h"  // �������ͷ�ļ���ʹ�� Button ��


class Toolbar : public cocos2d::Layer {
public:
    Toolbar() : currentToolIndex(1), markerSprite(nullptr), markerStartX(200), markerY(100) {}
    ~Toolbar() {}

    bool init();
    // ��ȡΨһ��ʵ��
    static Toolbar* getInstance() {
        if (!instance) {
            instance = new Toolbar();
            instance->init();  // ȷ����ʼ��
            instance->autorelease();  // �Զ������ڴ�
        }
        return instance;
    }
    // ����ʵ��
    static void destroyInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
    //����������
    static Toolbar* create() {
        Toolbar* ret = new Toolbar();
        if (ret && ret->init()) {
            ret->autorelease();  // ����ɹ�������ʵ�����Զ������ڴ�
            return ret;
        }
        else {
            delete ret;
            return nullptr;
        }
    }
    //���¹���������ͼ��
    void updateToolIcons();
    // �������¼�����
    void onMouseScroll(cocos2d::Event* event);
    void createSeedSelectionPanel();
    void onSeedSelected(cocos2d::Ref* sender, int seedType);
    void closeSeedPanel(cocos2d::Ref* sender);
private:
    int currentToolIndex;  // ��ǰ���еĹ�������
    cocos2d::ui::Button* SeedButton;       //���Ӱ�ť
    cocos2d::Sprite* markerSprite;        // �µ�ͼƬ (ָʾ���)
    float markerStartX;                   // ��ͼƬ�ĳ�ʼ x ����
    float markerY;                        // ��ͼƬ�� y ����
    void updateMarkerPosition();          // ������ͼƬ��λ��
    static Toolbar* instance;  // ��̬ʵ��ָ��
    cocos2d::Sprite* Axe;
    cocos2d::Sprite* Hoe;
    cocos2d::Sprite* Watering_Can;
    cocos2d::Sprite* Pickaxe;
    cocos2d::Sprite* Sickle;
    cocos2d::Sprite* Fish;
};
#pragma once