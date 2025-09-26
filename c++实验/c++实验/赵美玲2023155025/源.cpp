#include <graphics.h>		// ���� EasyX ͼ�ο�
#include <conio.h>
#include<time.h>
#include<math.h>
#define High 480  // ��Ϸ����ߴ�
#define Width 640

/*ʵ��ͨ����Ϸ
��һ�أ�����ƶ��ĵ���
�ڶ��أ���С����仯������ƶ��ĵ���
�����أ��ᷢ�ӵ�������ƶ��ĵ���
���Ĺأ���С����仯�һᷢ�ӵ�������ƶ��ĵ���
*/

//ʵ��������
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
class CBullet :public CCircle//�̳�CCircle
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

class CEnemy :public CCircle//�̳�CCircle
{
};
class CEnemywithBullet :virtual public CEnemy//�̳�CEnemy
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
class CEnemywithSize :virtual public CEnemy//�̳�CEnemy
{
public:
	void XY_Change()
	{
		x += vx;
		y += vy;
		radius = rand() % 30 + 10;
	}

};
class CEnemyBoss :public CEnemywithBullet, public CEnemywithSize//�̳�CEnemywithBullet��CEnemywithSize
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

	//�������ĸ���
}

void updateWithInput(CPlayer& obj)
{
	MOUSEMSG m;		// ���������Ϣ
	while (MouseHit())  //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			// ����λ�õ���������ڵ�λ��
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
	initgraph(Width, High);//// ��ʼ��640��480�Ļ���
	BeginBatchDraw();
}



int main()
{
	startup();
	srand((unsigned int)time(0));

	//�����·���д���룬����CPlayer�����
	CPlayer pobj;
	int round = 0, flag = 0;
	while (round < 4) {

		int i, j;
		CEnemy* cobjrandom = NULL;

		switch (round) {
			//case 0:   ��һ�أ�����ƶ��ĵ���
			//case 1:   �ڶ��أ���С����仯������ƶ��ĵ���
			//case 2:   �����أ��ᷢ�ӵ�������ƶ��ĵ���
			//case 3:   ���Ĺأ���С����仯�һᷢ�ӵ�������ƶ��ĵ���
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
				//�����·���д���룬����pobj�ķ���������Բ�������ú�ɫ��Բ�ٻ�һ�飩
				pobj.hide_circle();

				//�����·���д���룬����Circle���󷽷�������Բ�������ú�ɫ��Բ�ٻ�һ�飩
				cobjrandom->hide_circle();

				// ���ڸ����������
				// ���û������޹صĸ���
				// �����·���д���룬����update����������ÿ�����������	
				updateWithInput(pobj);
				updateWithoutInput(*cobjrandom);


				//�ж��Ƿ�����ײ
				int r = hit(pobj, *cobjrandom);

				//��δ������ײ�������·���д���룬����ÿ��Circle����ķ��������»���Բ
				//�����·���д���룬����CPlayer���������»���Բ
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
				Sleep(3);	// ��ʱ
				end = clock();
				period = (double)(end - start) / CLOCKS_PER_SEC;
			}

			//������ײ����Ϸ����
			if (round == 5)
			{
				settextstyle(30, 0, L"΢���ź�");
				outtextxy(Width * 0.4, High * 0.45, TEXT("GAME OVER"));
				break;
			}

			//���뵽��һ��
			else if (round < 3)
			{
				settextstyle(30, 0, L"΢���ź�");
				outtextxy(Width * 0.4, High * 0.45, TEXT("NEXT ROUND"));
				FlushBatchDraw();
				Sleep(1000);

			}

			//���سɹ�
			else if (round == 3)
			{
				settextstyle(30, 0, L"΢���ź�");
				outtextxy(Width * 0.3, High * 0.45, TEXT("CONGRADULATION!"));
				break;
			}

			round++;
			cleardevice();
		}
	}
	gameover();  // ��Ϸ��������������
	return 0;
}


