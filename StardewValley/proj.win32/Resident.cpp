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
    romance = 0;   // Ĭ������ֵ
    busy = false;
    this->initWithFile(imgPath);  // ʹ�� Cocos2d �ķ���������ͼ��
    this->setPosition(site);//��ʼ����λ��--��Ļ����
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


//����������
cocos2d::Rect Resident::getBoundingBox() const {
    // ��̬���ص�ǰ Resident �İ�Χ��
    auto position = this->getPosition();  // ��ǰ Resident ����������
    auto contentSize = this->getContentSize();
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,
        position.y - contentSize.height * this->getAnchorPoint().y,
        contentSize.width,
        contentSize.height
    );
}
//չʾ������
void Resident::showInfoPanel() {
    NPCInfo* npcLayer = NPCInfo::create(); // ����NPCInfoʵ��
    npcLayer->showResidentInfo(name, profession, friendship, romance); // ��ʾNPC��Ϣ
    this->getParent()->addChild(npcLayer); // �������ӵ����ڵ�
}