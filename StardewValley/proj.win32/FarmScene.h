#pragma once
//负责管理整个农场场景
//包括地图缩放、地图移动（人物移动）、与其中物品的交互接口
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resident.h"   //NPC基类
#include "player.h"    //玩家类
#include "Farmer.h"    //农民类
#include "NPCinfo.h"   //npcUI面板
#include "Tree.h"//农场--树（可砍伐）
#include"Coop.h" //鸡舍实现
#include "tilledLand.h"//瓦片土地
#include "WateredLand.h"//水资源
#include "Crop.h"    //农作物类
#include "MenuLayer.h"//菜单界面
#include "Toolbar.h" //工具栏
#include "RepairBuilding.h"//修复建筑/菜单界面



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
    //添加 onKeyPressed 声明 识别键盘控制 单击
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //长按
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 检查是否与围墙发生碰撞
    bool isColliding(const cocos2d::Vec2& newPos);  // 声明碰撞检测函数
    bool isColliding2(const cocos2d::Vec2& newPos);  // 声明碰撞检测函数

    //鼠标点击事件的控制
    void onMouseClicked(cocos2d::Event* event);

    //种植种子
    void onMouseClickedSoil(cocos2d::Event* event);
    //第二天更新植物状态
    void nextDay();

    //检查点击是否与地图元素发生交互
    int checkForElementInteraction(const cocos2d::Vec2& clickPos);
    // 添加一个管理所有可交互元素的方法
    void addInteractiveElement(InteractiveElement* element) {
        interactiveElements.push_back(element);
    }
    void displayDebugInfo(const std::string& info) {
        // 如果没有调试文本标签，创建一个新的
        if (!_debugLabel) {
            _debugLabel = cocos2d::Label::createWithSystemFont(info, "Arial", 24);
            _debugLabel->setPosition(cocos2d::Vec2(400, 500));  // 在屏幕中间位置显示
            this->addChild(_debugLabel);
        }
        else {
            // 如果已有调试标签，更新它的文本
            _debugLabel->setString(info);
        }
    }

private:
    cocos2d::Label* _debugLabel = nullptr;  // 用于显示调试信息
    // 地图相关
    cocos2d::TMXTiledMap* Farmmap;   // 地图对象，改为 Tiled 地图
    cocos2d::TMXLayer* groundLayer;  // 地面层
    cocos2d::TMXLayer* wallLayer;    // 围墙层
    cocos2d::TMXLayer* wallLayer2;    // 围墙层2

    //场景转化相关
    cocos2d::ui::Button* startButton;  // 声明按钮变量--进入室内
    cocos2d::ui::Button* startButton2;  // 声明按钮变量--前往冒险地图
    
    std::vector<std::vector<TilledLand*>> tilledLand;
    //只能进行手动清理的资源
    //void onExit();
    
    //钓鱼相关
    cocos2d::ui::Button* FishingButton;
    
    // 记录哪些土地已开垦
    std::vector<std::vector<WateredLand*>> wateredLand;// 记录哪些土地已浇水
    std::vector<std::vector<Crop*>> plantedCrops; // 存储种植的作物

    cocos2d::Size FarmmapSize;        // 地图大小
    float scaleFactor;  // 当前缩放比例


    //NPC相关
    Resident* farmer;
    Resident* fisherman;
    Resident* breeder;
    

    //农场实现后续功能相关
    //std::vector<Tool*> tools;      // 工具列表
    std::vector<Tree*> trees; //树列表
   Coop* coop;

    //修复建筑相关
    RepairBuilding* market;

    //交互相关
    //长按键盘相关
    bool movingUp;  // 是否按住上键
    bool movingDown; // 是否按住下键
    bool movingLeft; // 是否按住左键
    bool movingRight; // 是否按住右键
    //鼠标点击交互相关
    // 存储所有 NPC 和其他可交互元素的列表
    std::vector<InteractiveElement*> interactiveElements;

    MenuLayer* menuLayer;  // 菜单层对象
    bool isMenuActive = false;  // 标志变量，表示菜单是否显示
   
};

#endif // __FARM_SCENE_H__
