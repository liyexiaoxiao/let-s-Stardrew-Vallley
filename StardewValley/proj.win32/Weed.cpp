//ĿǰΪgyx11/30����ʹ����δ���ԣ�����
#include "Weed.h"

Weed::Weed() : removed(false) {}

Weed::~Weed() {}

Weed* Weed::create() {
    Weed* ret = new Weed();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Weed::init() {
    if (!Sprite::init()) {
        return false;
    }

    // �����Ӳݵ�ͼ��
    this->initWithFile("weed.png");
    this->setVisible(true);

    return true;
}

void Weed::removeWeed() {
    this->setVisible(false);  // �����Ӳ�
    removed = true;  // ����Ϊ���Ƴ�
}
