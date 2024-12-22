//��ͼ����������
#include "Tree.h"

Tree::Tree() : removed(false) {
    // ָ����Ҷ����ָ��
}

Tree::~Tree() {}

Tree* Tree::create() {
    Tree* ret = new Tree();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool Tree::init() {
    if (!Sprite::init()) {
        return false;
    }
    // ��������ͼ��
    this->initWithFile("photo/Farm/tree.png");
    this->setVisible(true);

    return true;
}

void Tree::removeTree() {
    this->initWithFile("photo/Farm/tree2.png");//��ͼ�����׮
    removed = true;  // ����Ϊ���Ƴ�
}
//����ÿ�ո���
void Tree::reset() {
    if (removed) {
        this->initWithFile("photo/Farm/tree.png");  // �ָ�Ϊ��
        removed = false;  // ���Ϊδ�Ƴ�
    }
}

cocos2d::Rect Tree::getBoundingBox() const {
    // ��ȡ������������
    auto position =  this->getPosition();

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

