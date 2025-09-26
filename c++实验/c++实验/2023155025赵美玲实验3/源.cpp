#include <graphics.h>    // 引用 EasyX 图形库
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

#define High 480  // 游戏画面尺寸
#define Width 640

class CCircle {
private:
    int x;          
    int y;         
    int radius;     
    int speedX;    
    int speedY;     

public:
    CCircle(int startX, int startY, int startRadius, int startSpeedX, int startSpeedY) {
        x = startX;
        y = startY;
        radius = startRadius;
        speedX = startSpeedX;
        speedY = startSpeedY;
    }

    CCircle() {
      radius = rand() % 30 + 10; 
        x = rand() % (Width - 2 * radius) + radius;
        y = rand() % (High - 2 * radius) + radius;
       

        speedX = rand() % 5 + 1;   
        speedY = rand() % 5 + 1;   
    }


    void erase() {
        setfillcolor(BLACK);    
        solidcircle(x, y, radius); 
    }


    void draw() {
        setfillcolor(GREEN);   
        solidcircle(x, y, radius);  
    }

 
    void update() {
     
        x += speedX;
        y += speedY;
      
        if (x <= radius || x >= Width - radius) {
            speedX = -speedX;
        }
        if (y <= radius || y >= High - radius) {
            speedY = -speedY;
        }
    }
};

void updateWithoutInput(CCircle& obj)
{
    obj.update();
}

void gameover()
{
    EndBatchDraw();
    _getch();
    closegraph();
}

void startup()
{
    initgraph(Width, High);// 初始化640×480的画布
    BeginBatchDraw();
}

int main()
{
    startup();
    srand((unsigned int)time(0));

   
    CCircle cobj(Width / 2, High / 2, 20, 3, 2);

   
    CCircle cobjrandom;

    while (1)
    {

        cobj.erase();
        cobjrandom.erase();

   
        updateWithoutInput(cobj);
        updateWithoutInput(cobjrandom);

   
        cobj.draw();
        cobjrandom.draw();

        FlushBatchDraw();
        Sleep(3);   // 延时
    }


    EndBatchDraw();
    closegraph();
    return 0;
}
