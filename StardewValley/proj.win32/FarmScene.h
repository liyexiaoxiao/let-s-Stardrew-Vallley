#pragma once
//�����������ũ������
//������ͼ���š���ͼ�ƶ��������ƶ�������������Ʒ�Ľ����ӿ�
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "Weed.h"       // ������ Weed ��
#include "Tool.h"       // ������ Tool ��
#include "Resident.h"   //NPC����
#include "player.h"    //�����
#include "Farmer.h"    //ũ����
#include "NPCinfo.h"   //npcUI���

#include "Crop.h"    //ũ������


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

    //������¼��Ŀ���
    void onMouseClicked(cocos2d::Event* event);

    //��ֲ����
    void onMouseClickedSoil(cocos2d::Event* event);
    void plantSeed(int x, int y);
    void waterCrop(int x, int y);  // ��ˮ

    //������Ƿ����ͼԪ�ط�������
    int checkForElementInteraction(const cocos2d::Vec2& clickPos);
    // ����һ���������пɽ���Ԫ�صķ���
    void addInteractiveElement(InteractiveElement* element) {
        interactiveElements.push_back(element);
    }
    void displayDebugInfo(const std::string& info) {
        // ���û�е����ı���ǩ������һ���µ�
        if (!_debugLabel) {
            _debugLabel = cocos2d::Label::createWithSystemFont(info, "Arial", 24);
            _debugLabel->setPosition(cocos2d::Vec2(400, 500));  // ����Ļ�м�λ����ʾ
            this->addChild(_debugLabel);
        }
        else {
            // ������е��Ա�ǩ�����������ı�
            _debugLabel->setString(info);
        }
    }


private:
    cocos2d::Label* _debugLabel = nullptr;  // ������ʾ������Ϣ
    // ��ͼ���
    cocos2d::TMXTiledMap* Farmmap;   // ��ͼ���󣬸�Ϊ Tiled ��ͼ
    cocos2d::TMXLayer* groundLayer;  // �����
    cocos2d::TMXLayer* wallLayer;    // Χǽ��

    std::vector<std::vector<Crop*>> plantedCrops; // �洢��ֲ������


    cocos2d::Size FarmmapSize;        // ��ͼ��С
    float scaleFactor;  // ��ǰ���ű���

    //������
    Player* mainPlayer; // �����

    //NPC���
    Farmer* farmer;
    //ũ���λ��

    //ũ��ʵ�ֺ����������
    std::vector<Weed*> weeds;      // �Ӳ��б�
    //std::vector<Tool*> tools;      // �����б�



    //�������
    //�����������
    bool movingUp;  // �Ƿ�ס�ϼ�
    bool movingDown; // �Ƿ�ס�¼�
    bool movingLeft; // �Ƿ�ס���
    bool movingRight; // �Ƿ�ס�Ҽ�
    //������������
    // �洢���� NPC �������ɽ���Ԫ�ص��б�
    std::vector<InteractiveElement*> interactiveElements;
};

#endif // __FARM_SCENE_H__