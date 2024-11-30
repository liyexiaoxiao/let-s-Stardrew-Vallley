#include "Crop.h"

Crop::Crop(const std::string& name, const std::vector<std::string>& stages)
    : name(name), currentAge(0), stages(stages) {
    sprite = cocos2d::Sprite::create(stages[0]);
}

void Crop::grow() {
    if (currentAge < stages.size() - 1) {
        currentAge++;
        sprite->setTexture(stages[currentAge]); // ¸üÐÂÍ¼Æ¬
    }
}

bool Crop::isMature() const {
    return currentAge == stages.size() - 1;
}

cocos2d::Sprite* Crop::getSprite() const {
    return sprite;
}

void Crop::setPosition(cocos2d::Vec2 position) {
    sprite->setPosition(position);
}
