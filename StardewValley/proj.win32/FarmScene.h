#pragma once
//�����������ũ������
//������ͼ���š���ͼ�ƶ��������ƶ�������������Ʒ�Ľ����ӿ�
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "Weed.h"       // ������ Weed ��
#include "Tool.h"       // ������ Tool ��
#include "player.h"    //�����


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
    //��� onKeyPressed ���� ʶ����̿��� ����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ����Ƿ���Χǽ������ײ
    bool isColliding(const cocos2d::Vec2& newPos);  // ������ײ��⺯��

    //������¼��Ŀ���
    void onMouseClicked(cocos2d::Event* event);
    //������Ƿ����ͼԪ�ط�������
    void checkForElementInteraction(const cocos2d::Vec2& clickPos);

private:
    // ��ͼ���
    cocos2d::TMXTiledMap* Farmmap;   // ��ͼ���󣬸�Ϊ Tiled ��ͼ
    cocos2d::TMXLayer* groundLayer;  // �����
    cocos2d::TMXLayer* wallLayer;    // Χǽ��

    cocos2d::Size FarmmapSize;        // ��ͼ��С
    float scaleFactor;  // ��ǰ���ű���

    //������
    Player* mainPlayer; // �����

    //ũ��ʵ�ֺ����������
    std::vector<Weed*> weeds;      // �Ӳ��б�
    //std::vector<Tool*> tools;      // �����б�

    //���湦����
    //�����������
    bool movingUp;  // �Ƿ�ס�ϼ�
    bool movingDown; // �Ƿ�ס�¼�
    bool movingLeft; // �Ƿ�ס���
    bool movingRight; // �Ƿ�ס�Ҽ�
};

#endif // __FARM_SCENE_H__
