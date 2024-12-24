#include "ItemStorage.h"
#include "ItemIDs.h"
#include <stdexcept>

// 单例获取
ItemStorage& ItemStorage::getInstance() {
    static ItemStorage instance;
    return instance;
}

// 私有构造函数
ItemStorage::ItemStorage() {
    // 初始化物品数量为 0
    itemQuantities.resize(MAX_ITEMS, 0);

    // 初始化物品图标路径
    initializeItems();
}

// 私有析构函数
ItemStorage::~ItemStorage() {}

// 初始化物品图标路径和数量
void ItemStorage::initializeItems() {
    // 为每个物品设置图标路径
    setItemIconPath(StorageID::MUTOU, "photo/storage/mutou.png");
    setItemIconPath(StorageID::SHITOU, "photo/storage/shitou.png");
    setItemIconPath(StorageID::DACONG, "photo/storage/dacong.png");
    setItemIconPath(StorageID::DUMOGU, "photo/storage/dumogu.png");
    setItemIconPath(StorageID::FANGFENGCAO, "photo/storage/fangfengcao.png");
    setItemIconPath(StorageID::HONGMOGU, "photo/storage/hongmogu.png");
    setItemIconPath(StorageID::JIANG, "photo/storage/jiang.png");
    setItemIconPath(StorageID::LANMOGU, "photo/storage/lanmogu.png");
    setItemIconPath(StorageID::LUOBO, "photo/storage/luobo.png");
    setItemIconPath(StorageID::NANGUA, "photo/storage/nangua.png");
    setItemIconPath(StorageID::SHUMEI, "photo/storage/shumei.png");
    setItemIconPath(StorageID::XIAOMAI, "photo/storage/xiaomai.png");
    setItemIconPath(StorageID::ZUANSHI, "photo/storage/zuanshi.png");
    setItemIconPath(StorageID::FENSHUIJING, "photo/storage/fenshuijing.png");
    setItemIconPath(StorageID::QICAIKUANGSHI, "photo/storage/qicaikuangshi.png");
    setItemIconPath(StorageID::FISH_A, "photo/storage/Fish_1.png");
    setItemIconPath(StorageID::FISH_B, "photo/storage/Fish_2.png");
    setItemIconPath(StorageID::FISH_C, "photo/storage/Fish_3.png");
    setItemIconPath(StorageID::FISH_D, "photo/storage/Fish_4.png");
    setItemIconPath(StorageID::BOILED_EGG, "photo/storage/boiled_egg.png");
    setItemIconPath(StorageID::BERRIES, "photo/storage/berries.png");
    setItemIconPath(StorageID::COOKED_FISH, "photo/storage/cooked_fish.png");
    setItemIconPath(StorageID::BEER, "photo/storage/beer.png");
    setItemIconPath(StorageID::FEILIAO, "photo/storage/feiliao.png");
    setItemIconPath(StorageID::HUASHU, "photo/storage/huashu.png");
    setItemIconPath(StorageID::BEIKE, "photo/storage/beike.png");
    setItemIconPath(StorageID::SHANHU, "photo/storage/shanhu.png");
    setItemIconPath(StorageID::LAZIJI, "photo/storage/laziji.png");
    setItemIconPath(StorageID::JUANZHOU, "photo/storage/juanzhou.png");
    setItemIconPath(StorageID::MINE, "photo/storage/mine.png");
    setItemIconPath(StorageID::EGG, "photo/storage/egg.png");
    setItemIconPath(StorageID::NIUNAI, "photo/storage/niunai.png");
    setItemIconPath(StorageID::YANGMAO, "photo/storage/yangmao.png");
    // 设置部分物品的初始数量
    itemQuantities[static_cast<int>(StorageID::MUTOU)] = 600;
    itemQuantities[static_cast<int>(StorageID::SHITOU)] = 600;
    itemQuantities[static_cast<int>(StorageID::DACONG)] = 200;
    itemQuantities[static_cast<int>(StorageID::DUMOGU)] = 10;
    itemQuantities[static_cast<int>(StorageID::FANGFENGCAO)] = 10;
    itemQuantities[static_cast<int>(StorageID::HONGMOGU)] = 210;
    itemQuantities[static_cast<int>(StorageID::JIANG)] = 260;
    itemQuantities[static_cast<int>(StorageID::LANMOGU)] = 10;
    itemQuantities[static_cast<int>(StorageID::LUOBO)] = 10;
    itemQuantities[static_cast<int>(StorageID::NANGUA)] = 210;
    itemQuantities[static_cast<int>(StorageID::SHUMEI)] = 10;
    itemQuantities[static_cast<int>(StorageID::XIAOMAI)] = 10;
    itemQuantities[static_cast<int>(StorageID::ZUANSHI)] = 10;
    itemQuantities[static_cast<int>(StorageID::FENSHUIJING)] = 10;
    itemQuantities[static_cast<int>(StorageID::QICAIKUANGSHI)] = 10;
    itemQuantities[static_cast<int>(StorageID::FEILIAO)] = 10;
    itemQuantities[static_cast<int>(StorageID::MINE)] = 20;
    itemQuantities[static_cast<int>(StorageID::EGG)] = 0;
    itemQuantities[static_cast<int>(StorageID::NIUNAI)] = 0;
    itemQuantities[static_cast<int>(StorageID::YANGMAO)] = 0;
}

// 添加物品
void ItemStorage::addItem(StorageID ID, int amount) {
    int itemID = static_cast<int>(ID);
    if (itemID < 0 || itemID >= MAX_ITEMS) {
        throw std::out_of_range("Invalid itemID");
    }
    itemQuantities[itemID] += amount;  // 增加物品数量
}

// 移除物品
void ItemStorage::removeItem(StorageID ID, int amount) {
    int itemID = static_cast<int>(ID);
    if (itemID < 0 || itemID >= MAX_ITEMS) {
        throw std::out_of_range("Invalid itemID");
    }
    if (itemQuantities[itemID] < amount) {
        throw std::logic_error("Not enough items to remove");
    }
    itemQuantities[itemID] -= amount;  // 减少物品数量
}

// 获取物品数量
int ItemStorage::getItemQuantity(int itemID) const {
    if (itemID < 0 || itemID >= MAX_ITEMS) {
        throw std::out_of_range("Invalid itemID");
    }
    return itemQuantities[itemID];
}

// 获取物品图标路径
std::string ItemStorage::getItemIconPath(int itemID) const {
    if (itemID < 0 || itemID >= MAX_ITEMS) {
        throw std::out_of_range("Invalid itemID");
    }
    auto it = itemIconPaths.find(itemID);
    if (it != itemIconPaths.end()) {
        return it->second;
    }
    return "";  // 如果未找到路径，返回空字符串
}

// 设置物品图标路径
void ItemStorage::setItemIconPath(StorageID ID, const std::string& path) {
    int itemID = static_cast<int>(ID);
    if (itemID < 0 || itemID >= MAX_ITEMS) {
        throw std::out_of_range("Invalid itemID");
    }
    itemIconPaths[itemID] = path;
}