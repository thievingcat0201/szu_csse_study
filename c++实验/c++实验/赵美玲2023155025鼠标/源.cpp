#include <graphics.h>
#include <conio.h>
#include <time.h>
#include<cmath>

#define High 480  // ��Ϸ����ߴ�
#define Width 640

class CCircle {



public:
    int x, y;   // Բ������
    int radius; // �뾶
    int speedX; // ˮƽ�ٶ�
    int speedY; // ��ֱ�ٶ�
    // ���캯�����������Բ
    CCircle() {
        x = rand() % Width;
        y = rand() % High;
        radius = rand() % 20 + 10; // �뾶��Χ��10~30
        speedX = rand() % 5 + 1;   // ˮƽ�ٶȷ�Χ��1~5
        speedY = rand() % 5 + 1;   // ��ֱ�ٶȷ�Χ��1~5
    }

    // ����Բ������
    void updatePosition() {
        x += speedX;
        y += speedY;
        if (x < 0 || x > Width) {
            speedX = -speedX; // ײǽ����
        }
        if (y < 0 || y > High) {
            speedY = -speedY; // ײǽ����
        }
    }

    // ����Բ
    void draw() {
        setlinecolor(YELLOW);
        setfillcolor(GREEN);
        fillcircle(x, y, radius);
    }


};

class CPlayer : public CCircle {
public:
    // �������λ��
    void updatePosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    // �������
    void draw() {
        setlinecolor(YELLOW);
        setfillcolor(BLUE);
        fillcircle(x, y, radius);
    }
};

// ��ײ���
bool hit(const CPlayer& player, const CCircle& circle) {
    int dx = player.x - circle.x;
    int dy = player.y - circle.y;
    int distance = sqrt(dx * dx + dy * dy);
    return distance <= (player.radius + circle.radius);
}

void updateWithInput(CPlayer& player) {
    MOUSEMSG m;
    while (MouseHit()) {
        m = GetMouseMsg();
        if (m.uMsg == WM_MOUSEMOVE) {
            player.updatePosition(m.x, m.y);
        }
    }
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

    CPlayer player;
    const int circleCount = 5;
    CCircle circles[circleCount];

    while (1) {
        cleardevice();

        updateWithInput(player);

        for (int i = 0; i < circleCount; ++i) {
            circles[i].updatePosition();
            circles[i].draw();
            if (hit(player, circles[i])) {
                circles[i].draw(); // ������ײ��Բ
                settextstyle(30, 0, L"΢���ź�");
                outtextxy(Width * 0.4, High * 0.45, TEXT("GAME OVER"));
                gameover();
                return 0;
            }
        }

        player.draw();

        FlushBatchDraw();
        Sleep(10);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}