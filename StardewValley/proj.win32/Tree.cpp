//地图上树的生成
#include "Tree.h"
#include"player.h"//进行所持工具的判断
extern Player* mainPlayer; 
Tree::Tree() : removed(false) {
    // 指向玩家对象的指针
}

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
int Tree::onClick(){
    if (mainPlayer->getHeldTool() == 1) {//拿着斧头
        removeTree();
        return 1;
    }
    return 0; //什么都不做
}
void Tree::removeTree() {
    this->initWithFile("photo/Farm/tree2.png");//树图变成树桩
    removed = true;  // 设置为已移除
}
//进行每日更新
void Tree::reset() {
    if (removed) {
        this->initWithFile("photo/Farm/tree.png");  // 恢复为树
        removed = false;  // 标记为未移除
    }
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

