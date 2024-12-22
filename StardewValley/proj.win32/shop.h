#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tools.h"
#include "ItemIDs.h"
#include "ItemStorage.h"
class Shop : public cocos2d::Layer {
public:
    Shop() : visible(false) {}
    ~Shop() {}

    // ��ȡ Shop ʵ��
    static Shop* getInstance() {
        if (instance == nullptr) {
            instance = new Shop();
            if (!instance->init()) {
                delete instance;
                instance = nullptr;
            }
        }
        return instance;
    }
    // �̵��ʼ��
    bool init();
    // ��ʾ�̵�
    void show();
    // �����̵�
    void hide();
    // ����̵굱ǰ�Ƿ�ɼ�
    bool isVisible() const;
    //������Ʒ
    void addItem(const std::string& itemPhotoPath, StorageID ID, float posX, float posY, bool sign);
    //������
    void sellItem(StorageID ID, int amount);
    //����
    void buyItem(StorageID ID, int amount);
private:
    static Shop* instance;  // ����ʵ��
    bool visible;  // ��¼����������ʾ״̬
};
