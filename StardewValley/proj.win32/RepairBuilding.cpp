#include "RepairBuilding.h"

RepairBuilding::RepairBuilding(const std::string& broken, const std::string& fixed)
    : brokenImage(broken), fixedImage(fixed), repairProgress(0), repairTime(10.0f), isRepairing(false), isRepaired(false) {
    // ����������
    repairProgressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("photo/startup_p/textBox.png"));
    repairProgressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    repairProgressBar->setBarChangeRate(cocos2d::Vec2(1, 0));  // ˮƽ������
    repairProgressBar->setMidpoint(cocos2d::Vec2(0, 0));  // ������
    repairProgressBar->setPercentage(0);  // ��ʼ����Ϊ 0
    repairProgressBar->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -20));  // ���ý�������λ��
    repairProgressBar->setLocalZOrder(5);  // ���ý�������Σ�ȷ�����ڽ�����֮��
    this->addChild(repairProgressBar);  // �����������뵽��������
}

RepairBuilding::~RepairBuilding() {
    // ���������������Ҫ�Ļ�
     // �����޸���ʱ��
    if (repairProgressBar) {
        repairProgressBar->removeFromParent();
    }
}

// ��̬��������
RepairBuilding* RepairBuilding::create(const std::string& brokenImage, const std::string& fixedImage) {
    RepairBuilding* ret = new RepairBuilding(brokenImage, fixedImage);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RepairBuilding::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ʹ�û�������ͼ����г�ʼ��
    this->initWithFile(brokenImage);
    this->setVisible(true);  // ȷ��ͼ��ɼ�

    return true;
}

void RepairBuilding::startRepair() {
    if (isRepairing) return;
    isRepairing = true;

    // �޸����ȣ�ÿ�����һ��
    schedule([this](float dt) {
        this->repairProgress += dt / repairTime;  // ÿ������޸�����
        repairProgressBar->setPercentage(repairProgress * 100);  // ���½���������ʾ

        // ����޸���ɣ���������޸��ĺ���
        if (repairProgress >= 1.0f) {
            completeRepair();  // �޸����
        }
        }, 1.0f, "repair_schedule_key");  // ÿ�����һ��
}

void RepairBuilding::completeRepair() {
    unschedule("repair_schedule_key");  // ֹͣ�޸�����
    repairProgress = 1.0f;  // �޸����
    repairProgressBar->setPercentage(100);  // ���½�����
    // �л����޸���Ľ���ͼ��
    this->setTexture(fixedImage);
    isRepaired = true;
    // ����������һЩ����Ч����չʾ�޸���ɺ�Ľ��
    cocos2d::FadeIn* fadeIn = cocos2d::FadeIn::create(0.5f);
    this->runAction(fadeIn);
    // ���ؽ�����
    repairProgressBar->setVisible(false);


}

cocos2d::Rect RepairBuilding::getBoundingBox() const {
    // ��ȡ��������������
    const auto position = this->getPosition();

    // ��ȡ�����ĳߴ�
    const auto contentSize = this->getContentSize();

    // �������İ�Χ��
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,  // ���Ͻ� X ����
        position.y - contentSize.height * this->getAnchorPoint().y, // ���Ͻ� Y ����
        contentSize.width,  // ���
        contentSize.height  // �߶�
    );
}