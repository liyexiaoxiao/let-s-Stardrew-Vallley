//地图上树的生成
#include "Mine.h"

Mine::Mine() : removed(false) {
    // 指向玩家对象的指针
}

Mine::~Mine() {}

Mine* Mine::create() {
    Mine* ret = new Mine();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool Mine::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 随机选择矿区图像
    int randomIndex = rand() % mineImages.size();  // 获取随机索引
    this->initWithFile(mineImages[randomIndex]);  // 根据随机索引选择矿区图像
    this->setVisible(true);

    return true;
}

void Mine::removeMine() {
    this->initWithFile("photo/Adventure/nomine.png");//树图变成树桩
    removed = true;  // 设置为已移除
}

//进行每日更新
void Mine::reset() {
    if (removed) {
        // 随机选择矿区图像
        int randomIndex = rand() % mineImages.size();  // 获取随机索引
        this->initWithFile(mineImages[randomIndex]);  // 根据随机索引选择矿区图像
        removed = false;  // 标记为未移除
    }
}

cocos2d::Rect Mine::getBoundingBox() const {
    // 获取树的世界坐标
    auto position = this->getPosition();

    // 获取树的尺寸
    auto contentSize = this->getContentSize();

    // 返回树的包围盒
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,  // 左上角 X 坐标
        position.y - contentSize.height * this->getAnchorPoint().y, // 左上角 Y 坐标
        contentSize.width,  // 宽度
        contentSize.height  // 高度
    );
}
