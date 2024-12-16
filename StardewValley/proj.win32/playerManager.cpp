#include "playerManager.h"

// ��̬��Ա������ʼ��
PlayerManager* PlayerManager::_instance = nullptr;

// ˽�й��캯��
PlayerManager::PlayerManager() : _player(nullptr) {
    // ������Խ���һЩ��ʼ�����������紴�����ʵ��
    // _player = Player::create();
}

// ��ȡ����ʵ���ķ���
PlayerManager* PlayerManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new PlayerManager();
    }
    return _instance;
}

// ���ٵ���ʵ���ķ���
void PlayerManager::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

