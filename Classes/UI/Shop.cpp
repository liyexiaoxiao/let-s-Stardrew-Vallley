#include "Shop.h"
#include "player.h"
#include "Tools.h"
#include "ItemStorage.h"
// ���徲̬��Ա����
Shop* Shop::instance = nullptr;
extern Player* mainPlayer;

// ��ʾ�̵�
void Shop::show() {
    this->setVisible(true);
    visible = true;
}
// �����̵�
void Shop::hide() {
    this->setVisible(false);
    visible = false;
}
// ����̵굱ǰ�Ƿ�ɼ�
bool Shop::isVisible() const {
    return visible;
}

bool Shop::init() {
    if (!Layer::init()) {
        return false;
    }
    Tools Tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // �����̵걳��
    auto BG_1_Pos = cocos2d::Vec2(visibleSize.width / 2-150, visibleSize.height / 2);
    auto BG_1 = Tool.addImageToScene("photo/storage/BG.png", BG_1_Pos, 1.7f);
    this->addChild(BG_1, 1);
    auto BG_2_Pos = cocos2d::Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2);
    auto BG_2 = Tool.addImageToScene("photo/storage/BG.png", BG_2_Pos, 1.7f);
    this->addChild(BG_2, 1);
    //��������
    auto Shoper_Pos = cocos2d::Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2);
    auto Shoper = Tool.addImageToScene("photo/storage/shoper.png", Shoper_Pos, 3.0f);
    this->addChild(Shoper, 3);
    //��������
    auto qipao_Pos = cocos2d::Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2 + 150);
    auto qipao = Tool.addImageToScene("photo/storage/qipao.png", qipao_Pos, 0.8f);
    this->addChild(qipao, 2);
    //�����Ի���
    auto SayLabel = Tool.createLabel("Welcome to my shop!", "fonts/Marker Felt.ttf", 24, qipao_Pos);
    this->addChild(SayLabel, 3);
    //�ر��̵�
    auto OkButton = Tool.createButton("photo/storage/ok_button.png", cocos2d::Vec2(visibleSize.width / 2 + 330, visibleSize.height / 2 - 150), 0.8f);
    OkButton->addClickEventListener([=](cocos2d::Ref* sender) {
        hide();
        });
    this->addChild(OkButton, 5);
    // ������ʶ
    auto Sell_Pos = cocos2d::Vec2(BG_1_Pos.x, BG_1_Pos.y + 120);
    auto SellLabel = Tool.createLabel("Sell", "fonts/Marker Felt.ttf", 30, Sell_Pos);
    this->addChild(SellLabel, 2);
    auto Buy_Pos = cocos2d::Vec2(BG_2_Pos.x, BG_2_Pos.y + 120);
    auto BuyLabel = Tool.createLabel("Buy", "fonts/Marker Felt.ttf", 30, Buy_Pos);
    this->addChild(BuyLabel, 2);

    float sell_pos_x, sell_pos_y, buy_pos_x, buy_pos_y;
    sell_pos_x = visibleSize.width / 2 - 230;
    sell_pos_y = visibleSize.height / 2 + 80;
    buy_pos_x = visibleSize.width / 2 + 80;
    buy_pos_y = visibleSize.height / 2 + 80;
    //�����Ʒ-��
    addItem("photo/storage/beer.png", StorageID::BEER, sell_pos_x, sell_pos_y, 0);
    addItem("photo/storage/dumogu.png", StorageID::DUMOGU, sell_pos_x + 50, sell_pos_y, 0);
    addItem("photo/storage/huashu.png", StorageID::HUASHU, sell_pos_x + 100, sell_pos_y, 0);
    addItem("photo/storage/lanmogu.png", StorageID::LANMOGU, sell_pos_x + 150, sell_pos_y, 0);
    addItem("photo/storage/Fish_1.png", StorageID::FISH_A, sell_pos_x, sell_pos_y - 50, 0);
    addItem("photo/storage/Fish_2.png", StorageID::FISH_B, sell_pos_x + 50, sell_pos_y - 50, 0);
    addItem("photo/storage/hongmogu.png", StorageID::HONGMOGU, sell_pos_x + 100, sell_pos_y - 50, 0);
    addItem("photo/storage/beike.png", StorageID::BEIKE, sell_pos_x + 150, sell_pos_y - 50, 0);
    addItem("photo/storage/mutou.png", StorageID::MUTOU, sell_pos_x, sell_pos_y - 100, 0);
    addItem("photo/storage/shitou.png", StorageID::SHITOU, sell_pos_x+50, sell_pos_y - 100, 0);
    //�����Ʒ-��
    addItem("photo/storage/beer.png", StorageID::BEER, buy_pos_x, buy_pos_y, 1);
    addItem("photo/storage/dumogu.png", StorageID::DUMOGU, buy_pos_x + 50, buy_pos_y, 1);
    addItem("photo/storage/feiliao.png", StorageID::FEILIAO, buy_pos_x + 100, buy_pos_y, 1);
    addItem("photo/storage/lanmogu.png", StorageID::LANMOGU, buy_pos_x + 150, buy_pos_y, 1);
    addItem("photo/storage/Fish_1.png", StorageID::FISH_A, buy_pos_x, buy_pos_y - 50, 1);
    addItem("photo/storage/zuanshi.png", StorageID::ZUANSHI, buy_pos_x + 50, buy_pos_y - 50, 1);
    addItem("photo/storage/hongmogu.png", StorageID::HONGMOGU, buy_pos_x + 100, buy_pos_y - 50, 1);
    addItem("photo/storage/fenshuijing.png", StorageID::FENSHUIJING, buy_pos_x + 150, buy_pos_y - 50, 1);
    addItem("photo/storage/shitou.png", StorageID::SHITOU, buy_pos_x , buy_pos_y - 100, 1);
    addItem("photo/storage/mutou.png", StorageID::MUTOU, buy_pos_x + 50, buy_pos_y - 100, 1);
    return true;
}
//������Ʒ
void Shop::addItem(const std::string& itemPhotoPath, StorageID ID, float posX, float posY, bool sign) {

    Tools Tool;
    auto thingButton = cocos2d::ui::Button::create(itemPhotoPath);
    thingButton->setScale(2.8f);
    thingButton->setPosition(cocos2d::Vec2(posX, posY));
    this->addChild(thingButton, 5);

    if (sign == 0) {//��
        thingButton->addClickEventListener([this, ID](cocos2d::Ref* sender) {
            sellItem(ID, 1);  // ���ݰ�ť����
            });
    }
    else {//��
        thingButton->addClickEventListener([this, ID](cocos2d::Ref* sender) {
            buyItem(ID, 1);  // ���ݰ�ť����
            });
    }

}
//������
void Shop::sellItem(StorageID ID, int amount) {
    Tools Tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    ItemStorage& storage = ItemStorage::getInstance();
    int have_num = storage.getItemQuantity(static_cast<int>(ID));
    int sell_money;
    if (have_num > 0) {
        storage.removeItem(ID, amount);
        //���÷����������ؼ۸�
        int a = 50;//��ʼ�۸�����ֵ
        int b = 2;//ƽ������
        int min_price = 10;
        sell_money = a / (have_num + b) + min_price;

        mainPlayer->setMoney(sell_money);
        // ������ʾLabel��������ʾ����
        auto YeslabelPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200);
        std::string AllYesstring="You have sold something and get "+std::to_string(sell_money)+"$";
        auto Yeslabel = Tool.createLabel(AllYesstring, "fonts/Marker Felt.ttf", 32, YeslabelPos);
        this->addChild(Yeslabel, 10);
        auto delay = cocos2d::DelayTime::create(2.0f);
        auto hideAction = cocos2d::FadeOut::create(0.5f);
        Yeslabel->runAction(cocos2d::Sequence::create(delay, hideAction, cocos2d::RemoveSelf::create(), nullptr));
    
    }
    else {
        // ������ʾLabel��������ʾ����
        auto labelPos=cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2-200);
        auto label = Tool.createLabel("You don't have this product!", "fonts/Marker Felt.ttf", 32,labelPos);
        this->addChild(label,10);
        auto delay = cocos2d::DelayTime::create(2.0f);
        auto hideAction = cocos2d::FadeOut::create(0.5f);
        label->runAction(cocos2d::Sequence::create(delay, hideAction, cocos2d::RemoveSelf::create(), nullptr));
    }
}
//����
void Shop::buyItem(StorageID ID, int amount) {
    Tools Tool;
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    ItemStorage& storage = ItemStorage::getInstance();
    int have_num = storage.getItemQuantity(static_cast<int>(ID));
    int buy_money;
    
    //���÷����������ؼ۸�
    int a = 50;//��ʼ�۸�����ֵ
    int b = 2;//ƽ������
    int min_price = 10;
    buy_money = a / (have_num + b) + min_price;
    if (mainPlayer->getMoney() >= buy_money){
        mainPlayer->setMoney(-1 * buy_money);
        storage.addItem(ID, amount);
        auto YeslabelPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200);
        std::string AllYesstring = "You have spent " + std::to_string(buy_money) + "$ to buy something";
        auto Yeslabel = Tool.createLabel(AllYesstring, "fonts/Marker Felt.ttf", 32, YeslabelPos);
        this->addChild(Yeslabel, 10);
        auto delay = cocos2d::DelayTime::create(2.0f);
        auto hideAction = cocos2d::FadeOut::create(0.5f);
        Yeslabel->runAction(cocos2d::Sequence::create(delay, hideAction, cocos2d::RemoveSelf::create(), nullptr));
    }
    else {
        // ������ʾLabel��������ʾ����
        auto labelPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200);
        auto label = Tool.createLabel("You don't have enough money!", "fonts/Marker Felt.ttf", 32, labelPos);
        this->addChild(label, 10);
        auto delay = cocos2d::DelayTime::create(2.0f);
        auto hideAction = cocos2d::FadeOut::create(0.5f);
        label->runAction(cocos2d::Sequence::create(delay, hideAction, cocos2d::RemoveSelf::create(), nullptr));
    }
    
}