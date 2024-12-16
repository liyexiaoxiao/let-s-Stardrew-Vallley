#include "playerManager.h"

// 静态成员变量初始化
PlayerManager* PlayerManager::_instance = nullptr;

// 私有构造函数
PlayerManager::PlayerManager() : _player(nullptr) {
    // 这里可以进行一些初始化操作，例如创建玩家实例
    // _player = Player::create();
}

// 获取单例实例的方法
PlayerManager* PlayerManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new PlayerManager();
    }
    return _instance;
}

// 销毁单例实例的方法
void PlayerManager::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

