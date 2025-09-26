#include <graphics.h>
#include <conio.h>
#include <time.h>
#include<cmath>

#define High 480  // 游戏画面尺寸
#define Width 640

class CCircle {



public:
    int x, y;   // 圆心坐标
    int radius; // 半径
    int speedX; // 水平速度
    int speedY; // 垂直速度
    // 构造函数，生成随机圆
    CCircle() {
        x = rand() % Width;
        y = rand() % High;
        radius = rand() % 20 + 10; // 半径范围：10~30
        speedX = rand() % 5 + 1;   // 水平速度范围：1~5
        speedY = rand() % 5 + 1;   // 垂直速度范围：1~5
    }

    // 更新圆心坐标
    void updatePosition() {
        x += speedX;
        y += speedY;
        if (x < 0 || x > Width) {
            speedX = -speedX; // 撞墙反弹
        }
        if (y < 0 || y > High) {
            speedY = -speedY; // 撞墙反弹
        }
    }

    // 绘制圆
    void draw() {
        setlinecolor(YELLOW);
        setfillcolor(GREEN);
        fillcircle(x, y, radius);
    }


};

class CPlayer : public CCircle {
public:
    // 更新玩家位置
    void updatePosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    // 绘制玩家
    void draw() {
        setlinecolor(YELLOW);
        setfillcolor(BLUE);
        fillcircle(x, y, radius);
    }
};

// 碰撞检测
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
                circles[i].draw(); // 绘制碰撞的圆
                settextstyle(30, 0, L"微软雅黑");
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