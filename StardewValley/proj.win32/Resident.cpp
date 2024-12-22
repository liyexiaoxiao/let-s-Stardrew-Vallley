#include "Resident.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Clock.h"
//����ÿ��ֻ������һ������ֵ

Resident::Resident()
    : name("Unknown"), profession("Unknown"), romance(0), friendship(0),busy(false) {
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

    //���Ӱ�ť����npc���к�������ֵ����
    // ������ť������ NPC �Ա�
    auto button = cocos2d::MenuItemImage::create(
        "photo/ui/basic.png",  // ��ť����״̬��ͼƬ
        "photo/ui/basic2.png", // ��ť����״̬��ͼƬ
        CC_CALLBACK_1(Resident::onButtonClick, this) // ��ť����¼�
    );
    button->setScale(4.0f);
    button->setPosition(cocos2d::Vec2(80, 0));  // ����� NPC ���Ͻ� (0, 0) ��ƫ��
    auto menu = cocos2d::Menu::create(button, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    menu->setLocalZOrder(10);  // ȷ����ťλ������Ԫ��֮��
    this->addChild(menu);
    return true;
}

//���к���ť�ص��¼�

void Resident::onButtonClick(cocos2d::Ref* sender) {
    // NPC ˵�����߼�
    auto talkLabel =cocos2d:: Label::createWithSystemFont("Hello, I'm " + name + "!", "Arial", 40);
    talkLabel->setPosition(this->getPosition() + cocos2d::Vec2(0, 50)); // ������ʾ�� NPC �Ϸ�
    this->getParent()->addChild(talkLabel);
    // �ӳ� 2 ���ɾ����ʾ������
    auto delay = cocos2d::DelayTime::create(2.0f);
    auto removeAction = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(delay, removeAction, nullptr);
    talkLabel->runAction(sequence);
    // ��������ֵ
    if (!isfs) {
        increaseFriendship();
        // ��ʾ����ֵ���ӵ���ʾ������ʹ�� Label ����ʾ��
        auto friendshipLabel = cocos2d::Label::createWithSystemFont("Friendship +1", "Arial", 40);
        friendshipLabel->setPosition(this->getPosition() + cocos2d::Vec2(0, -10));
        this->getParent()->addChild(friendshipLabel, 1);

        // 2����Ƴ�����ֵ��ʾ
        friendshipLabel->runAction(cocos2d::Sequence::create(
            cocos2d::DelayTime::create(2.0f),
            cocos2d::RemoveSelf::create(),
            nullptr
        ));
        isfs = true;
    }
    else {
        auto friendshipLabel = cocos2d::Label::createWithSystemFont("Please wait for tomorrow", "Arial", 35);
        friendshipLabel->setPosition(this->getPosition() + cocos2d::Vec2(0, -10));
        this->getParent()->addChild(friendshipLabel, 1);

        // 2����Ƴ�����ֵ��ʾ
        friendshipLabel->runAction(cocos2d::Sequence::create(
            cocos2d::DelayTime::create(2.0f),
            cocos2d::RemoveSelf::create(),
            nullptr
        ));
    }
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