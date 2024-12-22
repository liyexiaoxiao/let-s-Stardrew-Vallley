#include "TaskBar.h"
#include "player.h"
#include "ItemStorage.h"
// 定义静态成员变量
TaskBar* TaskBar::instance = nullptr;
extern Player* mainPlayer;
// 初始化
bool TaskBar::init() {
    if (!Layer::init()) {
        return false;
    }
    Tools Tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 创建任务栏背景
    auto BGImagePos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
    auto MenuBG = Tool.addImageToScene("photo/ui/Menu.png", BGImagePos, 2.0f);
    this->addChild(MenuBG, 1);
    auto bgSize = MenuBG->getContentSize();

    // 初始化任务列表
    taskList.clear();

    addTask("Alex","photo/task/alex.png", "photo/storage/beer.png",150,1);
    addTask("Willy", "photo/task/willy.png", "photo/storage/Fish_1.png", 50,2);
    addTask("Marnie", "photo/task/marnie.png", "photo/storage/hongmogu.png", 200, 3);
    addTask("Sandy", "photo/task/sandy.png", "photo/storage/jiang.png", 250, 4);
    addTask("Clint", "photo/task/clint.png", "photo/storage/luobo.png", 80, 5);
    addTask("Willy", "photo/task/willy.png", "photo/storage/mutou.png", 500, 6);
    addTask("Sandy", "photo/task/sandy.png", "photo/storage/cooked_fish.png", 20, 7);
    addTask("Marnie", "photo/task/marnie.png", "photo/storage/dacong.png", 150, 8);
    addTask("Clint", "photo/task/clint.png", "photo/storage/nangua.png", 200, 9);
    addTask("Alex", "photo/task/alex.png", "photo/storage/shitou.png", 500, 10);

    return true;
}
// 显示任务栏
void TaskBar::show() {
    this->setVisible(true);
    visible = true;
}
// 隐藏任务栏
void TaskBar::hide() {
    this->setVisible(false);
    visible = false;
}
// 检查任务栏当前是否可见
bool TaskBar::isVisible() const {
    return visible;
}
// 添加任务
void TaskBar::addTask(const std::string& title, const std::string& RenPhoto, const std::string& CailiaoPhoto, int CailiaoNum, int taskNum) {
    Tools Tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // 创建任务项按钮
    auto taskButton = cocos2d::ui::Button::create("photo/task/longbutton.png");
    taskButton->setScale(1.2f);
    taskButton->setTitleText(title + " (In Progress)");  // 初始状态为 In Progress
    taskButton->setTitleFontSize(20);
    taskButton->setTitleColor(cocos2d::Color3B::RED);  // 设置初始文字颜色为红色

    // 计算按钮的位置
    float posX = visibleSize.width / 2-100;
    if (taskNum > 5) {
        posX += 350;
    }
    float posY = visibleSize.width / 2 - 400;
    posY += ((taskNum-1) % 5) * 60;
    taskButton->setPosition(cocos2d::Vec2(posX, posY));  // 设定按钮位置
    taskButton->addClickEventListener([this, title, taskButton,taskNum](cocos2d::Ref* sender) {
        onTaskClicked(title, taskButton,taskNum);  // 传递按钮引用
        });
    //任务相关信息放置
    float Scale = 0.8f;
    if (title == "Sandy" || title == "Clint")
        Scale = 3.0f;
    float RenPosX=posX-210;
    this->addChild(Tool.addImageToScene(RenPhoto, cocos2d::Vec2(RenPosX, posY), Scale),20);
    float CailiaoPosX = RenPosX + 50;
    this->addChild(Tool.addImageToScene(CailiaoPhoto, cocos2d::Vec2(CailiaoPosX, posY), 2.8f),20);
    float CailiaoLabelPosX = CailiaoPosX + 35;
    this->addChild(Tool.createLabel(std::to_string(CailiaoNum), "fonts/Marker Felt.ttf", 24, cocos2d::Vec2(CailiaoLabelPosX, posY)),20);
    // 创建任务结构并添加到任务列表
    Task task;
    task.title = title;
    task.status = "In Progress";
    task.button = taskButton;
    task.number = taskNum;

    taskList.push_back(task);
    this->addChild(taskButton, 100);  // 直接将按钮添加到Layer

    // 更新任务栏高度，如果需要的话，你可以调整显示区域的高度
}
// 任务点击事件
void TaskBar::onTaskClicked(const std::string& taskTitle, cocos2d::ui::Button* taskButton,int taskNum) {
    // 查找对应的任务
    for (auto& task : taskList) {
        if (task.title == taskTitle) {
            if (if_can_complete(taskNum)) {
                // 更新任务状态
                task.status = "Completed";  // 修改为已完成
                taskButton->setTitleText(taskTitle + " (Completed)");  // 更新按钮的文本
                taskButton->setTitleColor(cocos2d::Color3B::GREEN);  // 修改文字颜色为绿色
                cocos2d::log("Task completed: %s", taskTitle.c_str());
                break;
            }
            else
                break;
        }
    }
}
//任务是否能完成+物品减少逻辑
bool TaskBar::if_can_complete(int taskNum) {
    ItemStorage& storage = ItemStorage::getInstance();
    if (taskNum == 1) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::BEER)) >= 150 ){
            storage.removeItem(StorageID::BEER, 150);
            mainPlayer->setMoney(1000);
            mainPlayer->setPrestige(20);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 2) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::FISH_A)) >= 50) {
            storage.removeItem(StorageID::FISH_A, 50);
            mainPlayer->setMoney(1500);
            mainPlayer->setPrestige(40);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 3) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::HONGMOGU)) >= 200) {
            storage.removeItem(StorageID::HONGMOGU, 200);
            storage.addItem(StorageID::JUANZHOU, 1);
            mainPlayer->setMoney(1200);
            mainPlayer->setPrestige(30);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 4) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::JIANG)) >= 250) {
            storage.removeItem(StorageID::JIANG, 250);
            storage.addItem(StorageID::HUASHU, 1);
            mainPlayer->setMoney(1800);
            mainPlayer->setPrestige(60);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 5) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::LUOBO)) >= 80) {
            storage.removeItem(StorageID::LUOBO, 80);
            mainPlayer->setMoney(500);
            mainPlayer->setPrestige(10);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 6) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::MUTOU)) >= 500) {
            storage.removeItem(StorageID::MUTOU, 500);
            storage.addItem(StorageID::BEIKE, 1);
            mainPlayer->setMoney(2000);
            mainPlayer->setPrestige(80);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 7) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::COOKED_FISH)) >= 20) {
            storage.removeItem(StorageID::COOKED_FISH, 20);
            mainPlayer->setMoney(800);
            mainPlayer->setPrestige(18);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 8) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::DACONG)) >= 150) {
            storage.removeItem(StorageID::DACONG, 150);
            mainPlayer->setMoney(900);
            mainPlayer->setPrestige(19);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 9) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::NANGUA)) >= 200) {
            storage.removeItem(StorageID::NANGUA, 200);
            storage.addItem(StorageID::LAZIJI, 1);
            mainPlayer->setMoney(1200);
            mainPlayer->setPrestige(40);
            return true;
        }
        else
            return false;
    }
    else if (taskNum == 10) {
        if (storage.getItemQuantity(static_cast<int>(StorageID::SHITOU)) >= 500) {
            storage.removeItem(StorageID::SHITOU, 500);
            storage.addItem(StorageID::SHANHU, 1);
            mainPlayer->setMoney(2000);
            mainPlayer->setPrestige(80);
            return true;
        }
        else
            return false;
    }
    return false;
}

