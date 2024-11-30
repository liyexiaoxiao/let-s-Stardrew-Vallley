//目前为gyx11/30测试使用！！！
#include "Player.h"

USING_NS_CC;

Player::Player() : health(100), speed(100.0f) {} // 初始化玩家默认属性

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

    // 设置玩家角色的图像
    this->initWithFile(filename);
    this->setVisible(true);

    return true;
}

void Player::move(const Vec2& direction, float distance) {
    Vec2 newPosition = this->getPosition() + direction * distance;
    this->setPosition(newPosition); // 更新玩家位置
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
