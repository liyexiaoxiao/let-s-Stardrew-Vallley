#ifndef TILLEDLAND_H
#define TILLEDLAND_H

#include "cocos2d.h"
#include <vector>

class TilledLand : public cocos2d::Sprite {
public:
    static TilledLand* create();
    bool init() override;

    // 开垦土地的方法
    static TilledLand* tillLand(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<TilledLand*>>& tilledLand);
};

#endif // TILLEDLAND_H
