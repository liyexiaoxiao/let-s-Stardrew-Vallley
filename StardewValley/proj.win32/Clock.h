#ifndef CLOCK_H
#define CLOCK_H

#include "cocos2d.h"

class Clock : public cocos2d::Node {

public:
    static Clock* getInstance();  // 获取单例实例
    void startClock();  // 启动时钟
    void stopClock();   // 停止时钟
    void setTimeafterSleep(int hour, int minute, int second); //设置固定时间（起床后）
    void updateClock(float deltaTime);  // 每帧更新时钟
    void setTimeDisplay();             // 更新屏幕上显示的时间

    // 防止外部调用构造函数
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;

    int getYear() const { return year; }
    int getDay() const { return day; }
    std::string getWeek() const { return Week; }
    std::string getSeason() const { return Season; }

private:
    Clock();  // 私有构造函数，防止外部实例化
    ~Clock(); // 私有析构函数

    static Clock* instance;  // 单例指针

    float gameTime;                   // 游戏时间，以秒为单位
    cocos2d::Label* timeLabel;        // 显示时间的标签
    cocos2d::Label* dayLabel;
    cocos2d::Sprite* ClockPhoto;      // 时钟图像
    cocos2d::Sprite* seasonImage;     //季节图像
    int year = 1;
    int day = 1; // 初始化天数
    std::string Week = ""; // 初始化星期
    std::string Season = "Spring"; // 初始化季节
};

#endif // CLOCK_H
