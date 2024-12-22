#include "Clock.h"
#include "Tools.h"

Clock* Clock::instance = nullptr;  // ��ʼ������ָ��Ϊ nullptr

Clock::Clock() : gameTime(0), timeLabel(nullptr), ClockPhoto(nullptr), dayLabel(nullptr), seasonImage(nullptr), weatherImage(nullptr){}

Clock::~Clock() {}

Clock* Clock::getInstance() {
    if (instance == nullptr) {
        instance = new Clock();  // ��������ʵ��
        instance->retain();  // �������ü���
    }
    return instance;  // ���ص�������
}

void Clock::startClock() {
    CCLOG("Clock started");
    schedule([this](float deltaTime) {
        updateClock(deltaTime);
        }, "clock_update_key");
}

void Clock::updateClock(float deltaTime) {
    CCLOG("Updating clock, gameTime: %f", gameTime);
    gameTime += deltaTime / 0.01f;//����ɷ���
    // ��һ�����ʱ���� gameTime
    if (gameTime >= 1440) { // 1440 ���Ӽ�Ϊһ��
        gameTime = 0;  // ����ʱ��
        notifyGameTimeReset();
        day++;  // ����һ��
    }
    setTimeDisplay();
}

void Clock::setTimeafterSleep(int hour, int minute, int second) {
    day++;
    // ������Ϸʱ�䣨��λ�����ӣ�
    gameTime = 0;
    setTimeDisplay(); // ������ʾ
}

void Clock::setTimeDisplay() {
    Tools Tool;
    // ����Ϸʱ��ת��ΪСʱ�ͷ���
    int inithours = 6;
    int deltahours = static_cast<int>(gameTime) / 60;
    int minutes = static_cast<int>(gameTime) % 60;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ��������
    if (gameTime >= 1440) {
        day++;
    }

    year = day / 112;
    // �ı����ڼ�
    switch (day % 7) {
        case 0: Week = "Sun"; break;
        case 1: Week = "Mon"; break;
        case 2: Week = "Tue"; break;
        case 3: Week = "Wed"; break;
        case 4: Week = "Thu"; break;
        case 5: Week = "Fri"; break;
        case 6: Week = "Sat"; break;
        default: break;
    }

    // ���ü���------------------------------------
    std::string newSeason;
    switch ((day / 28) % 4) {
        case 0: newSeason = "Spring"; break;
        case 1: newSeason = "Summer"; break;
        case 2: newSeason = "Autumn"; break;
        case 3: newSeason = "Winter"; break;
        default: break;
    }

    // ������ڱ仯�����¼���ͼƬ
    if (newSeason != Season) {
        Season = newSeason;

        // ����ɵļ���ͼƬ���������
        if (seasonImage) {
            seasonImage->removeFromParent();
        }

        // ���ݼ��ڼ��ز�ͬ��ͼƬ
        std::string imageFileName;
        if (Season == "Spring") {
            imageFileName = "photo/ui/Spring.png";
        }
        else if (Season == "Summer") {
            imageFileName = "photo/ui/Summer.png";
        }
        else if (Season == "Autumn") {
            imageFileName = "photo/ui/Autumn.png";
        }
        else if (Season == "Winter") {
            imageFileName = "photo/ui/Winter.png";
        }

        auto seasonImagePos = cocos2d::Vec2(visibleSize.width - 150, visibleSize.height - 90);
        seasonImage = Tool.addImageToScene(imageFileName, seasonImagePos, 3.0f);
        this->addChild(seasonImage,10);
    }
    // ��������------------------------------------
    std::string newWeather="Sunny";
    if (day%2==0) {
        newWeather = "Rainy";
    }

    // ��������仯����������ͼƬ
    if (newWeather != Weather) {
        Weather = newWeather;

        // ����ɵ�����ͼƬ���������
        if (weatherImage) {
            weatherImage->removeFromParent();
        }

        // �����������ز�ͬ��ͼƬ
        std::string imageFileName;
        if (Weather == "Sunny") {
            imageFileName = "photo/ui/Sunny.png";
        }
        else if (Weather == "Rainy") {
            imageFileName = "photo/ui/Rainy.png";
        }

        auto weatherImagePos = cocos2d::Vec2(visibleSize.width - 80, visibleSize.height - 90);
        weatherImage = Tool.addImageToScene(imageFileName, weatherImagePos, 3.0f);
        this->addChild(weatherImage, 10);
    }

    // ���ʱ��ͼƬ��û�д������򴴽���
    if (!ClockPhoto) {
        auto ClockPhotoPos = cocos2d::Vec2(visibleSize.width - 150, visibleSize.height - 120);
        ClockPhoto = Tool.addImageToScene("photo/ui/Clock.png", ClockPhotoPos, 3.0f);
        ClockPhoto->setLocalZOrder(1000);
        this->addChild(ClockPhoto);
    }

    // ������Ļ�ϵ�ʱ����ʾ
    if (!timeLabel) {
        auto timeLabelPos = cocos2d::Vec2(visibleSize.width - 110, visibleSize.height - 130);
        timeLabel = Tool.createLabel("", "fonts/Marker Felt.ttf", 24, timeLabelPos);
        timeLabel->setLocalZOrder(1000);
        this->addChild(timeLabel);
    }

    // ȷ�� dayLabel �Ѿ���ʼ��
    if (!dayLabel) {
        auto dayLabelPos = cocos2d::Vec2(visibleSize.width - 110, visibleSize.height - 60);
        dayLabel = Tool.createLabel("", "fonts/Marker Felt.ttf", 24, dayLabelPos);
        dayLabel->setLocalZOrder(1000);
        this->addChild(dayLabel);
    }

    // ����ʱ���ǩ�����ڱ�ǩ
    timeLabel->setString(cocos2d::StringUtils::format("%02d:%02d", (inithours + deltahours) % 24, minutes));
    dayLabel->setString(cocos2d::StringUtils::format("%s  %d", Week.c_str(), day));

    // ȷ�����ڵ�ɼ�
    this->setVisible(true);
}
