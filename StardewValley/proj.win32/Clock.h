#ifndef CLOCK_H
#define CLOCK_H

#include "cocos2d.h"

class Clock : public cocos2d::Node {

public:
    static Clock* getInstance();  // ��ȡ����ʵ��
    void startClock();  // ����ʱ��
    void stopClock();   // ֹͣʱ��
    void setTimeafterSleep(int hour, int minute, int second); //���ù̶�ʱ�䣨�𴲺�
    void updateClock(float deltaTime);  // ÿ֡����ʱ��
    void setTimeDisplay();             // ������Ļ����ʾ��ʱ��

    // ��ֹ�ⲿ���ù��캯��
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;

    int getYear() const { return year; }
    int getDay() const { return day; }
    std::string getWeek() const { return Week; }
    std::string getSeason() const { return Season; }

private:
    Clock();  // ˽�й��캯������ֹ�ⲿʵ����
    ~Clock(); // ˽����������

    static Clock* instance;  // ����ָ��

    float gameTime;                   // ��Ϸʱ�䣬����Ϊ��λ
    cocos2d::Label* timeLabel;        // ��ʾʱ��ı�ǩ
    cocos2d::Label* dayLabel;
    cocos2d::Sprite* ClockPhoto;      // ʱ��ͼ��
    cocos2d::Sprite* seasonImage;     //����ͼ��
    int year = 1;
    int day = 1; // ��ʼ������
    std::string Week = ""; // ��ʼ������
    std::string Season = "Spring"; // ��ʼ������
};

#endif // CLOCK_H
