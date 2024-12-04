#include "Resident.h"


Resident::Resident()
    : name("Unknown"), profession("Unknown"), romance(0), currentTask(nullptr), busy(false) {
}

Resident::~Resident() {}

bool Resident::init(const std::string& n, const std::string& prof, const std::string& imgPath) {
    name = n;
    profession = prof;
    romance = 0;   // 默认浪漫值
    busy = false;
    this->initWithFile(imgPath);  // 使用 Cocos2d 的方法来加载图像
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



