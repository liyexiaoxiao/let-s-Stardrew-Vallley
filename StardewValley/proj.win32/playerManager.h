#pragma once
// PlayerManager.h
#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "player.h"

class PlayerManager {
private:
    static PlayerManager* _instance;
    Player* _player;

    PlayerManager(); // 私有构造函数
public:
    static PlayerManager* getInstance();
    static void destroyInstance();
    Player* getPlayer() { return _player; }
    void setPlayer(Player* player) { _player = player; }
    // ...其他管理玩家数据的方法
};

#endif // PLAYER_MANAGER_H