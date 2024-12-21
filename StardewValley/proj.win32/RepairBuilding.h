#pragma once
#ifndef __REPAIRBUILDING_H__
#define __REPAIRBUILDING_H__

#include "cocos2d.h"
#include "InteractiveElement.h" //交互式相关

class RepairBuilding : public cocos2d::Sprite, public InteractiveElement {
public:
    RepairBuilding(const std::string& brokenImage, const std::string& fixedImage);  // 构造函数接收路径
    ~RepairBuilding();

    static RepairBuilding* create(const std::string& brokenImage, const std::string& fixedImage);  // 静态创建函数
    bool init();  // 初始化函数

    void startRepair();  // 开始修复
    void completeRepair();  // 完成修复

    // 实现 InteractiveElement 的 onClick 方法
    int onClick() override {
        // 在点击时可以触发轻微放大并恢复的效果
        this->runAction(cocos2d::Sequence::create(
            cocos2d::ScaleTo::create(0.1f, 1.1f),  // 放大 10%
            cocos2d::ScaleTo::create(0.1f, 1.0f),  // 恢复到原大小
            nullptr));  // 动作结束后继续执行
        if (isready) startRepair();
        return 2;//还未规定
    }
    //利用包围盒进行多态判断
    cocos2d::Rect getBoundingBox() const override;

    bool isready = true;//材料是否足够修复

private:
    std::string brokenImage;  // 坏建筑图像路径
    std::string fixedImage;  // 修复后的建筑图像路径
    bool isRepairing;  // 是否正在修复
    bool isRepaired;//是否已经修复
    float repairProgress;  // 修复进度
    float repairTime;  // 修复时间

    cocos2d::ProgressTimer* repairProgressBar;  // 进度条
    // 其他可能的成员变量
};

#endif // __REPAIRBUILDING_H__

