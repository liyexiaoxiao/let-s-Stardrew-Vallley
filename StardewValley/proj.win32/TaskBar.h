#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tools.h"

// 任务结构体定义
struct Task {
    std::string title;
    std::string status;  // 任务的状态，如 "In Progress" 或 "Completed"
    cocos2d::ui::Button* button;  // 任务对应的按钮
};

class TaskBar : public cocos2d::Layer {
public:
    TaskBar() : taskList(), visible(false) {}
    ~TaskBar() {}

    // 获取 TaskBar 实例
    static TaskBar* getInstance() {
        if (instance == nullptr) {
            instance = new TaskBar();
            if (!instance->init()) {
                delete instance;
                instance = nullptr;
            }
        }
        return instance;
    }

    // 任务栏初始化
    bool init();
    // 显示任务栏
    void show();
    // 隐藏任务栏
    void hide();
    // 检查任务栏当前是否可见
    bool isVisible() const;
    // 添加任务
    void addTask(const std::string& title, const std::string& RenPhoto, const std::string& CailiaoPhoto, int CailiaoNum,int taskNum);
    // 任务点击事件
    void onTaskClicked(const std::string& taskTitle, cocos2d::ui::Button* taskButton);
    // 更新任务状态
    void updateTaskStatus(const std::string& taskTitle, const std::string& newStatus);

private:
    static TaskBar* instance;  // 单例实例
    bool visible;  // 记录任务栏的显示状态
    std::vector<Task> taskList;  // 存储任务按钮
};
