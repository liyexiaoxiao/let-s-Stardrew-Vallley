#include "Resident.h"


Resident::Resident()
    : name("Unknown"), profession("Unknown"), romance(0), currentTask(nullptr), busy(false) {
    nameLabel = cocos2d::Label::createWithSystemFont("Name: ", "Arial", 24);
    this->addChild(nameLabel);
    nameLabel->setVisible(false);
}

Resident::~Resident() {}
bool Resident::init(const std::string& n, const std::string& prof, const std::string& imgPath, const cocos2d::Vec2& site) {
    name = n;
    profession = prof;
    romance = 0;   // 默认浪漫值
    busy = false;
    this->initWithFile(imgPath);  // 使用 Cocos2d 的方法来加载图像
    this->setPosition(site);//初始生成位置--屏幕坐标
    return true;
}


void Resident::setTask(Task* task) {
    currentTask = task;
}

Task* Resident::getCurrentTask() const {
    return currentTask;
}

void Resident::setBusy(bool busyStatus) {
    busy = busyStatus;
}


//点击交互相关
cocos2d::Rect Resident::getBoundingBox() const {
    // 动态返回当前 Resident 的包围盒
    auto position = this->getPosition();  // 当前 Resident 的世界坐标
    auto contentSize = this->getContentSize();
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,
        position.y - contentSize.height * this->getAnchorPoint().y,
        contentSize.width,
        contentSize.height
    );
}
//展示面板测试
void Resident::showInfoPanel() {
    NPCInfo* npcLayer = NPCInfo::create(); // 创建NPCInfo实例
    npcLayer->showResidentInfo(name, profession, friendship, romance); // 显示NPC信息
    this->getParent()->addChild(npcLayer); // 将面板添加到父节点
}