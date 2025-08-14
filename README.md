__注意：此项目为__[ttd](https://github.com/GuoYang17/ttd)__的改版，在原基础上加入了帮助、保存和加载功能。原作者GitHub名:GuoYang17__
====================
1. ttd 新
2. ttd (new)
3. ttd 基于旧原文翻译
4. ttd 旧原文 英  
--------------------
# ttd 新

一个基于 ncurses 的简单终端绘图程序。

## 功能特点

- 使用多种颜色和符号进行绘制
- 基于 C 语言和 ncurses 库，因此非常快速且轻量级
- 简单的命令系统
- 帮助系统
- 保存和加载画布功能

## 使用方法

只需运行 `./ttd`

## 快捷键

| 按键              | 动作                 |
| ----------------- | ---------------------- |
| 方向键 / WASD     | 移动光标            |
| 空格键            | 在光标位置绘制         |
| Q / E             | 上一个 / 下一个颜色  |
| O / P             | 第一个 / 最后一个颜色     |
| Z / C             | 上一个 / 下一个符号 |
| K / L             | 第一个 / 最后一个符号    |
| I                 | 橡皮擦                 |
| N                 | 增大画笔大小           |
| M                 | 减小画笔大小      |
| B                 | 重置画笔大小         |
| S                 | 保存画布            |
| L                 | 加载画布            |
| :                 | 命令模式           |
| Esc               | 退出命令模式      |
| X                 | 退出                   |

## 命令

- `:draw` — 在当前位置绘制
- `:draw +N` — 向右绘制 N 次（在边界处停止）
- `:draw -N` — 向左绘制 N 次（在边界处停止）
- `:draw +*` — 向右绘制直到边界
- `:draw -*` — 向左绘制直到边界
- `:draw (N` — 向上绘制 N 次（在边界处停止）
- `:draw )N` — 向下绘制 N 次（在边界处停止）
- `:draw (*` — 向上绘制直到边界
- `:draw )*` — 向下绘制直到边界
- `:move` — 将光标移动到 (1, 1)
- `:move y x` — 将光标移动到 (y, x)
- `:save [文件名]` — 将画布保存到文件（默认：canvas.txt）
- `:load 文件名` — 从文件加载画布
- `:help` — 显示帮助信息
- `:quit` — 退出程序

示例：

```
:draw +10
:draw (*
:move 5 10
:quit
```

## 构建

在您的计算机上安装 `libncurses5-dev`。然后运行：`make`

## 其他

这只是我编程学习的一部分。
====================
# ttd (new)

A simple ncurses-based terminal drawing program.

## Features

- Draw with multiple colors and symbols
- Based on C programming language and ncurses, so it is very fast and lightweight
- Simple command system
- Help system
- Save and load canvas functionality

## How to use

Just run `./ttd`

## Key Bindings

| Key               | Action                 |
| ----------------- | ---------------------- |
| Arrow keys / WASD | Move cursor            |
| Space             | Draw at cursor         |
| Q / E             | Previous / Next color  |
| O / P             | First / Last color     |
| Z / C             | Previous / Next symbol |
| K / L             | First / Last symbol    |
| I                 | Eraser                 |
| N                 | Add Pen Size           |
| M                 | Subtract Pen Size      |
| B                 | Reset Pen Size         |
| S                 | Save canvas            |
| L                 | Load canvas            |
| :                 | Command Mode           |
| Esc               | Quit Command Mode      |
| X                 | Exit                   |

## Commands

- `:draw` — Draw at current position
- `:draw +N` — Draw right N times (stop at border)
- `:draw -N` — Draw left N times (stop at border)
- `:draw +*` — Draw right until border
- `:draw -*` — Draw left until border
- `:draw (N` — Draw up N times (stop at border)
- `:draw )N` — Draw down N times (stop at border)
- `:draw (*` — Draw up until border
- `:draw )*` — Draw down until border
- `:move` — Move cursor to (1, 1)
- `:move y x` — Move cursor to (y, x)
- `:save [filename]` — Save canvas to file (default: canvas.txt)
- `:load filename` — Load canvas from file
- `:help` — Show help information
- `:quit` — Quit the program

Example:

```
:draw +10
:draw (*
:move 5 10
:quit
```

## Build

Install `libncurses5-dev` in your computer. Then run: `make`

## Other

It is just a part of my programming learning.
====================
# 中文翻译(基于原文)旧
# ttd

## 功能特点

- 使用多种颜色和符号进行绘制
- 基于 C 语言和 ncurses 库，因此非常快速且轻量级
- 简单的命令系统

## 使用方法

只需运行 `./ttd`

## 快捷键

| 按键              | 动作                 |
| ----------------- | ---------------------- |
| 方向键 / WASD     | 移动光标            |
| 空格键            | 在光标位置绘制         |
| Q / E             | 上一个 / 下一个颜色  |
| O / P             | 第一个 / 最后一个颜色     |
| Z / C             | 上一个 / 下一个符号 |
| K / L             | 第一个 / 最后一个符号    |
| I                 | 橡皮擦                 |
| N                 | 增大画笔大小           |
| M                 | 减小画笔大小      |
| B                 | 重置画笔大小         |
| S                 | 保存画布            |
| L                 | 加载画布            |
| :                 | 命令模式           |
| Esc               | 退出命令模式      |
| X                 | 退出                   |

## 命令

- `:draw` — 在当前位置绘制
- `:draw +N` — 向右绘制 N 次（在边界处停止）
- `:draw -N` — 向左绘制 N 次（在边界处停止）
- `:draw +*` — 向右绘制直到边界
- `:draw -*` — 向左绘制直到边界
- `:draw (N` — 向上绘制 N 次（在边界处停止）
- `:draw )N` — 向下绘制 N 次（在边界处停止）
- `:draw (*` — 向上绘制直到边界
- `:draw )*` — 向下绘制直到边界
- `:move` — 将光标移动到 (1, 1)
- `:move y x` — 将光标移动到 (y, x)
- `:save [文件名]` — 将画布保存到文件（默认：canvas.txt）
- `:load 文件名` — 从文件加载画布
- `:help` — 显示帮助信息
- `:quit` — 退出程序

示例：

```
:draw +10
:draw (*
:move 5 10
:quit
```

## 构建

在您的计算机上安装 `libncurses5-dev`。然后运行：`make`

## 其他

这只是我编程学习的一部分。
====================
# 原文 旧
# ttd

A simple ncurses-based terminal drawing program.

## Features

- Draw with multiple colors and symbols
- Based on C programming language and ncurses, so it is very fast and lightweight
- Simple command system

## How to use

Just run `./ttd`

## Key Bindings

| Key               | Action                 |
| ----------------- | ---------------------- |
| Arrow keys / WASD | Move cursor            |
| Space             | Draw at cursor         |
| Q / E             | Previous / Next color  |
| O / P             | First / Last color     |
| Z / C             | Previous / Next symbol |
| K / L             | First / Last symbol    |
| I                 | Eraser                 |
| N                 | Add Pen Size           |
| M                 | Subtract Pen Size      |
| B                 | Reset Pen Size         |
| S                 | Save canvas            |
| L                 | Load canvas            |
| :                 | Command Mode           |
| Esc               | Quit Command Mode      |
| X                 | Exit                   |

## Commands

- `:draw` — Draw at current position
- `:draw +N` — Draw right N times (stop at border)
- `:draw -N` — Draw left N times (stop at border)
- `:draw +*` — Draw right until border
- `:draw -*` — Draw left until border
- `:draw (N` — Draw up N times (stop at border)
- `:draw )N` — Draw down N times (stop at border)
- `:draw (*` — Draw up until border
- `:draw )*` — Draw down until border
- `:move` — Move cursor to (1, 1)
- `:move y x` — Move cursor to (y, x)
- `:save [filename]` — Save canvas to file (default: canvas.txt)
- `:load filename` — Load canvas from file
- `:help` — Show help information
- `:quit` — Quit the program

Example:

```
:draw +10
:draw (*
:move 5 10
:quit
```

## Build

Install `libncurses5-dev` in your computer. Then run: `make`

## Other

It is just a part of my programming learning.
