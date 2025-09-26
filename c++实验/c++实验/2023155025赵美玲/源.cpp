#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>		// 引用 EasyX 图形库
#include <conio.h>
#include<time.h>
#include<math.h>
#include <random>
#define High 480  // 游戏画面尺寸
#define Width 640
using namespace std;
#include<iostream>

/*实现通关游戏
第一关：随机移动的敌人
第二关：大小随机变化且随机移动的敌人
第三关：会发子弹且随机移动的敌人
第四关：大小随机变化且会发子弹且随机移动的敌人
*/

//实现以下类
class CCircle;
class CEnemywithBullet;
class helper;
int n = 0;

class CPlayer
{
	int x, y, r;
public:
	friend void operator+(CPlayer& obj1, helper& obj);
	friend void operator-(CPlayer& obj1, helper& obj);
	friend int hit(CCircle& a, CPlayer& b);
	friend CEnemywithBullet;
	CPlayer() {
		x = 550, y = 200, r = 20;
	}
	void update(int x_, int y_) {
		x = x_, y = y_;
	}
	void show() {
		setcolor(WHITE);
		setfillcolor(BLUE);
		fillcircle(x, y, r);
	}
	void cdelete() {
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, r);
	}
	void bombshow() {
		setcolor(YELLOW);
		setfillcolor(RED);
		fillcircle(x, y, r);
	}



};

class CCircle
{
protected:
	int x, y, r, vx, vy;
public:
	friend int hit(CCircle& a, CPlayer& b);
	CCircle() {
		x = rand() % 350 + 70;
		y = rand() % 350 + 70;
		r = 50;
		vx = rand() % 8 + 3;
		vy = rand() % 8 + 3;
	}
	virtual void update() {
		if (x + r >= 640 || x - r <= 0)vx = -vx;
		if (y + r >= 480 || y - r <= 0)vy = -vy;
		x += vx; y += vy;
	}
	virtual void cdelete() {
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, r);
	}
	virtual void show() {
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, y, r);
	}

	void operator++() {
		vx *= 2;
		vy *= 2;
	}
	void operator--() {
		vx /= 2;
		vy /= 2;
	}

	virtual int hit2(CPlayer& a) {
		return 1;
	}
};

class CBullet :virtual public CCircle
{
public:
	friend int hit(CCircle& a, CPlayer& b);
	virtual ~CBullet() {}
	friend CEnemywithBullet;
	CBullet() :CCircle() {
		r = 20;
	}
	void update(int a, int b) {
		x += vx; y += vy;
		if (x >= 640 || x <= 0 || y >= 480 || y <= 0) {
			vx = rand() % 5 + 3;
			vy = rand() % 5 + 3;
			x = a, y = b;
		}
	}
	void show() {
		setcolor(WHITE);
		setfillcolor(YELLOW);
		fillcircle(x, y, r);
	}

};//继承CCircle

class CEnemy :virtual public CCircle
{
public:
	CEnemy() :CCircle() {}
	friend int hit(CCircle& a, CPlayer& b);
	virtual ~CEnemy() {}
};//继承CCircle

class CEnemywithBullet :virtual public CEnemy
{
protected:
	CBullet p;
public:
	friend int hit(CCircle& a, CPlayer& b);
	virtual ~CEnemywithBullet() {}
	CEnemywithBullet() :CEnemy() {
		p = CBullet();
	}
	void update() {
		if (x + r >= 640 || x - r <= 0)vx = -vx;
		if (y + r >= 480 || y - r <= 0)vy = -vy;
		x += vx; y += vy;
		p.update(x, y);
	}
	void show() {
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, y, r);
		p.show();
	}
	void cdelete() {
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, r);
		p.cdelete();
	}
	int hit2(CPlayer& a) {
		int distance1 = (a.x - p.x) * (a.x - p.x) + (a.y - p.y) * (a.y - p.y);
		int distance2 = (a.r + p.r) * (a.r + p.r);
		if (distance1 > distance2)return 1;
		return 0;
	}

};//继承CEnemy

class CEnemywithSize :virtual public CEnemy
{
public:
	friend int hit(CCircle& a, CPlayer& b);
	virtual ~CEnemywithSize() {}
	CEnemywithSize() :CEnemy() {}
	void update() {
		if (x + r >= 640 || x - r <= 0)vx = -vx;
		if (y + r >= 480 || y - r <= 0)vy = -vy;
		x += vx; y += vy;
		n++;
		if (n == 30) {
			r = rand() % 70 + 10;
			n = 0;
		}

	}

};//继承CEnemy

class CEnemyBoss :public CEnemywithBullet, public CEnemywithSize
{
public:
	friend int hit(CCircle& a, CPlayer& b);
	CEnemyBoss() :CEnemywithBullet(), CEnemywithSize() {}
	void update() {
		if (x + r >= 640 || x - r <= 0)vx = -vx;
		if (y + r >= 480 || y - r <= 0)vy = -vy;
		x += vx; y += vy;
		p.update(x, y);
		n++;
		if (n == 30) {
			r = rand() % 100 + 1;
			n = 0;
		}
	}
	void show() {
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, y, r);
		p.show();
	}
	void cdelete() {
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, r);
		p.cdelete();
	}

	virtual ~CEnemyBoss() {}
};//继承CEnemywithBullet和CEnemywithSize

class helper :virtual public CCircle {
public:
	friend int hit(CCircle& a, CPlayer& b);
	friend CPlayer;
	friend void operator+(CPlayer& obj1, helper& obj);
	friend void operator-(CPlayer& obj1, helper& obj);
	helper() :CCircle() {
		r = rand() % 20;
	}

	virtual void show() {
		setcolor(YELLOW);
		setfillcolor(WHITE);
		fillcircle(x, y, r);
	}
	~helper() {}

	void set() {
		x = rand() % 350 + 70;
		y = rand() % 350 + 70;
		r = rand() % 50 + 20;
		vx = rand() % 8 + 3;
		vy = rand() % 8 + 3;
	}

};
void operator +(CPlayer& obj1, helper& obj)
{
	obj1.r = obj1.r + obj.r;
	if (obj1.r > 100) obj1.r = 100;
}
void operator -(CPlayer& obj1, helper& obj)
{
	obj1.r = obj1.r - obj.r;
	if (obj1.r < 10) obj1.r = 10;
}



int hit(CCircle& a, CPlayer& b)
{
	int distance1 = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	int distance2 = (a.r + b.r) * (a.r + b.r);
	if (distance1 > distance2)return 1;
	return 0;
}

void updateWithoutInput(CCircle& obj)
{
	obj.update();
	//随机对象的更新
}

void updateWithInput(CPlayer& obj)
{
	MOUSEMSG m;		// 定义鼠标消息
	while (MouseHit())  //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			// 更新位置等于鼠标所在的位置
			obj.update(m.x, m.y);
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}



void startup()
{
	initgraph(Width, High);//// 初始化640×480的画布
	BeginBatchDraw();
}



int main()
{
	startup();
	srand((unsigned int)time(0));

	//请在下方编写代码，生成CPlayer类对象
	CPlayer cobj;

	int round = 0, flag = 0, flag2 = 0, random_number = 0;
	while (round < 4) {

		int i, j;
		CEnemy* obj = NULL;

		switch (round) {
			//case 0:   第一关：随机移动的敌人
		case 0:
			obj = new CEnemy();
			break;
			//case 1:   第二关：大小随机变化且随机移动的敌人
		case 1:
			obj = new CEnemywithSize();
			break;
			//case 2:   第三关：会发子弹且随机移动的敌人
		case 2:
			obj = new CEnemywithBullet();
			break;
			//case 3:   第四关：大小随机变化且会发子弹且随机移动的敌人
		case 3:
			obj = new CEnemyBoss();
			break;
		}
		helper* helperobj = new helper();
		if (obj != NULL) {
			clock_t start = clock(), end = clock();
			double period = (double)(end - start) / CLOCKS_PER_SEC;
			while (period <= 5) {
				//请在下方编写代码，调用pobj的方法，擦除圆（就是用黑色把圆再画一遍）
				cobj.cdelete();


				//请在下方编写代码，调用Circle对象方法，擦除圆（就是用黑色把圆再画一遍）
				obj->cdelete();
				helperobj->cdelete();


				// 请在更新球的坐标
				// 与用户输入无关的更新
				// 请在下方编写代码，调用update函数，更新每个对象的坐标	
				updateWithInput(cobj);
				updateWithoutInput(*obj);
				updateWithoutInput(*helperobj);

				//判断是否发生碰撞
				flag = hit(*obj, cobj);
				if ((round == 2 || round == 3) && flag == 1)flag = obj->hit2(cobj);

				if (flag == 0) {
					cobj.bombshow();
					setcolor(YELLOW);
					setfillcolor(WHITE);
					settextstyle(30, 0, L"微软雅黑");
					outtextxy(Width * 0.4, High * 0.45, TEXT("GAME OVER"));
					delete obj;
					FlushBatchDraw();
					Sleep(1000);
					break;
				}
				flag2 = hit(*helperobj, cobj);
				if (flag2 == 0) {
					helperobj->set();
					mt19937 generator(random_device{}());
					// 创建一个分布范围在1到4之间的均匀分布
					uniform_int_distribution<int> distribution(1, 4);
					// 生成随机数
					random_number = distribution(generator);

					switch (random_number) {
					case 1:
						++(*obj);
						break;
					case 2:
						--(*obj);
						break;
					case 3:
						cobj + *helperobj;
						break;
					case 4:
						cobj - *helperobj;
						break;
					}
				}





				//若未发生碰撞，请在下方编写代码，调用每个Circle对象的方法，重新绘制圆
				obj->show();
				helperobj->show();

				//请在下方编写代码，调用CPlayer方法，重新绘制圆
				cobj.show();



				FlushBatchDraw();
				Sleep(3);	// 延时
				end = clock();
				period = (double)(end - start) / CLOCKS_PER_SEC;
			}

			if (flag == 0) {
				break;
			}
			//发生碰撞，游戏结束
			/*settextstyle(30, 0, L"微软雅黑");
			outtextxy(Width*0.4, High*0.45, TEXT("GAME OVER"));*/
			else if (flag == 1 && round < 3) {
				setcolor(YELLOW);
				setfillcolor(WHITE);
				settextstyle(30, 0, L"微软雅黑");
				outtextxy(Width * 0.4, High * 0.45, TEXT("NEXT ROUND"));
				FlushBatchDraw();
				Sleep(1000);
			}
			//进入到下一关
			/*settextstyle(30, 0, L"微软雅黑");
			outtextxy(Width*0.4, High*0.45, TEXT("NEXT ROUND"));
			FlushBatchDraw();
			Sleep(1000);
			*/
			else if (round == 3) {
				setcolor(YELLOW);
				setfillcolor(WHITE);
				settextstyle(30, 0, L"微软雅黑");
				outtextxy(Width * 0.3, High * 0.45, TEXT("CONGRADULATION!"));
				FlushBatchDraw();
				Sleep(1000);
				break;
			}
			//闯关成功
			/*	settextstyle(30, 0, L"微软雅黑");
			outtextxy(Width*0.3, High*0.45, TEXT("CONGRADULATION!"));*/

			round++;
			cleardevice();
		}
	}
	gameover();  // 游戏结束、后续处理
	return 0;
}
