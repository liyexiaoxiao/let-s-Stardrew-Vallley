#pragma once
//�����������ð�ճ���
//������ͼ���š���ͼ�ƶ��������ƶ�������������Ʒ�Ľ����ӿ�
#ifndef __EXPLORE_SCENE_H__
#define __EXPLORE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resident.h"   //NPC����
#include "player.h"    //�����
#include "Farmer.h"    //ũ����
#include "NPCinfo.h"   //npcUI���
#include "Tree.h"
#include "tilledLand.h"
#include "Crop.h"    //ũ������
#include "MenuLayer.h"//�˵�����

class ExploreScene : public cocos2d::Scene {
public:
    ExploreScene();
    ~ExploreScene();


    //Explore��ͼ��������
    static ExploreScene* create();
    bool init();


    // ��Ϸ����
    void update(float deltaTime);

    //��ͼ�ƶ��������������Ұ�������
    void moveMap(float deltaX, float deltaY);
    //��� onKeyPressed ���� ʶ����̿��� ����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ����Ƿ���Χǽ������ײ
    bool isColliding(const cocos2d::Vec2& newPos);  // ������ײ��⺯��

    //������¼��Ŀ���
    void onMouseClicked(cocos2d::Event* event);

    //������Ƿ����ͼԪ�ط�������
    int checkForElementInteraction(const cocos2d::Vec2& clickPos);
    // ���һ���������пɽ���Ԫ�صķ���
    void addInteractiveElement(InteractiveElement* element) {
        interactiveElements.push_back(element);
    }

private:

    // ��ͼ���
    cocos2d::TMXTiledMap* Exploremap;   // ��ͼ���󣬸�Ϊ Tiled ��ͼ
    cocos2d::TMXLayer* groundLayer;  // �����
    cocos2d::TMXLayer* wallLayer;    // Χǽ��


    cocos2d::Size ExploremapSize;        // ��ͼ��С
    float scaleFactor;  // ��ǰ���ű���


    //�������
    cocos2d::ui::Button* returnButton;  // ������ť����--�ص�ũ��
    //�����������
    bool movingUp;  // �Ƿ�ס�ϼ�
    bool movingDown; // �Ƿ�ס�¼�
    bool movingLeft; // �Ƿ�ס���
    bool movingRight; // �Ƿ�ס�Ҽ�
    //������������
    // �洢���� NPC �������ɽ���Ԫ�ص��б�
    std::vector<InteractiveElement*> interactiveElements;

};

#endif 
