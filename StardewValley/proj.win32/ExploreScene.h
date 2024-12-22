#pragma once
//负责管理整个冒险场景
//包括地图缩放、地图移动（人物移动）、与其中物品的交互接口
#ifndef __EXPLORE_SCENE_H__
#define __EXPLORE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resident.h"   //NPC基类
#include "player.h"    //玩家类
#include "Farmer.h"    //农民类
#include "NPCinfo.h"   //npcUI面板
#include "Tree.h"
#include "tilledLand.h"
#include "Crop.h"    //农作物类
#include "MenuLayer.h"//菜单界面

class ExploreScene : public cocos2d::Scene {
public:
    ExploreScene();
    ~ExploreScene();


    //Explore地图界面生成
    static ExploreScene* create();
    bool init();


    // 游戏更新
    void update(float deltaTime);

    //地图移动，利用上下左右按键控制
    void moveMap(float deltaX, float deltaY);
    //添加 onKeyPressed 声明 识别键盘控制 单击
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //长按
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 检查是否与围墙发生碰撞
    bool isColliding(const cocos2d::Vec2& newPos);  // 声明碰撞检测函数

    //鼠标点击事件的控制
    void onMouseClicked(cocos2d::Event* event);

    //检查点击是否与地图元素发生交互
    int checkForElementInteraction(const cocos2d::Vec2& clickPos);
    // 添加一个管理所有可交互元素的方法
    void addInteractiveElement(InteractiveElement* element) {
        interactiveElements.push_back(element);
    }

private:

    // 地图相关
    cocos2d::TMXTiledMap* Exploremap;   // 地图对象，改为 Tiled 地图
    cocos2d::TMXLayer* groundLayer;  // 地面层
    cocos2d::TMXLayer* wallLayer;    // 围墙层


    cocos2d::Size ExploremapSize;        // 地图大小
    float scaleFactor;  // 当前缩放比例


    //交互相关
    cocos2d::ui::Button* returnButton;  // 声明按钮变量--回到农场
    //长按键盘相关
    bool movingUp;  // 是否按住上键
    bool movingDown; // 是否按住下键
    bool movingLeft; // 是否按住左键
    bool movingRight; // 是否按住右键
    //鼠标点击交互相关
    // 存储所有 NPC 和其他可交互元素的列表
    std::vector<InteractiveElement*> interactiveElements;

};

#endif 
