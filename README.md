# let-s-Stardrew-Vallley
本仓库用于2024同济大学程序设计范式期末大作业星露谷物语设计项目！

## 项目名称

Stardew_Valley_Farm

## 项目简介

该项目是一个基于 [cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual/) 开发的星露谷农村游戏。
该游戏是一个农场生活模拟游戏，玩家将管理自己的农场。

## 成员分工

|姓名|学号|分工|
| :----:| :----: | :----: |
|关云兮(组长)|       |项目任务分工<br>共同修改`FarmScene`类 |
|张诗蔻|2353240|<br>`Crop`类 <br>`FarmHouseScene`类 <br> `calendar`类 <br> `tiledland`类<br>`WateredLand`类 <br>`钓鱼功能` <br>`烹饪功能`<br>共同修改`FarmScene`类|
|李烨|2351127|<br>`InitialScene`类<br>共同修改`FarmScene`类及`StartupScene`类<br>`Shop`类<br>`Tool`类<br>`TaskBar`类<br>`Clock`类<br>`ItemStorage`类<br>`Menulayer`类<br>`Toolbar`类<br>(内容包括时间、工具栏、菜单、背包、任务栏等UI组件及部分场景)|

## 成员贡献

|姓名|学号|代码量|工作量|
| :----:| :----: | :----: | :----: |
|关云兮(组长)|       |    |    |
|张诗蔻|2353240|    |    |
|李烨|2351127|    |   |

## 项目组成

* `/Resources`
资源文件

* `/proj.win32`
游戏程序 类定义与类实现

## 项目实现功能与项目技术细节

### 实现功能

* [X] 有初始界面和设置界面
* [X] 支持人物的自由移动、物体碰撞
* [X] 支持多种农场活动，包括砍树、挖矿、耕田、种地、钓鱼
* [X] 有多种NPC，支持与NPC对话、购买商品、完成委托

## 项目开发日志

### 2024/11/23

- Python 环境配置
- Cmake 环境配置
- cocos2d-x 4.0 环境配置
  
### 2024/11/24

- 放弃cocos2d-x 4.0，转而使用cocos2d-x 3.17.2

### 2024/11/27

- 学习cocos2d-x
  
### 2024/11/28-30

- 搭建仓库

### 2024/12/5

- 初步实现 `tilledland` 类

### 2024/12/6

- 初步实现 `Crop` 类
- 讨论并解决现有疑问

### 2024/12/10

- 基本实现 `Crop` 类中的作物种植和生长

### 2024/12/14


### 2024/12/15

- 初步实现 `FarmHouseScene` 类

### 2024/12/17

- 初步实现 `WateredLand` 类
- 实现 `FarmHouse` 类

### 2024/12/18

- 完善 `FarmHouseScene` 类

### 2024/12/19

- 初步实现钓鱼功能
- 完善种植范围

### 2024/12/21

- 完善钓鱼功能
- 完善 `FarmHouseScene` 类，实现烹饪功能
- 实现每天早上六点植物状态的重置

### 2024/12/22

- 完善 `calendar` 类
- 完善节日功能
- 完善测试游戏功能，美化界面
- 完善项目说明文档
- 制作答辩PPT
