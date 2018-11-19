#include "tetris.h"
#include <QDebug>
#include <QTime>
#include "widget.h"

Tetris::Tetris(QWidget *parent) : QWidget(parent)
{
    heightOfLocation = 0;
    widthOfLocation = 4;

    size = 40;
    key = 0;
    score = 0;
    index = random(19);
    indexNext = random(19);

    Change_Array( gra[index] );
}

int mapTemp[20][12];

int maps[20][12] =
{
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int gra[19][4][4] =
{
    {0, 1, 0, 0,
     0, 1, 0, 0,
     0, 1, 0, 0,
     0, 1, 0, 0},

    {0, 0, 0, 0,
     1, 1, 1, 1,
     0, 0, 0, 0,
     0, 0, 0, 0},

    {0, 1, 0, 0,
     0, 1, 1, 0,
     0, 0, 1, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     0, 1, 1, 0,
     1, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 1, 0,
     0, 1, 1, 0,
     0, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     0, 1, 1, 0,
     0, 0, 1, 1,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     0, 1, 1, 0,
     0, 1, 1, 0,
     0, 0, 0, 0},

    {0, 1, 0, 0,
     1, 1, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0},

    {0, 1, 0, 0,
     0, 1, 1, 0,
     0, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     1, 1, 1, 0,
     0, 1, 0, 0,
     0, 0, 0, 0},

    {0, 1, 0, 0,
     1, 1, 0, 0,
     0, 1, 0, 0,
     0, 0, 0, 0},

    {1, 0, 0, 0,
     1, 0, 0, 0,
     1, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     1, 1, 1, 0,
     1, 0, 0, 0,
     0, 0, 0, 0},

    {1, 1, 0, 0,
     0, 1, 0, 0,
     0, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     0, 0, 1, 0,
     1, 1, 1, 0,
     0, 0, 0, 0},

    {0, 1, 0, 0,
     0, 1, 0, 0,
     1, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     1, 0, 0, 0,
     1, 1, 1, 0,
     0, 0, 0, 0},

    {0, 1, 1, 0,
     0, 1, 0, 0,
     0, 1, 0, 0,
     0, 0, 0, 0},

    {0, 0, 0, 0,
     1, 1, 1, 0,
     0, 0, 1, 0,
     0, 0, 0, 0}
};

//生成随机数
int Tetris::random(int temp)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return qrand() % temp;
}


void Tetris::Change_Array(int temp_maps[4][4])//复制数组
{
    if ( Judge_Hit_Wall(temp_maps) ) //变换之后判断是否撞墙，如果撞墙就不变换
        return;

    for (int i=0; i<4; i++)//把按下按键之后变换的方块的数组坐标赋值到正在下降的数组坐标中
        for (int j=0; j<4; j++)
            array[i][j] = temp_maps[i][j];

    return ;
}

int Tetris::Judge_Hit_Wall(int tempArray[][4])//判断是否撞到墙
{
    for (int i=widthOfLocation; i<4+widthOfLocation; i++)
    {
        for (int j=heightOfLocation; j<4+heightOfLocation; j++)
        {
            if (tempArray[j-heightOfLocation][i-widthOfLocation] + maps[j][i] == 2)//如果现在移动的俄罗斯方块和maps数组重元素相加为2，则表示重合，那么返回1
            {
                return 1;
            }
        }
    }

    return 0;
}

void Tetris::Deal_Key(void)//处理按键函数
{
    if (key == 1)
    {
        switch ( index )
        {
            case 0:
                Change_Array( gra[++index] );//先将俄罗斯方块的索引值改变，然后通过索引值改变方块的形状
                break;
            case 1:
                Change_Array( gra[--index] );
                break;
            case 2:
                Change_Array( gra[++index] );
                break;
            case 3:
                Change_Array( gra[--index] );
                break;
            case 4:
                Change_Array( gra[++index] );
                break;
            case 5:
                Change_Array( gra[--index] );
                break;
            case 6:
                break;

            case 7:
                Change_Array( gra[++index] );
                break;
            case 8:
                Change_Array( gra[++index] );
                break;
            case 9:
                Change_Array( gra[++index] );
                break;
            case 10:
                index -= 3;
                Change_Array( gra[index] );
                break;

            case 11:
                Change_Array( gra[++index] );
                break;
            case 12:
                Change_Array( gra[++index] );
                break;
            case 13:
                Change_Array( gra[++index] );
                break;
            case 14:
                index -= 3;
                Change_Array( gra[index] );
                break;

            case 15:
                Change_Array( gra[++index] );
                break;
            case 16:
                Change_Array( gra[++index] );
                break;
            case 17:
                Change_Array( gra[++index] );
                break;
            case 18:
                index -= 3;
                Change_Array( gra[index] );
                break;
            default:
                break;
        }
    }
    if (key == 2)//延时变短，加速下降
    {

    }
    if (key == 3)//向左移动
    {
        widthOfLocation--;
        if ( Judge_Hit_Wall(array) )//如果有重合，就不移动
        {
            widthOfLocation++;
        }
    }
    if (key == 4)//向右移动
    {
        widthOfLocation++;
        if ( Judge_Hit_Wall(array) )//如果有重合，就不移动
        {
            widthOfLocation--;
        }
    }
}

void Tetris::Tetris_Move()
{
    heightOfLocation++;//方块下降一格

    for (int i=widthOfLocation; i<4+widthOfLocation; i++)
    {
        for (int j=heightOfLocation; j<4+heightOfLocation; j++)
        {
            if (array[j-heightOfLocation][i-widthOfLocation] + maps[j][i] == 2)//下降过程中，循环比对16个方块，如果有等于2的，就表示已经下降到底部
            {
                heightOfLocation--;//heightOfLocation-- 把降下来的一个在升回去

                for (int i=widthOfLocation; i<4+widthOfLocation; i++)//for循环，将现在的方块坐标复制到maps数组中
                {
                    for (int j=heightOfLocation; j<4+heightOfLocation; j++)
                    {
                        if (array[j-heightOfLocation][i-widthOfLocation] == 1)
                        {
                            maps[j][i] = 1;
                        }
                    }
                }

                for (int i=0; i<20; i++)
                {
                    for (int j=0; j<12; j++)
                    {
                        mapTemp[i][j] = maps[i][j];
                    }
                }

                heightOfLocation = 0;//一系列初始化
                widthOfLocation = 4;
                index = indexNext;//随机生成俄罗斯方块；
                indexNext = random(19);

                key = 0;//方块下降到底部之后，按键值初始化为零
                Change_Array( gra[index] );//通过索引值将数组赋值到下降的数组中
                qDebug() << "index = " << index;

                return ;//下降到底部，终止函数
            }

            if (array[j-heightOfLocation][i-widthOfLocation] == 1)//显示正在下落的方块
            {
                mapTemp[j][i] = 1;
            }
        }
    }
}

bool Tetris::GameOver(void)
{
    for (int n=1; n<=10; n++)
    {
        if (maps[2][n] == 1)
        {
            qDebug() << "Game Over";
            return 1;
        }
    }

    return 0;
}

void Tetris::Line_Full(void)
{
    static int Line = 0;
    for (int j=18; j>0; j--)//十四行
    {
        int sum = 0;
        for (int i=1; i<=10; i++)//判断每一行是否都为1
        {
            sum += maps[j][i];//10个数组元素的和
        }

        if (sum == 10)//
        {
            Line++;
            int k = j;
            for (; k>0; k--)//从满的那一行开始通过循环将以上的方格数据全部复制下来
            {
                for (int i=1; i<=10; i++)
                {
                    maps[k][i] = maps[k-1][i];
                }
            }

            if (k == 0)//最上面一行全部赋值为零
            {
                for (int i=1; i<=10; i++)
                {
                    maps[k][i] = 0;
                }
            }

            j++;
        }

    }

    switch(Line)
    {
        case 1:
            score += 10;
            break;
        case 2:
            score += 30;
            break;
        case 3:
            score += 50;
            break;
        case 4:
            score += 100;
            break;
        default:
            break;
    }
    Line = 0;

    return ;//函数终止
}
