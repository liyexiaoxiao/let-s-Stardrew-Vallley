#pragma once
//负责管理整个农场场景
//包括地图缩放、地图移动（人物移动）、与其中物品的交互接口
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "Weed.h"       // 假设有 Weed 类
#include "Tool.h"       // 假设有 Tool 类
#include "player.h"    //玩家类


class FarmScene : public cocos2d::Scene {
public:
    FarmScene();
    ~FarmScene();
    //Farm地图界面生成
    static FarmScene* create();
    bool init();

    // 游戏更新
    void update(float deltaTime);

    //地图移动，利用上下左右按键控制
    void moveMap(float deltaX, float deltaY);
    //void movePlayer(float deltaX, float deltaY);不实现玩家移动
    //添加 onKeyPressed 声明 识别键盘控制 单击
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //长按
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //鼠标点击事件的控制
    void onMouseClicked(cocos2d::Event* event);
    //检查点击是否与地图元素发生交互
    void checkForElementInteraction(const cocos2d::Vec2& clickPos);

private:
    //地图参数相关
    cocos2d::Sprite* Farmmap;    // 地图
    cocos2d::Size FarmmapSize;  // 地图大小
    float scaleFactor;  // 当前缩放比例

    //玩家相关
    Player* mainPlayer; // 主玩家

    //农场实现后续功能相关
    std::vector<Weed*> weeds;      // 杂草列表
    //std::vector<Tool*> tools;      // 工具列表

    //游玩功能性
    //长按键盘相关
    bool movingUp;  // 是否按住上键
    bool movingDown; // 是否按住下键
    bool movingLeft; // 是否按住左键
    bool movingRight; // 是否按住右键
};

#endif // __FARM_SCENE_H__
