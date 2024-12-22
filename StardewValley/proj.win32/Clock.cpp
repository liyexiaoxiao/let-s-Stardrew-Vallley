#include "Clock.h"
#include "Tools.h"

Clock* Clock::instance = nullptr;  // 初始化单例指针为 nullptr

Clock::Clock() : gameTime(0), timeLabel(nullptr), ClockPhoto(nullptr), dayLabel(nullptr), seasonImage(nullptr), weatherImage(nullptr){}

Clock::~Clock() {}

Clock* Clock::getInstance() {
    if (instance == nullptr) {
        instance = new Clock();  // 创建单例实例
        instance->retain();  // 增加引用计数
    }
    return instance;  // 返回单例对象
}

void Clock::startClock() {
    CCLOG("Clock started");
    schedule([this](float deltaTime) {
        updateClock(deltaTime);
        }, "clock_update_key");
}

void Clock::updateClock(float deltaTime) {
    CCLOG("Updating clock, gameTime: %f", gameTime);
    gameTime += deltaTime / 0.01f;//换算成分钟
    // 当一天结束时重置 gameTime
    if (gameTime >= 1440) { // 1440 分钟即为一天
        gameTime = 0;  // 重置时间
        notifyGameTimeReset();
        day++;  // 增加一天
    }
    setTimeDisplay();
}

void Clock::setTimeafterSleep(int hour, int minute, int second) {
    day++;
    // 计算游戏时间（单位：分钟）
    gameTime = 0;
    setTimeDisplay(); // 更新显示
}

void Clock::setTimeDisplay() {
    Tools Tool;
    // 将游戏时间转化为小时和分钟
    int inithours = 6;
    int deltahours = static_cast<int>(gameTime) / 60;
    int minutes = static_cast<int>(gameTime) % 60;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 更新天数
    if (gameTime >= 1440) {
        day++;
    }

    year = day / 112;
    // 改变星期几
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

    // 设置季节------------------------------------
    std::string newSeason;
    switch ((day / 28) % 4) {
        case 0: newSeason = "Spring"; break;
        case 1: newSeason = "Summer"; break;
        case 2: newSeason = "Autumn"; break;
        case 3: newSeason = "Winter"; break;
        default: break;
    }

    // 如果季节变化，更新季节图片
    if (newSeason != Season) {
        Season = newSeason;

        // 清除旧的季节图片，如果存在
        if (seasonImage) {
            seasonImage->removeFromParent();
        }

        // 根据季节加载不同的图片
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
    // 设置天气------------------------------------
    std::string newWeather="Sunny";
    if (day%2==0) {
        newWeather = "Rainy";
    }

    // 如果天气变化，更新天气图片
    if (newWeather != Weather) {
        Weather = newWeather;

        // 清除旧的天气图片，如果存在
        if (weatherImage) {
            weatherImage->removeFromParent();
        }

        // 根据天气加载不同的图片
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

    // 如果时钟图片还没有创建，则创建它
    if (!ClockPhoto) {
        auto ClockPhotoPos = cocos2d::Vec2(visibleSize.width - 150, visibleSize.height - 120);
        ClockPhoto = Tool.addImageToScene("photo/ui/Clock.png", ClockPhotoPos, 3.0f);
        ClockPhoto->setLocalZOrder(1000);
        this->addChild(ClockPhoto);
    }

    // 更新屏幕上的时间显示
    if (!timeLabel) {
        auto timeLabelPos = cocos2d::Vec2(visibleSize.width - 110, visibleSize.height - 130);
        timeLabel = Tool.createLabel("", "fonts/Marker Felt.ttf", 24, timeLabelPos);
        timeLabel->setLocalZOrder(1000);
        this->addChild(timeLabel);
    }

    // 确保 dayLabel 已经初始化
    if (!dayLabel) {
        auto dayLabelPos = cocos2d::Vec2(visibleSize.width - 110, visibleSize.height - 60);
        dayLabel = Tool.createLabel("", "fonts/Marker Felt.ttf", 24, dayLabelPos);
        dayLabel->setLocalZOrder(1000);
        this->addChild(dayLabel);
    }

    // 更新时间标签和日期标签
    timeLabel->setString(cocos2d::StringUtils::format("%02d:%02d", (inithours + deltahours) % 24, minutes));
    dayLabel->setString(cocos2d::StringUtils::format("%s  %d", Week.c_str(), day));

    // 确保父节点可见
    this->setVisible(true);
}
