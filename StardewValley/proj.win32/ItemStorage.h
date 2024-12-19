#pragma once
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "ItemIDs.h"
class ItemStorage {
public:
    // ��ȡ����ʵ��
    static ItemStorage& getInstance();

    // ��ֹ�����͸�ֵ
    ItemStorage(const ItemStorage&) = delete;
    ItemStorage& operator=(const ItemStorage&) = delete;

    // �޸���Ʒ����
    void addItem(StorageID ID, int amount);       // ������Ʒ
    void removeItem(StorageID ID, int amount);    // ������Ʒ
    int getItemQuantity(int itemID) const;      // ��ȡ��Ʒ����

    // ��ȡ��Ʒͼ��·��
    std::string getItemIconPath(int itemID) const;
    //������Ʒͼ��·��
    void setItemIconPath(StorageID ID, const std::string& path);
    // ��ʼ����Ʒͼ��·��
    void initializeItems();

private:
    ItemStorage();   // ˽�й��캯��
    ~ItemStorage();  // ˽����������

    static const int MAX_ITEMS = 60;  // �����Ʒ����

    std::vector<int> itemQuantities;  // �洢ÿ����Ʒ������
    std::unordered_map<int, std::string> itemIconPaths;  // �洢��ƷID��ͼ��·����ӳ��
};
