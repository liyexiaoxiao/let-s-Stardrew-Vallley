#ifndef __TOOLS_H__
#define __TOOLS_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace std;

class Tools {
public:
	Tools() {};
	~Tools() {};
	// 添加图片到场景
	cocos2d::Sprite* addImageToScene(const std::string& imageFile, const cocos2d::Vec2& position, const float scale);
	// 创建文本框的函数声明
	cocos2d::ui::TextField* createTextField(const cocos2d::Vec2& position);
	//创建标签的函数声明
	cocos2d::Label* createLabel(const std::string& text, const std::string& font, int fontSize, const cocos2d::Vec2& position);
	//创建按钮的函数声明
	cocos2d::ui::Button* createButton(const std::string& normalImage, const cocos2d::Vec2& position, float scale = 1.0);
};
#endif // __TOOLS_H__
#pragma once