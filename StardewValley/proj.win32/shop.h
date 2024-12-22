#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tools.h"
#include "ItemIDs.h"
#include "ItemStorage.h"
class Shop : public cocos2d::Layer {
public:
    Shop() : visible(false) {}
    ~Shop() {}

    // 获取 Shop 实例
    static Shop* getInstance() {
        if (instance == nullptr) {
            instance = new Shop();
            if (!instance->init()) {
                delete instance;
                instance = nullptr;
            }
        }
        return instance;
    }
    // 商店初始化
    bool init();
    // 显示商店
    void show();
    // 隐藏商店
    void hide();
    // 检查商店当前是否可见
    bool isVisible() const;
    //增加商品
    void addItem(const std::string& itemPhotoPath, StorageID ID, float posX, float posY, bool sign);
    //卖东西
    void sellItem(StorageID ID, int amount);
    //买东西
    void buyItem(StorageID ID, int amount);
private:
    static Shop* instance;  // 单例实例
    bool visible;  // 记录任务栏的显示状态
};
