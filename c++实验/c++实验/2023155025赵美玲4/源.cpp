#include <graphics.h>       // ���� EasyX ͼ�ο�
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

#define High 480  // ��Ϸ����ߴ�
#define Width 640

class CCircle {
private:
    int x;  // Բ�� x ����
    int y;  // Բ�� y ����
    int speedX;  // x �����ٶ�
    int speedY;  // y �����ٶ�

public:
    static int radius;  // ������̬���ݳ�Ա radius

    CCircle() {
        x = rand() % (Width - 2 * radius) + radius;  
        y = rand() % (High - 2 * radius) + radius;
        speedX = rand() % 6 - 3; 
        speedY = rand() % 6 - 3;
    }

    void draw() {
        setfillcolor(GREEN);  
        setlinecolor(GREEN);
        fillcircle(x, y, radius);
    }

    void erase() {
        setfillcolor(BLACK);  
        setlinecolor(BLACK);
        fillcircle(x, y, radius);
    }

   
        void update() {
            erase();  

            x += speedX;
            y += speedY;


            if (x < radius || x > Width - radius) {
                speedX = -speedX;
            }
            if (y < radius || y > High - radius) {
                speedY = -speedY;
            }
            erase();
            draw();  
        }

    

    static void changeRadius() {
        
        radius = (radius == 20) ? 5 : 20; 
    }
    static void changeRadius(CCircle(&circles)[5]) {  
        for (int i = 0; i < 5; ++i) {
            circles[i].erase(); 
        }

        radius = (radius == 20) ? 5 : 20; 

        for (int i = 0; i < 5; ++i) {
            circles[i].draw(); 
        }
    }
};

int CCircle::radius = 20;  

void updateWithoutInput(CCircle& obj) {
    obj.update(); 
}

void gameover() {
    EndBatchDraw();
    _getch();
    closegraph();
}

void startup() {
    initgraph(Width, High);  
    BeginBatchDraw();
}

int main() {
    startup();
    srand((unsigned int)time(0));
    MOUSEMSG m;  

    CCircle circles[5];  

    while (1) {
        for (int i = 0; i < 5; ++i) {
            circles[i].erase();
        }

        for (int i = 0; i < 5; ++i) {
            updateWithoutInput(circles[i]);  
        }

        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                CCircle::changeRadius(circles); 
            }
        }

        for (int i = 0; i < 5; ++i) {
            circles[i].draw();  
        }

        FlushBatchDraw();
        Sleep(3);  // ��ʱ
    }

    gameover();  // ��Ϸ��������������
    return 0;
}
