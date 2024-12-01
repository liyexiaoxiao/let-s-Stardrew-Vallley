#ifndef CLOCK_H
#define CLOCK_H

#include "cocos2d.h"

// ����ȫ�ֱ���
extern int day;
extern std::string Week;
extern std::string Season;

class Clock : public cocos2d::Node {
public:
    Clock();
    ~Clock();

    static Clock* create();
    void startClock();  // ����ʱ��
    void stopClock();   // ֹͣʱ��

    void updateClock(float deltaTime);  // ÿ֡����ʱ��
    void setTimeDisplay();             // ������Ļ����ʾ��ʱ��

private:
    float gameTime;                   // ��Ϸʱ�䣬����Ϊ��λ
    cocos2d::Label* timeLabel;        // ��ʾʱ��ı�ǩ
    cocos2d::Label* dayLabel;
    cocos2d::Sprite* ClockPhoto;      // ʱ��ͼ��
    cocos2d::Sprite* seasonImage;     //����ͼ��
};


#endif // CLOCK_H
