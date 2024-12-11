#include "Farmer.h"
using namespace cocos2d;

Farmer::Farmer() {
    name = "John Doe";
    profession = "Farmer";
    Worldx = 1100;
    Worldy = 1100;
    sprite = this;
    this->initWithFile("photo/Character/Resident1.png");  // 设置农民的图像
    this->setPosition(cocos2d::Vec2(Worldx, Worldy));
    
    // 创建面板的 UI 元素以及面板初始化
    nameLabel = cocos2d::Label::createWithSystemFont("Name: ", "Arial", 24);
    this->addChild(nameLabel);
    /*professionLabel = cocos2d::Label::createWithSystemFont("Profession: ", "Arial", 24);
    this->addChild(professionLabel);
    romanceLabel = cocos2d::Label::createWithSystemFont("Romance: 0", "Arial", 24);
    this->addChild(romanceLabel);
    friendshipLabel = cocos2d::Label::createWithSystemFont("Friendship: 0", "Arial", 24);
    this->addChild(friendshipLabel);
    taskLabel = cocos2d::Label::createWithSystemFont("Task: ", "Arial", 24);
    this->addChild(taskLabel);*/
    // 设置初始位置（例如，确保它们不会显示在屏幕上，或者设置为透明）
    nameLabel->setVisible(false);
    /*professionLabel->setVisible(false);
    romanceLabel->setVisible(false);
    friendshipLabel->setVisible(false);
    taskLabel->setVisible(false);*/
}

Farmer::~Farmer() {}

void Farmer::offerTask() {
    CCLOG("%s is offering a task", name.c_str());
    // 在这里创建农民的任务逻辑
}

//交互相关
void Farmer::showInfoPanel() {
    nameLabel->setVisible(true);
    /*professionLabel->setVisible(true);
    romanceLabel->setVisible(true);
    friendshipLabel->setVisible(true);
    taskLabel->setVisible(true);*/
    // 更新面板上的信息
    nameLabel->setString("Name: " + name);
    /*professionLabel->setString("Profession: " + profession);
    romanceLabel->setString("Romance: " + std::to_string(romance));
    friendshipLabel->setString("Friendship: " + std::to_string(friendship));*/

    // 如果有任务，则更新任务信息
    if (currentTask) {
        //taskLabel->setString("Task: " + currentTask->getTaskName());
    }
}
cocos2d::Rect Farmer::getBoundingBox() const {
    // 动态返回当前 Farmer 的包围盒
    auto position = this->getPosition();  // 当前 Farmer 的世界坐标
    auto contentSize = this->getContentSize();

    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,
        position.y - contentSize.height * this->getAnchorPoint().y,
        contentSize.width,
        contentSize.height
    );
}

