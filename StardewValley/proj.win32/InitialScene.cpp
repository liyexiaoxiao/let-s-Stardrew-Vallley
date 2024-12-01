#include "InitialScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FarmScene.h"
#include "Tools.h"
using namespace cocos2d;

InitialScene::InitialScene() {
    CCLOG("InitialScene constructed");
}

// ��������
InitialScene::~InitialScene() {
    CCLOG("InitialScene destructed");
}
// ��������
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = InitialScene::create();
    scene->addChild(layer); // ʹ�� CREATE_FUNC �����ɳ���
    return scene;
}

// ��ʼ������
bool InitialScene::init()
{
    Tools Tool;
    if (!Scene::init()) {
        return false;
    }
    
    // ��ȡ��Ļ�ߴ�
    const auto screenSize = Director::getInstance()->getVisibleSize();
    auto setGroundPosition = Vec2(screenSize.width / 2, screenSize.height / 2);

    // ���ñ���
    auto background = Sprite::create("photo/startup_p/StartupScene.png");
    if (background == nullptr) {
        CCLOG("Background image loading failed for GameScene!");
    }
    else {
        background->setPosition(setGroundPosition);
        background->setContentSize(screenSize);
        this->addChild(background, 0);
    }

    // ����С���� SetGround
    auto SetGround=Tool.addImageToScene("photo/startup_p/SetGround.png", setGroundPosition, 2.0f);
    this->addChild(SetGround);
    // ��ȡ SetGround ����ĸ߶�
    float SetGroundHeight = SetGround->getContentSize().height;
    float SetGroundWidth = SetGround->getContentSize().width;
    // ��ȡ SetGround �����Ͻ�λ��
    Vec2 setGroundLeftTop = setGroundPosition + Vec2(-SetGroundWidth / 2, SetGroundHeight / 2);
    //λ���趨
    Vec2 CharacterPosition= setGroundLeftTop + Vec2(-80, -30);
    Vec2 NameLabelPosition = setGroundLeftTop + Vec2(130, 50);
    
    //�������ﱳ��
    auto CharacterGround = Tool.addImageToScene("photo/startup_p/Character Backgrounds.png", CharacterPosition, 0.8f);
    CharacterGround->setPosition(CharacterPosition);
    this->addChild(CharacterGround);
    //��������
    Vec2 CharacterGroundPos = CharacterGround->getPosition();
    auto PlayerPhoto = Tool.addImageToScene("photo/Character/PlayerFront1.png", CharacterGroundPos, 4.0f);
    this->addChild(PlayerPhoto);

    // �����ı���
    Vec2 PlayerNamePos = NameLabelPosition + Vec2(200, 0);
    Vec2 FarmNamePosition = PlayerNamePos + Vec2(0, -80);
    auto PlayerNameTxt = Tool.createTextField(PlayerNamePos);
    auto FarmNameTxt = Tool.createTextField(FarmNamePosition);
    auto textBox1=Tool.addImageToScene("photo/startup_p/textBox.png", PlayerNamePos, 1.0f);
    auto textBoxl2 = Tool.addImageToScene("photo/startup_p/textBox.png", FarmNamePosition, 1.0f);
    this->addChild(textBox1);
    this->addChild(textBoxl2);
    // ������ʾ�û������ Label
    auto DisplayLabel = Tool. createLabel("", "fonts/Marker Felt.ttf", 24, PlayerNamePos);
    this->addChild(DisplayLabel);  
    auto DisplayLabel2 = Tool.createLabel("", "fonts/Marker Felt.ttf", 24, FarmNamePosition);
    this->addChild(DisplayLabel2);  

    auto FarmType=Tool.addImageToScene("photo/startup_p/FarmType.png", FarmNamePosition + Vec2(0, -100), 0.8f);
    this->addChild(FarmType);
    // �Զ��ڵ���ı����ʼ���룬��ʵʱ���� DisplayLabel
    PlayerNameTxt->addEventListener([=](Ref* sender, ui::TextField::EventType event) {
        if (event == ui::TextField::EventType::INSERT_TEXT || event == ui::TextField::EventType::DELETE_BACKWARD) {
            // ��ȡ�ı����е��ı�
            std::string enteredText = PlayerNameTxt->getString();
            // ������ʾ�� Label
            DisplayLabel->setString(enteredText);  // �����ı�
        }
        });
    FarmNameTxt->addEventListener([=](Ref* sender, ui::TextField::EventType event) {
        if (event == ui::TextField::EventType::INSERT_TEXT || event == ui::TextField::EventType::DELETE_BACKWARD) {
            // ��ȡ�ı����е��ı�
            std::string enteredText = FarmNameTxt->getString();
            // ������ʾ�� Label
            DisplayLabel2->setString(enteredText);  // �����ı�
        }
        });
    // ���ı�����ӵ�������
    this->addChild(PlayerNameTxt);
    this->addChild(FarmNameTxt);

    // ���� Label
    auto NameLabel = Tool.createLabel("Your Name:", "fonts/Marker Felt.ttf", 24, NameLabelPosition);
    this->addChild(NameLabel);
    auto FarmLabel= Tool.createLabel("Your Farm Name:", "fonts/Marker Felt.ttf", 24, NameLabelPosition + Vec2(0, -80));
    this->addChild(FarmLabel);
    auto FarmTypeLabel= Tool.createLabel("Your Farm Type:", "fonts/Marker Felt.ttf", 24, NameLabelPosition + Vec2(0, -160));
    this->addChild(FarmTypeLabel);

    // ����Ϊ gyx Ϊ�˲��Ե�ͼ�Լ������д�İ�ť����

     //������ť,ȷ����
    auto startButton = cocos2d::ui::Button::create("photo/startup_p/ok.png");
    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2+300, screenSize.height / 4+50));
    // ���ð�ť��С��ȷ����ť���ᳬ����Ļ
    startButton->setScale(0.8f);  // �ɸ�����Ҫ������ť��С

    // ���ð�ť����¼������ӵ���һ�����棺ũ��������
    startButton->addClickEventListener([=](Ref* sender) {
        // �л�����Ϸ����
        auto transition = cocos2d::TransitionFade::create(1.0f, FarmScene::create(), cocos2d::Color3B::WHITE);
        cocos2d::Director::getInstance()->replaceScene(transition);
        });
    this->addChild(startButton);

    return true;
}
