//��ͼ����������
#include "Mine.h"

Mine::Mine() : removed(false) {
    // ָ����Ҷ����ָ��
}

Mine::~Mine() {}

Mine* Mine::create() {
    Mine* ret = new Mine();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool Mine::init() {
    if (!Sprite::init()) {
        return false;
    }
    // ���ѡ�����ͼ��
    int randomIndex = rand() % mineImages.size();  // ��ȡ�������
    this->initWithFile(mineImages[randomIndex]);  // �����������ѡ�����ͼ��
    this->setVisible(true);

    return true;
}

void Mine::removeMine() {
    this->initWithFile("photo/Adventure/nomine.png");//��ͼ�����׮
    removed = true;  // ����Ϊ���Ƴ�
}

//����ÿ�ո���
void Mine::reset() {
    if (removed) {
        // ���ѡ�����ͼ��
        int randomIndex = rand() % mineImages.size();  // ��ȡ�������
        this->initWithFile(mineImages[randomIndex]);  // �����������ѡ�����ͼ��
        removed = false;  // ���Ϊδ�Ƴ�
    }
}

cocos2d::Rect Mine::getBoundingBox() const {
    // ��ȡ������������
    auto position = this->getPosition();

    // ��ȡ���ĳߴ�
    auto contentSize = this->getContentSize();

    // �������İ�Χ��
    return cocos2d::Rect(
        position.x - contentSize.width * this->getAnchorPoint().x,  // ���Ͻ� X ����
        position.y - contentSize.height * this->getAnchorPoint().y, // ���Ͻ� Y ����
        contentSize.width,  // ���
        contentSize.height  // �߶�
    );
}
