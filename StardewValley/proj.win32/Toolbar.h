#include "cocos2d.h"
#include "ui/CocosGUI.h"  // 添加这个头文件来使用 Button 类


class Toolbar : public cocos2d::Layer {
public:
    Toolbar() : currentToolIndex(1), markerSprite(nullptr), markerStartX(200), markerY(100) {}
    ~Toolbar() {}

    bool init();
    // 获取唯一的实例
    static Toolbar* getInstance() {
        if (!instance) {
            instance = new Toolbar();
            instance->init();  // 确保初始化
            instance->autorelease();  // 自动管理内存
        }
        return instance;
    }
    // 销毁实例
    static void destroyInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
    //创建工具栏
    static Toolbar* create() {
        Toolbar* ret = new Toolbar();
        if (ret && ret->init()) {
            ret->autorelease();  // 如果成功，返回实例并自动管理内存
            return ret;
        }
        else {
            delete ret;
            return nullptr;
        }
    }
    //更新工具升级的图标
    void updateToolIcons();
    // 鼠标滚轮事件处理
    void onMouseScroll(cocos2d::Event* event);
    void createSeedSelectionPanel();
    void onSeedSelected(cocos2d::Ref* sender, int seedType);
    void closeSeedPanel(cocos2d::Ref* sender);
private:
    int currentToolIndex;  // 当前持有的工具索引
    cocos2d::ui::Button* SeedButton;       //种子按钮
    cocos2d::Sprite* markerSprite;        // 新的图片 (指示标记)
    float markerStartX;                   // 新图片的初始 x 坐标
    float markerY;                        // 新图片的 y 坐标
    void updateMarkerPosition();          // 更新新图片的位置
    static Toolbar* instance;  // 静态实例指针
    cocos2d::Sprite* Axe;
    cocos2d::Sprite* Hoe;
    cocos2d::Sprite* Watering_Can;
    cocos2d::Sprite* Pickaxe;
    cocos2d::Sprite* Sickle;
    cocos2d::Sprite* Fish;
};
#pragma once