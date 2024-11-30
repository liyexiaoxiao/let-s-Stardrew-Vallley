//目前为gyx11/30测试使用且未测试！！！
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

    // 设置杂草的图像
    this->initWithFile("weed.png");
    this->setVisible(true);

    return true;
}

void Weed::removeWeed() {
    this->setVisible(false);  // 隐藏杂草
    removed = true;  // 设置为已移除
}
