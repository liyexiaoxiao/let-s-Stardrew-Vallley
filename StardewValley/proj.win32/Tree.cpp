//地图上树的生成
#include "Tree.h"

Tree::Tree() : removed(false) {}

Tree::~Tree() {}

Tree* Tree::create() {
    Tree* ret = new Tree();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool Tree::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 设置树的图像
    this->initWithFile("photo/Farm/tree.png");
    this->setVisible(true);

    return true;
}

void Tree::removeTree() {
    this->initWithFile("photo/Farm/tree2.png");//树图变成树桩
    removed = true;  // 设置为已移除
}

cocos2d::Rect Tree::getBoundingBox() const {
    // 获取树的世界坐标
    auto position =  this->getPosition();

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

