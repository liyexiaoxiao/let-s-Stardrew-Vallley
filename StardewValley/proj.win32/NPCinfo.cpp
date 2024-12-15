//û�д��������´���
#include"NPCinfo.h"

bool NPCInfo::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��������
    background = cocos2d::Sprite::create("photo/ui/Menu.png");
    background->setScale(2.2f);
    // ��ȡ��Ϸ���ڵĿ�Ⱥ͸߶�
    const float width = cocos2d::Director::getInstance()->getVisibleSize().width;
    const float height = cocos2d::Director::getInstance()->getVisibleSize().height;
    // ������ͼƬ������ʾ
    background->setPosition(cocos2d::Vec2(width / 2, height / 2));
    // ��������ӵ���ǰ��
    this->addChild(background);

    // ������ǩ��ʾNPC������
    nameLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 24);
    nameLabel->setPosition(cocos2d::Vec2(width / 2, height - 250));
    this->addChild(nameLabel);

    // ������ǩ��ʾNPC��ְҵ
    professionLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 18);
    professionLabel->setPosition(cocos2d::Vec2(width / 2,height - 300));
    this->addChild(professionLabel);

    // ������ǩ��ʾ����ֵ
    friendshipLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 18);
    friendshipLabel->setPosition(cocos2d::Vec2(width / 2,height - 350));
    this->addChild(friendshipLabel);

    // ������ǩ��ʾ����ֵ
    romanceLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 18);
    romanceLabel->setPosition(cocos2d::Vec2(width / 2, height - 400));
    this->addChild(romanceLabel);
    // ����Ĭ�ϲ��ɼ�
    this->setVisible(false);

    //�ر���尴ť
     // �����رհ�ť
    closeButton = cocos2d::ui::Button::create("photo/startup_p/ExitButton.png", "photo/startup_p/ExitButtonPressed.png");
    closeButton->setPosition(cocos2d::Vec2(width - closeButton->getContentSize().width / 2, closeButton->getContentSize().height / 2));
    closeButton->addClickEventListener([this](cocos2d::Ref* sender) {
        this->closePanel();
        });
    this->addChild(closeButton);

    return true;
}
NPCInfo* NPCInfo::create() {
    auto ret = new(std::nothrow) NPCInfo();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
//��ʾNPC������Ϣ
void NPCInfo::showResidentInfo(const std::string& name, const std::string& profession, int friendship, int romance) {
    // ����NPC������
    if (nameLabel) {
        nameLabel->setString(name);
    }

    // ����NPC��ְҵ
    if (professionLabel) {
        professionLabel->setString(profession);
    }

    // ��������ֵ
    if (friendshipLabel) {
        std::string friendshipStr = "Friendship: " + std::to_string(friendship);
        friendshipLabel->setString(friendshipStr);
    }

    // ��������ֵ
    if (romanceLabel) {
        std::string romanceStr = "Romance: " + std::to_string(romance);
        romanceLabel->setString(romanceStr);
    }

    // ��ʾ���
    this->setVisible(true);
}
//�ر����
void NPCInfo::closePanel() {
    this->removeFromParent();
}