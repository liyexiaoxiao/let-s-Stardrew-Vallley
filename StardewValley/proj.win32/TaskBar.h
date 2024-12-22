#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tools.h"

// ����ṹ�嶨��
struct Task {
    std::string title;
    std::string status;  // �����״̬���� "In Progress" �� "Completed"
    cocos2d::ui::Button* button;  // �����Ӧ�İ�ť
};

class TaskBar : public cocos2d::Layer {
public:
    TaskBar() : taskList(), visible(false) {}
    ~TaskBar() {}

    // ��ȡ TaskBar ʵ��
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

    // ��������ʼ��
    bool init();
    // ��ʾ������
    void show();
    // ����������
    void hide();
    // �����������ǰ�Ƿ�ɼ�
    bool isVisible() const;
    // �������
    void addTask(const std::string& title, const std::string& RenPhoto, const std::string& CailiaoPhoto, int CailiaoNum,int taskNum);
    // �������¼�
    void onTaskClicked(const std::string& taskTitle, cocos2d::ui::Button* taskButton);
    // ��������״̬
    void updateTaskStatus(const std::string& taskTitle, const std::string& newStatus);

private:
    static TaskBar* instance;  // ����ʵ��
    bool visible;  // ��¼����������ʾ״̬
    std::vector<Task> taskList;  // �洢����ť
};
