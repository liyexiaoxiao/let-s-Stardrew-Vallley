#include "InitialScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "Tools.h"
using namespace cocos2d;

InitialScene::InitialScene() {
    CCLOG("InitialScene constructed");
}

// 析构函数
InitialScene::~InitialScene() {
    CCLOG("InitialScene destructed");
}
// 创建场景
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = InitialScene::create();
    scene->addChild(layer); // 使用 CREATE_FUNC 宏生成场景
    return scene;
}

// 初始化场景
bool InitialScene::init()
{
    Tools Tool;
    if (!Scene::init()) {
        return false;
    }
    
    // 获取屏幕尺寸
    const auto screenSize = Director::getInstance()->getVisibleSize();
    auto setGroundPosition = Vec2(screenSize.width / 2, screenSize.height / 2);

    // 设置背景
    auto background = Sprite::create("photo/startup_p/StartupScene.png");
    if (background == nullptr) {
        CCLOG("Background image loading failed for GameScene!");
    }
    else {
        background->setPosition(setGroundPosition);
        background->setContentSize(screenSize);
        this->addChild(background, 0);
    }

    // 放置小背景 SetGround
    auto SetGround=Tool.addImageToScene("photo/startup_p/SetGround.png", setGroundPosition, 2.0f);
    this->addChild(SetGround);
    // 获取 SetGround 精灵的高度
    float SetGroundHeight = SetGround->getContentSize().height;
    float SetGroundWidth = SetGround->getContentSize().width;
    // 获取 SetGround 的左上角位置
    Vec2 setGroundLeftTop = setGroundPosition + Vec2(-SetGroundWidth / 2, SetGroundHeight / 2);
    //位置设定
    Vec2 CharacterPosition= setGroundLeftTop + Vec2(-80, -30);
    Vec2 NameLabelPosition = setGroundLeftTop + Vec2(130, 50);
    
    //放置人物背景
    auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterPosition, 0.8f);
    CharacterGround->setPosition(CharacterPosition);
    this->addChild(CharacterGround);
    //放置人物
    Vec2 CharacterGroundPos = CharacterGround->getPosition();
    auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterGroundPos, 4.0f);
    this->addChild(PlayerPhoto);

    // 输入文本框
    Vec2 PlayerNamePos = NameLabelPosition + Vec2(200, 0);
    Vec2 FarmNamePosition = PlayerNamePos + Vec2(0, -80);
    auto PlayerNameTxt = Tool.createTextField(PlayerNamePos);
    auto FarmNameTxt = Tool.createTextField(FarmNamePosition);
    auto textBox1=Tool.addImageToScene("photo/startup_p/textBox.png", PlayerNamePos, 1.0f);
    auto textBoxl2 = Tool.addImageToScene("photo/startup_p/textBox.png", FarmNamePosition, 1.0f);
    this->addChild(textBox1);
    this->addChild(textBoxl2);
    // 创建显示用户输入的 Label
    auto DisplayLabel = Tool. createLabel("", "fonts/Marker Felt.ttf", 24, PlayerNamePos);
    this->addChild(DisplayLabel);  
    auto DisplayLabel2 = Tool.createLabel("", "fonts/Marker Felt.ttf", 24, FarmNamePosition);
    this->addChild(DisplayLabel2);  

    auto FarmType=Tool.addImageToScene("photo/startup_p/FarmType.png", FarmNamePosition + Vec2(0, -100), 0.8f);
    this->addChild(FarmType);
    // 自动在点击文本框后开始输入，且实时更新 DisplayLabel
    PlayerNameTxt->addEventListener([=](Ref* sender, ui::TextField::EventType event) {
        if (event == ui::TextField::EventType::INSERT_TEXT || event == ui::TextField::EventType::DELETE_BACKWARD) {
            // 获取文本框中的文本
            std::string enteredText = PlayerNameTxt->getString();
            // 更新显示的 Label
            DisplayLabel->setString(enteredText);  // 更新文本
        }
        });
    FarmNameTxt->addEventListener([=](Ref* sender, ui::TextField::EventType event) {
        if (event == ui::TextField::EventType::INSERT_TEXT || event == ui::TextField::EventType::DELETE_BACKWARD) {
            // 获取文本框中的文本
            std::string enteredText = FarmNameTxt->getString();
            // 更新显示的 Label
            DisplayLabel2->setString(enteredText);  // 更新文本
        }
        });
    // 将文本框添加到场景中
    this->addChild(PlayerNameTxt);
    this->addChild(FarmNameTxt);

    // 创建 Label
    auto NameLabel = Tool.createLabel("Your Name:", "fonts/Marker Felt.ttf", 24, NameLabelPosition);
    this->addChild(NameLabel);
    auto FarmLabel= Tool.createLabel("Your Farm Name:", "fonts/Marker Felt.ttf", 24, NameLabelPosition + Vec2(0, -80));
    this->addChild(FarmLabel);
    auto FarmTypeLabel= Tool.createLabel("Your Farm Type:", "fonts/Marker Felt.ttf", 24, NameLabelPosition + Vec2(0, -160));
    this->addChild(FarmTypeLabel);

    // 以下为 gyx 为了测试地图以及游玩而写的按钮代码

     //创建按钮,确定键
    auto startButton = cocos2d::ui::Button::create("photo/startup_p/ok.png");
    // 设置按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2+300, screenSize.height / 4+50));
    // 设置按钮大小，确保按钮不会超出屏幕
    startButton->setScale(0.8f);  // 可根据需要调整按钮大小

    // 设置按钮点击事件，连接到第一个画面：农场！！！
    startButton->addClickEventListener([=](Ref* sender) {
        // 切换到游戏场景
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    return true;
}
