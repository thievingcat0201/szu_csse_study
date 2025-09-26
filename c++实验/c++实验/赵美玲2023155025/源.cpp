#include <graphics.h>		// 引用 EasyX 图形库
#include <conio.h>
#include<time.h>
#include<math.h>
#define High 480  // 游戏画面尺寸
#define Width 640

/*实现通关游戏
第一关：随机移动的敌人
第二关：大小随机变化且随机移动的敌人
第三关：会发子弹且随机移动的敌人
第四关：大小随机变化且会发子弹且随机移动的敌人
*/

//实现以下类
class CCircle
{
protected:
	float x, y, vx, vy, radius;
public:
	CCircle()
	{
		vx = (rand() % 5 + 5);
		vy = (rand() % 5 + 5);
		radius = rand() % 10 + 10;
		x = (rand() % 400 + 40);
		y = (rand() % 350 + 50);
	}
	CCircle(float ox, float oy, float vx, float vy)
	{
		this->x = ox;
		this->y = oy;
		this->vy = vy;
		this->vx = vx;

	}
	float GetX() { return x; }
	float GetY() { return y; }
	float GetR() { return radius; }
	float GetCircumference() { return 2 * 3.14 * radius; }
	float GetVX() { return vx; }
	float GetVY() { return vy; }
	virtual void XY_Change()
	{
		x += vx;
		y += vy;
	}
	virtual void XY_Change(float a, float b)
	{
		x = a;
		y = b;
	}
	void VX_change()
	{
		vx = -vx;
	}
	void VY_change()
	{
		vy = -vy;
	}
	virtual void show_circle()
	{
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, y, radius);
	}
	virtual void hide_circle()
	{
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, radius);
	}
	void explosion_show_circle()
	{
		setcolor(YELLOW);
		setfillcolor(RED);
		fillcircle(x, y, radius);
	}
};
class CPlayer :public  CCircle
{
public:
	void XY_Change(float a, float b)
	{
		x = a;
		y = b;
	}
	void show_circle()
	{
		setcolor(YELLOW);
		setfillcolor(BLUE);
		fillcircle(x, y, radius);
	}
};
class CBullet :public CCircle//继承CCircle
{
public:
	void updateXY(float a, float b)
	{
		x += vx;
		y += vy;
		if (x + radius >= Width || x - radius <= 0)
		{
			x = a;
			y = b;
			vx = rand() % 21 - 10;
			vy = rand() % 21 - 10;
		}
		if (y + radius >= High || y - radius <= 0)
		{
			x = a;
			y = b;
			vx = rand() % 21 - 10;
			vy = rand() % 21 - 10;
		}
	}
	void show_circle()
	{
		setcolor(YELLOW);
		setfillcolor(YELLOW);
		fillcircle(x, y, radius);
	}
};

class CEnemy :public CCircle//继承CCircle
{
};
class CEnemywithBullet :virtual public CEnemy//继承CEnemy
{
protected:
	CBullet m;
public:
	CEnemywithBullet()
	{
		vx = (rand() % 5 + 5);
		vy = (rand() % 5 + 5);
		radius = rand() % 30 + 10;
		x = (rand() % 400 + 40);
		y = (rand() % 350 + 50);
		m = CBullet();
	}
	void XY_Change()
	{
		x += vx;
		y += vy;
		m.updateXY(x, y);
	}
	void show_circle()
	{
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, y, radius);
		setcolor(YELLOW);
		setfillcolor(YELLOW);
		m.show_circle();
	}
	void hide_circle()
	{
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, radius);
		setcolor(BLACK);
		setfillcolor(BLACK);
		m.hide_circle();
	}
};
class CEnemywithSize :virtual public CEnemy//继承CEnemy
{
public:
	void XY_Change()
	{
		x += vx;
		y += vy;
		radius = rand() % 30 + 10;
	}

};
class CEnemyBoss :public CEnemywithBullet, public CEnemywithSize//继承CEnemywithBullet和CEnemywithSize
{
public:
	void XY_Change()
	{
		x += vx;
		y += vy;
		radius = rand() % 30 + 10;
		m.updateXY(x, y);
	}
	void show_circle()
	{
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, y, radius);
		setcolor(YELLOW);
		setfillcolor(YELLOW);
		fillcircle(m.GetX(), m.GetY(), m.GetR());
	}
	void hide_circle()
	{
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, radius);
		fillcircle(m.GetX(), m.GetY(), m.GetR());
	}
};

int hit(CCircle a, CCircle b)
{
	if ((a.GetR() + b.GetR()) * (a.GetR() + b.GetR()) >= (a.GetX() - b.GetX()) * (a.GetX() - b.GetX()) + (a.GetY() - b.GetY()) * (a.GetY() - b.GetY()))
		return 1;
	else return 0;


}

void updateWithoutInput(CCircle& obj)
{
	obj.XY_Change();
	if (obj.GetX() + obj.GetR() >= 640 || obj.GetX() - obj.GetR() <= 0) obj.VX_change();
	if (obj.GetY() + obj.GetR() >= 480 || obj.GetY() - obj.GetR() <= 0) obj.VY_change();

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
			obj.XY_Change(m.x, m.y);
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
	CPlayer pobj;
	int round = 0, flag = 0;
	while (round < 4) {

		int i, j;
		CEnemy* cobjrandom = NULL;

		switch (round) {
			//case 0:   第一关：随机移动的敌人
			//case 1:   第二关：大小随机变化且随机移动的敌人
			//case 2:   第三关：会发子弹且随机移动的敌人
			//case 3:   第四关：大小随机变化且会发子弹且随机移动的敌人
		case 0:
			cobjrandom = new CEnemy;
			break;
		case 1:
			cobjrandom = new CEnemywithSize;
			break;
		case 2:
			cobjrandom = new CEnemywithBullet;
			break;
		case 3:
			cobjrandom = new CEnemyBoss;
			break;


		}

		if (cobjrandom != NULL) {
			clock_t start = clock(), end = clock();
			double period = (double)(end - start) / CLOCKS_PER_SEC;
			while (period <= 5) {
				//请在下方编写代码，调用pobj的方法，擦除圆（就是用黑色把圆再画一遍）
				pobj.hide_circle();

				//请在下方编写代码，调用Circle对象方法，擦除圆（就是用黑色把圆再画一遍）
				cobjrandom->hide_circle();

				// 请在更新球的坐标
				// 与用户输入无关的更新
				// 请在下方编写代码，调用update函数，更新每个对象的坐标	
				updateWithInput(pobj);
				updateWithoutInput(*cobjrandom);


				//判断是否发生碰撞
				int r = hit(pobj, *cobjrandom);

				//若未发生碰撞，请在下方编写代码，调用每个Circle对象的方法，重新绘制圆
				//请在下方编写代码，调用CPlayer方法，重新绘制圆
				if (r == 0)
				{
					pobj.show_circle();
					cobjrandom->show_circle();
				}
				else if (r == 1)
				{
					round = 5;
					pobj.explosion_show_circle();
					cobjrandom->explosion_show_circle();
					break;
				}

				FlushBatchDraw();
				Sleep(3);	// 延时
				end = clock();
				period = (double)(end - start) / CLOCKS_PER_SEC;
			}

			//发生碰撞，游戏结束
			if (round == 5)
			{
				settextstyle(30, 0, L"微软雅黑");
				outtextxy(Width * 0.4, High * 0.45, TEXT("GAME OVER"));
				break;
			}

			//进入到下一关
			else if (round < 3)
			{
				settextstyle(30, 0, L"微软雅黑");
				outtextxy(Width * 0.4, High * 0.45, TEXT("NEXT ROUND"));
				FlushBatchDraw();
				Sleep(1000);

			}

			//闯关成功
			else if (round == 3)
			{
				settextstyle(30, 0, L"微软雅黑");
				outtextxy(Width * 0.3, High * 0.45, TEXT("CONGRADULATION!"));
				break;
			}

			round++;
			cleardevice();
		}
	}
	gameover();  // 游戏结束、后续处理
	return 0;
}


