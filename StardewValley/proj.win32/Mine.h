#pragma once
#ifndef MINE_H
#define MINE_H

// 确保包含保护不会与同名的其他头文件冲突
#pragma once
#include "InteractiveElement.h" //交互式相关
#include "cocos2d.h"

class Mine : public cocos2d::Sprite, public InteractiveElement {
public:
    Mine();
    ~Mine();
    // 初始化
    static Mine* create();
    bool init();

    // 相关功能
    void removeMine(); // 移除矿区
    bool isRemoved() const { return removed; }

    // 实现 InteractiveElement 的 onClick 方法
    int onClick() override {
        removeMine();
        return 2;//多态返回2，表示收获矿产，后续实现仓库物品+n
    }

    // 利用包围盒进行多态判断
    cocos2d::Rect getBoundingBox() const override;

private:
    bool removed; // 标记矿区是否已被移除
    // 随机选择的矿区图片路径
    std::vector<std::string> mineImages = {
        "photo/Adventure/mine1.png",  // 第一种矿区图像
        "photo/Adventure/mine2.png",  // 第二种矿区图像
        "photo/Adventure/mine3.png"   // 第三种矿区图像
    };
};

#endif // MINE_H
