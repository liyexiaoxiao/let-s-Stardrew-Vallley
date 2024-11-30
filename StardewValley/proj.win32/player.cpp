//ĿǰΪgyx11/30����ʹ�ã�����
#include "Player.h"

USING_NS_CC;

Player::Player() : health(100), speed(100.0f) {} // ��ʼ�����Ĭ������

Player::~Player() {}

Player* Player::create(const std::string& filename) {
    Player* ret = new Player();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Player::init(const std::string& filename) {
    if (!Sprite::init()) {
        return false;
    }

    // ������ҽ�ɫ��ͼ��
    this->initWithFile(filename);
    this->setVisible(true);

    return true;
}

void Player::move(const Vec2& direction, float distance) {
    Vec2 newPosition = this->getPosition() + direction * distance;
    this->setPosition(newPosition); // �������λ��
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getHealth() const {
    return health;
}

void Player::setSpeed(float speed) {
    this->speed = speed;
}

float Player::getSpeed() const {
    return speed;
}
