#ifndef WATEREDLAND_H
#define WATEREDLAND_H

#include "cocos2d.h"
#include <vector>

class WateredLand : public cocos2d::Sprite {
public:
    static WateredLand* create();
    bool init() override;

    // 开垦土地的方法
    static WateredLand* waterLand(int x, int y, cocos2d::TMXTiledMap* map, std::vector<std::vector<WateredLand*>>& wateredLand);
};

#endif // WATEREDLAND_H
