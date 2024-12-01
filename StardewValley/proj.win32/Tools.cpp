#include "Tools.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
// 增添精灵
cocos2d::Sprite* Tools::addImageToScene(const std::string& imageFile, const cocos2d::Vec2& position, const float scale)
{
    // 创建精灵
    auto sprite = Sprite::create(imageFile);
    if (sprite != nullptr) {
        // 设置精灵的位置
        sprite->setPosition(position);
        sprite->setScale(scale);
        // 需要将精灵手动添加到场景
    }
    else {
        CCLOG("Failed to load image: %s", imageFile.c_str());
        return nullptr; // 返回空指针表示失败
    }

    return sprite; // 返回创建的 sprite
}

// 创建标签的函数实现
cocos2d::Label* Tools::createLabel(const std::string& text, const std::string& font, int fontSize, const cocos2d::Vec2& position) {
    // 创建Label
    auto label = cocos2d::Label::createWithTTF(text, font, fontSize);
    // 设置Label的位置
    label->setPosition(position);
    label->setTextColor(cocos2d::Color4B::BLACK);
    // 返回创建的Label对象
    return label;
}

// 创建文本框的函数实现
cocos2d::ui::TextField* Tools::createTextField(const cocos2d::Vec2& position) {
    auto textField = ui::TextField::create("Click and Enter", "fonts/Marker Felt.ttf", 24);
    textField->setPosition(position);  // 设置文本框位置
    textField->setMaxLength(10);  // 设置最大输入字符数
    textField->setTextColor(Color4B::BLACK);  // 设置文本颜色
    textField->setTouchEnabled(true); // 启用触摸

    // 设置文本框的事件监听器
    textField->addEventListener([=](Ref* sender, ui::TextField::EventType event) {
        switch (event) {
            case ui::TextField::EventType::ATTACH_WITH_IME: // 聚焦时
                CCLOG("TextField: attach with ime");
                if (textField->getString() == "Enter name") {
                    textField->setString("");  // 清空占位符文本
                }
                break;
            case ui::TextField::EventType::DETACH_WITH_IME: // 失去焦点时
                CCLOG("TextField: detach with ime");
                if (textField->getString().empty()) {
                    textField->setString("Enter name");
                }
                break;
            case ui::TextField::EventType::INSERT_TEXT: // 输入文本时
                CCLOG("TextField: inserted text");
                break;
            case ui::TextField::EventType::DELETE_BACKWARD: // 删除时
                CCLOG("TextField: delete backward");
                break;
            default:
                break;
        }
        });
    return textField;
}