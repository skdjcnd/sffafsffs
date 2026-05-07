#include "food.h"
#include "snake.h"
#include "tools.h"
#include <cstdlib>//rand()函数，srand()函数的头文件，用以生成食物的随机位置
#include <iostream>


void Food::DrawFood(Snake& csnake)//
{
    
    while (true)
    {
        int tmp_x = rand() % 29;//改动处，原来的30会导致食物出现在边界上
        int tmp_y = rand() % 29;//改动处，原来的30会导致食物出现在边界上
        if (tmp_x < 2) tmp_x += 2;
        if (tmp_y < 2) tmp_y += 2;
        bool flag = false;
		for (auto it = csnake.snake.begin();it != csnake.snake.end();++it)//确保食物不会出现在蛇身上或者大食物的位置上
        {
            if ((it->GetX() == tmp_x && it->GetY() == tmp_y) || (tmp_x == big_x && tmp_y == big_y)) {
                flag = true;
                break;
            }
        }
        if (flag) continue;
        x = tmp_x;
        y = tmp_y;
        SetCursorPosition(x, y);
        SetColor(13);//设置颜色为淡紫色
        std::cout << "\u2605";
        ++cnt;
        cnt %= 5;
        if (cnt == 0)
        {
            DrawBigFood(csnake);
        }
        break;
    }
}

void Food::DrawBigFood(Snake& csnake)//绘制大食物
{
    SetCursorPosition(5, 0);
    SetColor(11);//设置颜色为淡蓝色
    std::cout << "------------------------------------------";//模拟倒计时
    progress_bar = 42;//上面这个横线的长度为42
    while (true)
    {
        int tmp_x = rand() % 29;//改动处，原来的30会导致食物出现在边界上
        int tmp_y = rand() % 29;//改动处，原来的30会导致食物出现在边界上
        if (tmp_x < 2) tmp_x += 2;
        if (tmp_y < 2) tmp_y += 2;
        bool flag = false;//判断生成的位置是否合法
		for (auto it = csnake.snake.begin();it != csnake.snake.end();++it)//判断食物不会出现在蛇身上或者普通食物的位置上
        {
            if ((it->GetX() == tmp_x && it->GetY() == tmp_y) || (tmp_x == x && tmp_y == y))
            {
                flag = true;
                break;
            }
        }
        if (flag) continue;//如果位置不合法，就跳过以下代码，继续生成随机位置

        big_x = tmp_x;
        big_y = tmp_y;
        SetCursorPosition(big_x, big_y);
        SetColor(18);//设置颜色为绿色
        std::cout << "\u25A0";//输出一个实心方块
		big_flag = true;//大食物出现
        flash_flag = true;//控制闪动
        break;
    }
}

int Food::GetCnt()//获取吃到普通食物的次数
{
    return cnt;
}

void Food::FlashBigFood()//闪烁大食物
{
    SetCursorPosition(big_x, big_y);
    SetColor(18);//设置颜色为绿色
    if (flash_flag)//交替输出空格和方块来实现闪烁效果
    {
        std::cout << " ";//
        flash_flag = false;
    }
    else
    {
		std::cout << "\u25A0";//输出一个实心方块
        flash_flag = true;
    }

	SetCursorPosition(26, 0);//移到进度条最右端
    SetColor(11);//设置颜色为淡蓝色
    for (int i = 42; i >= progress_bar; --i)//模拟倒计时
		std::cout << "\b \b";//实现遮盖。
    //\b是退格符，这里第一个\b先退一个，再用中间的空格覆盖原来位置上的符号，然后再退一格。这里好像只需要用一个\b就行了？
    --progress_bar;
	if (progress_bar == 0)//倒计时结束，大食物消失
    {
        SetCursorPosition(big_x, big_y);
        std::cout << "  ";
        big_flag = false;
        big_x = 0;
        big_y = 0;
    }
}

bool Food::GetBigFlag()//有没有大食物存在
{
    return big_flag;
}

int Food::GetProgressBar()//获取进度条的长度
{
    return progress_bar;
}
