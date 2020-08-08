# 功能描述
使用**STM32F103**最小系统、**LCD**屏幕及**矩阵键盘**实现基础的计算器功能，即"+", "-", "*", "/"以及括号运算。

[ENGLISH VERSION!](https://github.com/Kexin-Tang/Calculator/blob/master/README_EN.md)

![Calculator.png](https://i.loli.net/2020/08/08/EaPH6ThXvwnueZj.png)

----
# 引脚分配

部件 | 型号
----|:----:
单片机|STM32F103
显示屏|LCD1602-5V

单片机引脚 | LCD屏幕引脚
----------|:----------:
GND       | 1, 16
VCC       | 2, 3, 15
PC13      | 4(RS)
PC14      | 5(RW)
PC15      | 6(EN)
PA0~7     | 7~14(DB0~7)

单片机引脚 | 矩阵键盘
----------|: -------:
PB4~7     | 矩阵行
PB12~15   | 矩阵列

----
# 键盘分布
<table>
    <tr>
        <td>(</td>
        <td>)</td>
        <td>CE</td>
        <td>/</td>
    </tr>
    <tr>
        <td>7</td>
        <td>8</td>
        <td>9</td>
        <td>*</td>
    </tr>
    <tr>
        <td>4</td>
        <td>5</td>
        <td>6</td>
        <td>-</td>
    </tr>
    <tr>
        <td>1</td>
        <td>2</td>
        <td>3</td>
        <td>+</td>
    </tr>
    <tr>
        <td>.</td>
        <td>0</td>
        <td>ANS</td>
        <td>=</td>
    </tr>
</table>


----
# 功能

* 使用栈实现括号的匹配
* 使用中断系统实现按键的检测及防抖
* 使用LCD进行公式的显示，可通过屏幕下方的滑动变阻器调节屏幕亮度
* 能够保存上一次计算的结果，通过*ANS*键进行调用
