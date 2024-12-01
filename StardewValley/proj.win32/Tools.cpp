#include "Tools.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
// ������
cocos2d::Sprite* Tools::addImageToScene(const std::string& imageFile, const cocos2d::Vec2& position, const float scale)
{
    // ��������
    auto sprite = Sprite::create(imageFile);
    if (sprite != nullptr) {
        // ���þ����λ��
        sprite->setPosition(position);
        sprite->setScale(scale);
        // ��Ҫ�������ֶ���ӵ�����
    }
    else {
        CCLOG("Failed to load image: %s", imageFile.c_str());
        return nullptr; // ���ؿ�ָ���ʾʧ��
    }

    return sprite; // ���ش����� sprite
}

// ������ǩ�ĺ���ʵ��
cocos2d::Label* Tools::createLabel(const std::string& text, const std::string& font, int fontSize, const cocos2d::Vec2& position) {
    // ����Label
    auto label = cocos2d::Label::createWithTTF(text, font, fontSize);
    // ����Label��λ��
    label->setPosition(position);
    label->setTextColor(cocos2d::Color4B::BLACK);
    // ���ش�����Label����
    return label;
}

// �����ı���ĺ���ʵ��
cocos2d::ui::TextField* Tools::createTextField(const cocos2d::Vec2& position) {
    auto textField = ui::TextField::create("Click and Enter", "fonts/Marker Felt.ttf", 24);
    textField->setPosition(position);  // �����ı���λ��
    textField->setMaxLength(10);  // ������������ַ���
    textField->setTextColor(Color4B::BLACK);  // �����ı���ɫ
    textField->setTouchEnabled(true); // ���ô���

    // �����ı�����¼�������
    textField->addEventListener([=](Ref* sender, ui::TextField::EventType event) {
        switch (event) {
            case ui::TextField::EventType::ATTACH_WITH_IME: // �۽�ʱ
                CCLOG("TextField: attach with ime");
                if (textField->getString() == "Enter name") {
                    textField->setString("");  // ���ռλ���ı�
                }
                break;
            case ui::TextField::EventType::DETACH_WITH_IME: // ʧȥ����ʱ
                CCLOG("TextField: detach with ime");
                if (textField->getString().empty()) {
                    textField->setString("Enter name");
                }
                break;
            case ui::TextField::EventType::INSERT_TEXT: // �����ı�ʱ
                CCLOG("TextField: inserted text");
                break;
            case ui::TextField::EventType::DELETE_BACKWARD: // ɾ��ʱ
                CCLOG("TextField: delete backward");
                break;
            default:
                break;
        }
        });
    return textField;
}