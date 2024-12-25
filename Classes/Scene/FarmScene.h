#pragma once
//�����������ũ������
//������ͼ���š���ͼ�ƶ��������ƶ�������������Ʒ�Ľ����ӿ�
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resident.h"   //NPC����
#include "player.h"    //�����
#include "Farmer.h"    //ũ����
#include "NPCinfo.h"   //npcUI���
#include "Tree.h"//ũ��--�����ɿ�����
#include"Coop.h" //����ʵ��
#include "tilledLand.h"//��Ƭ����
#include "WateredLand.h"//ˮ��Դ
#include "Crop.h"    //ũ������
#include"Mine.h"//��
#include "MenuLayer.h"//�˵�����
#include "Toolbar.h" //������
#include "RepairBuilding.h"//�޸�����/�˵�����



class FarmScene : public cocos2d::Scene {
public:
    FarmScene();
    ~FarmScene();


    //Farm��ͼ��������
    static FarmScene* create();
    bool init();


    // ��Ϸ����
    void update(float deltaTime);

    //��ͼ�ƶ��������������Ұ�������
    void moveMap(float deltaX, float deltaY);
    //���� onKeyPressed ���� ʶ����̿��� ����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ����Ƿ���Χǽ������ײ
    bool isColliding(const cocos2d::Vec2& newPos);  // ������ײ��⺯��
    bool isColliding2(const cocos2d::Vec2& newPos);  // ������ײ��⺯��

    //������¼��Ŀ���
    void onMouseClicked(cocos2d::Event* event);

    //��ֲ����
    void onMouseClickedSoil(cocos2d::Event* event);
    //�ڶ������ֲ��״̬
    void resetAllCrops();

    //������Ƿ����ͼԪ�ط�������
    int checkForElementInteraction(const cocos2d::Vec2& clickPos);
    // ����һ���������пɽ���Ԫ�صķ���
    void addInteractiveElement(InteractiveElement* element) {
        interactiveElements.push_back(element);
    }
    void setEnabledForReset(bool enabled);

private:

    // ��ͼ���
    cocos2d::TMXTiledMap* Farmmap;   // ��ͼ���󣬸�Ϊ Tiled ��ͼ
    cocos2d::TMXLayer* groundLayer;  // �����
    cocos2d::TMXLayer* wallLayer;    // Χǽ��
    cocos2d::TMXLayer* wallLayer2;    // Χǽ��2
    bool canResetCrops;
    //����ת�����
    cocos2d::ui::Button* startButton;  // ������ť����--��������

    std::vector<std::vector<TilledLand*>> tilledLand;
    //ֻ�ܽ����ֶ���������Դ
    //void onExit();

    //�������
    cocos2d::ui::Button* FishingButton;

    // ��¼��Щ�����ѿ���
    std::vector<std::vector<WateredLand*>> wateredLand;// ��¼��Щ�����ѽ�ˮ
    std::vector<std::vector<Crop*>> plantedCrops; // �洢��ֲ������

    cocos2d::Size FarmmapSize;        // ��ͼ��С
    float scaleFactor;  // ��ǰ���ű���


    //NPC���
    Resident* farmer;
    Resident* fisherman;
    Resident* breeder;


    //ũ��ʵ�ֺ����������
    //std::vector<Tool*> tools;      // �����б�
    std::vector<Tree*> trees; //���б�
    Coop* coop;

    //�޸��������
    RepairBuilding* market;

    //��
    std::vector<Mine*> mines; //���б�

    //�������
    //�����������
    bool movingUp;  // �Ƿ�ס�ϼ�
    bool movingDown; // �Ƿ�ס�¼�
    bool movingLeft; // �Ƿ�ס���
    bool movingRight; // �Ƿ�ס�Ҽ�
    //������������
    // �洢���� NPC �������ɽ���Ԫ�ص��б�
    std::vector<InteractiveElement*> interactiveElements;

    MenuLayer* menuLayer;  // �˵������
    bool isMenuActive = false;  // ��־��������ʾ�˵��Ƿ���ʾ

};

#endif // __FARM_SCENE_H__