#ifndef CLOCK_H
#define CLOCK_H

#include "cocos2d.h"

// 声明全局变量
extern int day;
extern std::string Week;
extern std::string Season;

class Clock : public cocos2d::Node {
public:
    Clock();
    ~Clock();

    static Clock* create();
    void startClock();  // 启动时钟
    void stopClock();   // 停止时钟

    void updateClock(float deltaTime);  // 每帧更新时钟
    void setTimeDisplay();             // 更新屏幕上显示的时间

private:
    float gameTime;                   // 游戏时间，以秒为单位
    cocos2d::Label* timeLabel;        // 显示时间的标签
    cocos2d::Label* dayLabel;
    cocos2d::Sprite* ClockPhoto;      // 时钟图像
    cocos2d::Sprite* seasonImage;     //季节图像
};


#endif // CLOCK_H
