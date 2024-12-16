#pragma once
// PlayerManager.h
#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "player.h"

class PlayerManager {
private:
    static PlayerManager* _instance;
    Player* _player;

    PlayerManager(); // ˽�й��캯��
public:
    static PlayerManager* getInstance();
    static void destroyInstance();
    Player* getPlayer() { return _player; }
    void setPlayer(Player* player) { _player = player; }
    // ...��������������ݵķ���
};

#endif // PLAYER_MANAGER_H