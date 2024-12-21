#include "RepairBuilding.h"

RepairBuilding::RepairBuilding(const std::string& broken, const std::string& fixed)
    : brokenImage(broken), fixedImage(fixed), repairProgress(0), repairTime(10.0f), isRepairing(false), isRepaired(false) {
    // 创建进度条
    repairProgressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("photo/startup_p/textBox.png"));
    repairProgressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    repairProgressBar->setBarChangeRate(cocos2d::Vec2(1, 0));  // 水平进度条
    repairProgressBar->setMidpoint(cocos2d::Vec2(0, 0));  // 从左到右
    repairProgressBar->setPercentage(0);  // 初始进度为 0
    repairProgressBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -20));  // 设置进度条的位置
    repairProgressBar->setLocalZOrder(5);  // 设置进度条层次，确保它在建筑物之上
    this->addChild(repairProgressBar);  // 将进度条加入到建筑物中
}

RepairBuilding::~RepairBuilding() {
    // 清理工作，如果有需要的话
     // 清理修复计时器
    if (repairProgressBar) {
        repairProgressBar->removeFromParent();
    }
}

// 静态创建函数
RepairBuilding* RepairBuilding::create(const std::string& brokenImage, const std::string& fixedImage) {
    RepairBuilding* ret = new RepairBuilding(brokenImage, fixedImage);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RepairBuilding::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 使用坏建筑的图像进行初始化
    this->initWithFile(brokenImage);
    this->setVisible(true);  // 确保图像可见

    return true;
}

void RepairBuilding::startRepair() {
    if (isRepairing) return;
    isRepairing = true;

    // 修复进度，每秒更新一次
    schedule([this](float dt) {
        this->repairProgress += dt / repairTime;  // 每秒更新修复进度
        repairProgressBar->setPercentage(repairProgress * 100);  // 更新进度条的显示

        // 如果修复完成，调用完成修复的函数
        if (repairProgress >= 1.0f) {
            completeRepair();  // 修复完成
        }
        }, 1.0f, "repair_schedule_key");  // 每秒更新一次
}

void RepairBuilding::completeRepair() {
    unschedule("repair_schedule_key");  // 停止修复过程
    repairProgress = 1.0f;  // 修复完成
    repairProgressBar->setPercentage(100);  // 更新进度条
    // 切换到修复后的建筑图像
    this->setTexture(fixedImage);
    isRepaired = true;
    // 这里可以添加一些动画效果来展示修复完成后的结果
    cocos2d::FadeIn* fadeIn = cocos2d::FadeIn::create(0.5f);
    this->runAction(fadeIn);
    // 隐藏进度条
    repairProgressBar->setVisible(false);


}

cocos2d::Rect RepairBuilding::getBoundingBox() const {
    // 获取建筑的世界坐标
    const auto position = this->getPosition();

    // 获取建筑的尺寸
    const auto contentSize = this->getContentSize();

    // 返回树的包围盒
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,  // 左上角 X 坐标
        position.y - contentSize.height * this->getAnchorPoint().y, // 左上角 Y 坐标
        contentSize.width,  // 宽度
        contentSize.height  // 高度
    );
}