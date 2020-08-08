# Description
Used **STM32F103**, **LCD Screen** and **Matrix Keyboard** to achieve "+", "-", "*", "/" and operations with brackets

[中文版本!](https://github.com/Kexin-Tang/Calculator)

![Calculator.png](https://i.loli.net/2020/08/08/EaPH6ThXvwnueZj.png)

----
# Pins Assignment

Parts | Type
----|:----:
Embedded Chip|STM32F103
LCD Screen |LCD1602-5V

Pins | LCD Pins
----------|:----------:
GND       | 1, 16
VCC       | 2, 3, 15
PC13      | 4(RS)
PC14      | 5(RW)
PC15      | 6(EN)
PA0~7     | 7~14(DB0~7)

Pins | Keyboard
----------|: -------:
PB4~7     | row
PB12~15   | col

----
# Keyboard Assignment
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
# Functions

* Using **stack** to achieve bracket matching
* Using **nested vector interrupt system** to achieve *pressing detection* and *key without jitter*
* LCD is used to display the formula, and the screen brightness can be adjusted by sliding rheostat at the bottom of the screen
* It can save the result of the last calculation and utilize it through the *ANS* key
