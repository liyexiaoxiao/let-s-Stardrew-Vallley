#pragma once
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "ItemIDs.h"
class ItemStorage {
public:
    // 获取单例实例
    static ItemStorage& getInstance();

    // 禁止拷贝和赋值
    ItemStorage(const ItemStorage&) = delete;
    ItemStorage& operator=(const ItemStorage&) = delete;

    // 修改物品数量
    void addItem(StorageID ID, int amount);       // 增加物品
    void removeItem(StorageID ID, int amount);    // 减少物品
    int getItemQuantity(int itemID) const;      // 获取物品数量

    // 获取物品图标路径
    std::string getItemIconPath(int itemID) const;
    //设置物品图标路径
    void setItemIconPath(StorageID ID, const std::string& path);
    // 初始化物品图标路径
    void initializeItems();

private:
    ItemStorage();   // 私有构造函数
    ~ItemStorage();  // 私有析构函数

    static const int MAX_ITEMS = 60;  // 最大物品数量

    std::vector<int> itemQuantities;  // 存储每个物品的数量
    std::unordered_map<int, std::string> itemIconPaths;  // 存储物品ID与图标路径的映射
};
