#ifndef CLOCK_H
#define CLOCK_H

#include "cocos2d.h"

enum class rainyday {

};

class Clock : public cocos2d::Node {

public:
    static Clock* getInstance();  // ��ȡ����ʵ��
    void startClock();  // ����ʱ��
    void stopClock();   // ֹͣʱ��
    void setTimeafterSleep(int hour, int minute, int second); //���ù̶�ʱ�䣨�𴲺�
    void updateClock(float deltaTime);  // ÿ֡����ʱ��
    void setTimeDisplay();             // ������Ļ����ʾ��ʱ��
    float getGameTime() const { return gameTime; }

    // ��ֹ�ⲿ���ù��캯��
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;

    int getYear() const { return year; }
    int getDay() const { return day; }
    std::string getWeek() const { return Week; }
    std::string getSeason() const { return Season; }
    std::string getWeather()const { return Weather; }
    void onGameTimeReset(const std::function<void()>& callback) {
        callbacks.push_back(callback);
    }

private:
    Clock();  // ˽�й��캯������ֹ�ⲿʵ����
    ~Clock(); // ˽����������

    static Clock* instance;  // ����ָ��

    float gameTime;                   // ��Ϸʱ�䣬����Ϊ��λ
    cocos2d::Label* timeLabel;        // ��ʾʱ��ı�ǩ
    cocos2d::Label* dayLabel;         // ��ʾ�����ı�ǩ
    cocos2d::Sprite* ClockPhoto;      // ʱ��ͼ��
    cocos2d::Sprite* seasonImage;     //����ͼ��
    cocos2d::Sprite* weatherImage;     //����ͼ��
    int year = 1; // ��ʼ�����
    int day = 1; // ��ʼ������
    std::string Week = ""; // ��ʼ������
    std::string Season = ""; // ��ʼ������
    std::string Weather = "";// ��ʼ������
    std::set<int> rainyDays;  // �洢�ض�������

    std::vector<std::function<void()>> callbacks;
    void notifyGameTimeReset() {
        for (const auto& callback : callbacks) {
            callback();
        }
    }
};

#endif // CLOCK_H
