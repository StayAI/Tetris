#ifndef TETRIS_H
#define TETRIS_H

#include <QWidget>

extern int gra[19][4][4];
extern int maps[20][12];
extern int mapTemp[20][12];

class Tetris : public QWidget
{
    Q_OBJECT
public:
    explicit Tetris(QWidget *parent = 0);

    int random(int temp);
    void Change_Array(int temp_maps[4][4]);
    int Judge_Hit_Wall(int tempArray[][4]);
    void Deal_Key(void);
    void Tetris_Move();
    void Line_Full(void);
    bool Tetris::GameOver(void);


    int getKey()//获取按键值
    {
        return key;
    }

    void setKey(int key)//设置按键值
    {
        this->key = key;
    }

    int getSize()//获取方块像素值大小
    {
        return size;
    }
    int getScore()//获取分数
    {
        return score;
    }
    int getIndexNext()//获取下一个方块的索引值
    {
        return indexNext;
    }



signals:

public slots:

private:

    int widthOfLocation;    //通过这两个数来定位array在maps中的位置
    int heightOfLocation;


    int size;//方块像素值大小
    int index;//当前正在移动的方块的索引值
    int indexNext;//下一个方块的索引值
    int array[4][4];//存储正在下降的方块数据
    int key;//按键值
    int score;//分数
};

#endif // TETRIS_H
