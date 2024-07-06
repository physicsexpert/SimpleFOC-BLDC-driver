# 项目简介
主要技术方案采用SimpleFoc，主控芯片采用ESP32模组，驱动芯片使用DRV8313，电流采样芯片采用INA199，可以驱动两路带编码器的无刷电机。

<img src=picture/AdWIgMhK2bCL5GJ33nmXmBWWS5gPIubUDsHZDpyN.jpeg width=50% />
<img src=picture/peTHgNELNo7OnheFytLxN6cdYVJ1PxNy4Pa9DMnS.jpeg width=50% />
<img src=picture/qZ66wLYQ4V7P8rpM6NiEBqIqAkB49yHfawNPQKqE.jpeg width=50% />
<img src=picture/0HDxo8IRM7GcT2FgbbebIhXV2MPNrl9LxxvudG3n.jpeg width=50% />
<img src=picture/gZeYQfZDzireu5fIR0ds1P1ZklRd1Y51lduXPFRu.jpeg width=50% />


## 项目链接
### 立创开源平台链接：https://oshwhub.com/expert/xin-shuang-lu-simplefoc-wu-shua-dian-ji-qu-dong-qi-yi-shi-pei-deng-ge-foc-cheng-xu

## 关于硬件
本项目的硬件使用嘉立创eda专业版设计，分为两个部分，分别是驱动板和电机编码器底板，驱动板比较重要编码器驱动板可以选择性制作，我设计的编码器驱动板使用AS5600芯片，兼容4010云台电机和2804云台电机。

控制板的主控芯片采用ESP32模组，驱动芯片使用DRV8313，电流采样芯片采用INA199，可以驱动两路带编码器的无刷电机，供电为12V,输出最大电流不超过2A，建议使用低功率的无刷云台电机，板载两路iic，一路can，一路usart接口电路，支持位置/速度开环，位置环，速度环，电流环，支持Arduino编程和ESPIDF，已经适配灯哥foc的Arduino开源程序，具体代码见software文件夹。
## 关于软件
软件代码适配灯哥开源示例程序，使用了simplefoc的arduino库，目前我使用的电机是4010无刷云台电机和2804无刷云台电机，使用其他电机需要重新调整驱动程序中的pid参数。

## 参考工程
### https://github.com/ToanTech/Deng-s-foc-controller
### https://github.com/ToanTech/DengFOC_Lib
