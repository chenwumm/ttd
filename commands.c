#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "cursor.h"
#include "commands.h"
#include "utils.h"

void save_canvas(const char *filename) {
    FILE *file = fopen(filename, "wb");  // 以二进制模式打开文件
    if (file == NULL) {
        // 显示错误信息
        move(LINES - 1, 0);
        clrtoeol();
        mvprintw(LINES - 1, 0, "Error: Cannot save to %s", filename);
        refresh();
        return;
    }
    
    // 保存画布内容（不包括边框）
    for (int y = 1; y < LINES - 2; y++) {
        for (int x = 1; x < COLS - 1; x++) {
            chtype ch = mvinch(y, x);  // 获取完整的字符和属性信息
            // 保存chtype值（包含字符和颜色属性）
            fwrite(&ch, sizeof(chtype), 1, file);
        }
        // 用换行符分隔行
        fputc('\n', file);
    }
    
    fclose(file);
    
    // 显示成功信息
    move(LINES - 1, 0);
    clrtoeol();
    mvprintw(LINES - 1, 0, "Saved to %s", filename);
    refresh();
    
    // 注意：我们不能直接访问main.c中的canvas_modified变量
    // 需要在main.c中处理这个标志
}

void load_canvas(const char *filename) {
    FILE *file = fopen(filename, "rb");  // 以二进制模式打开文件
    if (file == NULL) {
        // 显示错误信息
        move(LINES - 1, 0);
        clrtoeol();
        mvprintw(LINES - 1, 0, "Error: Cannot load from %s", filename);
        refresh();
        return;
    }
    
    // 清空当前画布
    for (int y = 1; y < LINES - 2; y++) {
        for (int x = 1; x < COLS - 1; x++) {
            mvaddch(y, x, ' ');
        }
    }
    
    // 从文件加载内容（包含颜色信息）
    for (int y = 0; y < LINES - 3; y++) {
        for (int x = 0; x < COLS - 2; x++) {
            chtype ch;
            // 读取chtype值（包含字符和颜色属性）
            if (fread(&ch, sizeof(chtype), 1, file) != 1) {
                fclose(file);
                move(LINES - 1, 0);
                clrtoeol();
                mvprintw(LINES - 1, 0, "Error: File format incorrect");
                refresh();
                return;
            }
            
            // 使用mvaddch直接设置字符和颜色属性
            mvaddch(y + 1, x + 1, ch);
        }
        // 跳过换行符
        fgetc(file);
    }
    
    fclose(file);
    
    // 显示成功信息
    move(LINES - 1, 0);
    clrtoeol();
    mvprintw(LINES - 1, 0, "Loaded from %s", filename);
    refresh();
}

void show_help() {
    // 清屏并显示帮助信息
    clear();
    
    // 显示标题
    move(1, (COLS - 20) / 2);
    addstr("=== TTD 终端画板帮助 ===");
    
    // 显示快捷键说明
    move(3, 2);
    addstr("=== 快捷键说明 ===");
    move(4, 4);
    addstr("方向键/WASD  - 移动光标");
    move(5, 4);
    addstr("空格键       - 在光标位置绘制");
    move(6, 4);
    addstr("I            - 橡皮擦");
    move(7, 4);
    addstr("Q/E          - 切换颜色");
    move(8, 4);
    addstr("O/P          - 切换到第一个/最后一个颜色");
    move(9, 4);
    addstr("Z/C          - 切换符号");
    move(10, 4);
    addstr("K/L          - 切换到第一个/最后一个符号");
    move(11, 4);
    addstr("N/M          - 减小/增大画笔粗细");
    move(12, 4);
    addstr("B            - 重置画笔粗细");
    move(13, 4);
    addstr("S            - 保存画布到 canvas.txt");
    move(14, 4);
    addstr("L            - 从 canvas.txt 加载画布");
    move(15, 4);
    addstr("X            - 退出程序");
    move(16, 4);
    addstr(":            - 进入命令模式");
    
    // 显示命令模式说明
    move(18, 2);
    addstr("=== 命令模式说明 ===");
    move(19, 4);
    addstr(":draw        - 在当前位置绘制");
    move(20, 4);
    addstr(":draw +N     - 向右绘制N次");
    move(21, 4);
    addstr(":draw -N     - 向左绘制N次");
    move(22, 4);
    addstr(":draw +*     - 向右绘制到边界");
    move(23, 4);
    addstr(":draw -*     - 向左绘制到边界");
    move(24, 4);
    addstr(":draw (N     - 向上绘制N次");
    move(25, 4);
    addstr(":draw )N     - 向下绘制N次");
    move(26, 4);
    addstr(":draw (*     - 向上绘制到边界");
    move(27, 4);
    addstr(":draw )*     - 向下绘制到边界");
    move(28, 4);
    addstr(":move        - 移动光标到(1,1)");
    move(29, 4);
    addstr(":move y x    - 移动光标到(y,x)");
    move(30, 4);
    addstr(":save [文件名] - 保存画布到文件(默认: canvas.txt)");
    move(31, 4);
    addstr(":load 文件名  - 从文件加载画布");
    move(32, 4);
    addstr(":help        - 显示帮助信息");
    move(33, 4);
    addstr(":quit        - 退出程序");
    
    // 显示提示信息
    move(LINES - 2, 2);
    addstr("按任意键返回...");
    refresh();
    
    // 等待用户按键
    getch();
    
    // 重新绘制界面
    clear();
    draw_border();
}

void parse_and_exec_cmd(const char *cmd, Cursor *cursor, int color, char symbol)
{
    if (strncmp(cmd, "save", 4) == 0)
    {
        const char *arg = cmd + 4;
        while (*arg == ' ') arg++;
        if (*arg != '\0') {
            save_canvas(arg);
        } else {
            save_canvas("canvas.txt");
        }
    }
    else if (strncmp(cmd, "load", 4) == 0)
    {
        const char *arg = cmd + 4;
        while (*arg == ' ') arg++;
        if (*arg != '\0') {
            load_canvas(arg);
        } else {
            move(LINES - 1, 0);
            clrtoeol();
            mvprintw(LINES - 1, 0, "Error: Please specify a file to load");
            refresh();
        }
    }
    else if (strncmp(cmd, "help", 4) == 0)
    {
        show_help();
    }
    else if (strncmp(cmd, "draw", 4) == 0)
    {
        const char *arg = cmd + 4;
        while (*arg == ' ')
            arg++;
        if (*arg == '\0')
        {
            cursor_draw(cursor, color, symbol, 1);
        }
        else if (*arg == '+' || *arg == '-')
        {
            int dir = (*arg == '+') ? 1 : -1;
            arg++;
            if (isdigit(*arg))
            {
                int n = atoi(arg);
                for (int i = 0; i < n; i++)
                {
                    if (dir == 1 && cursor->x < COLS - 2)
                    {
                        cursor_move_right(cursor);
                        cursor_draw(cursor, color, symbol, 1);
                    }
                    else if (dir == -1 && cursor->x > 1)
                    {
                        cursor_move_left(cursor);
                        cursor_draw(cursor, color, symbol, 1);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (*arg == '*')   // 持续绘制直到边界
            {
                while ((dir == 1 && cursor->x < COLS - 2) || (dir == -1 && cursor->x > 1))
                {
                    if (dir == 1)
                        cursor_move_right(cursor);
                    else
                        cursor_move_left(cursor);
                    cursor_draw(cursor, color, symbol, 1);
                }
            }
        }
        else if (*arg == '(' || *arg == ')')
        {
            int dir = (*arg == '(') ? -1 : 1; // ( 向上, ) 向下
            arg++;
            if (isdigit(*arg))
            {
                int n = atoi(arg);
                for (int i = 0; i < n; i++)
                {
                    if (dir == 1 && cursor->y < LINES - 3)
                    {
                        cursor_move_down(cursor);
                        cursor_draw(cursor, color, symbol, 1);
                    }
                    else if (dir == -1 && cursor->y > 1)
                    {
                        cursor_move_up(cursor);
                        cursor_draw(cursor, color, symbol, 1);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (*arg == '*')   // 持续绘制直到边界
            {
                while ((dir == 1 && cursor->y < LINES - 3) || (dir == -1 && cursor->y > 1))
                {
                    if (dir == 1)
                        cursor_move_down(cursor);
                    else
                        cursor_move_up(cursor);
                    cursor_draw(cursor, color, symbol, 1);
                }
            }
        }
    }
    else if (strncmp(cmd, "move", 4) == 0)
    {
        const char *arg = cmd + 4;
        while (*arg == ' ') arg++;
        if (*arg == '\0') {
            cursor->y = 1;
            cursor->x = 1;
            cursor_move(cursor);
        } else {
            int y = 1, x = 1;
            if (sscanf(arg, "%d %d", &y, &x) == 2) {
                if (y < 1) y = 1;
                if (x < 1) x = 1;
                if (y > LINES-3) y = LINES-3;
                if (x > COLS-2) x = COLS-2;
                cursor->y = y;
                cursor->x = x;
                cursor_move(cursor);
            }
        }
    }
    else if (strncmp(cmd, "quit", 4) == 0)
    {
        endwin();
        exit(0);
    }
}
