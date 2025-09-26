#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>		// ���� EasyX ͼ�ο�
#include <conio.h>
#include<time.h>
#include<math.h>
#include <random>
#define High 480  // ��Ϸ����ߴ�
#define Width 640
using namespace std;
#include<iostream>

/*ʵ��ͨ����Ϸ
��һ�أ�����ƶ��ĵ���
�ڶ��أ���С����仯������ƶ��ĵ���
�����أ��ᷢ�ӵ�������ƶ��ĵ���
���Ĺأ���С����仯�һᷢ�ӵ�������ƶ��ĵ���
*/

//ʵ��������
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

};//�̳�CCircle

class CEnemy :virtual public CCircle
{
public:
	CEnemy() :CCircle() {}
	friend int hit(CCircle& a, CPlayer& b);
	virtual ~CEnemy() {}
};//�̳�CCircle

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

};//�̳�CEnemy

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

};//�̳�CEnemy

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
};//�̳�CEnemywithBullet��CEnemywithSize

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
	initgraph(Width, High);//// ��ʼ��640��480�Ļ���
	BeginBatchDraw();
}



int main()
{
	startup();
	srand((unsigned int)time(0));

	//�����·���д���룬����CPlayer�����
	CPlayer cobj;

	int round = 0, flag = 0, flag2 = 0, random_number = 0;
	while (round < 4) {

		int i, j;
		CEnemy* obj = NULL;

		switch (round) {
			//case 0:   ��һ�أ�����ƶ��ĵ���
		case 0:
			obj = new CEnemy();
			break;
			//case 1:   �ڶ��أ���С����仯������ƶ��ĵ���
		case 1:
			obj = new CEnemywithSize();
			break;
			//case 2:   �����أ��ᷢ�ӵ�������ƶ��ĵ���
		case 2:
			obj = new CEnemywithBullet();
			break;
			//case 3:   ���Ĺأ���С����仯�һᷢ�ӵ�������ƶ��ĵ���
		case 3:
			obj = new CEnemyBoss();
			break;
		}
		helper* helperobj = new helper();
		if (obj != NULL) {
			clock_t start = clock(), end = clock();
			double period = (double)(end - start) / CLOCKS_PER_SEC;
			while (period <= 5) {
				//�����·���д���룬����pobj�ķ���������Բ�������ú�ɫ��Բ�ٻ�һ�飩
				cobj.cdelete();


				//�����·���д���룬����Circle���󷽷�������Բ�������ú�ɫ��Բ�ٻ�һ�飩
				obj->cdelete();
				helperobj->cdelete();


				// ���ڸ����������
				// ���û������޹صĸ���
				// �����·���д���룬����update����������ÿ�����������	
				updateWithInput(cobj);
				updateWithoutInput(*obj);
				updateWithoutInput(*helperobj);

				//�ж��Ƿ�����ײ
				flag = hit(*obj, cobj);
				if ((round == 2 || round == 3) && flag == 1)flag = obj->hit2(cobj);

				if (flag == 0) {
					cobj.bombshow();
					setcolor(YELLOW);
					setfillcolor(WHITE);
					settextstyle(30, 0, L"΢���ź�");
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
					// ����һ���ֲ���Χ��1��4֮��ľ��ȷֲ�
					uniform_int_distribution<int> distribution(1, 4);
					// ���������
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





				//��δ������ײ�������·���д���룬����ÿ��Circle����ķ��������»���Բ
				obj->show();
				helperobj->show();

				//�����·���д���룬����CPlayer���������»���Բ
				cobj.show();



				FlushBatchDraw();
				Sleep(3);	// ��ʱ
				end = clock();
				period = (double)(end - start) / CLOCKS_PER_SEC;
			}

			if (flag == 0) {
				break;
			}
			//������ײ����Ϸ����
			/*settextstyle(30, 0, L"΢���ź�");
			outtextxy(Width*0.4, High*0.45, TEXT("GAME OVER"));*/
			else if (flag == 1 && round < 3) {
				setcolor(YELLOW);
				setfillcolor(WHITE);
				settextstyle(30, 0, L"΢���ź�");
				outtextxy(Width * 0.4, High * 0.45, TEXT("NEXT ROUND"));
				FlushBatchDraw();
				Sleep(1000);
			}
			//���뵽��һ��
			/*settextstyle(30, 0, L"΢���ź�");
			outtextxy(Width*0.4, High*0.45, TEXT("NEXT ROUND"));
			FlushBatchDraw();
			Sleep(1000);
			*/
			else if (round == 3) {
				setcolor(YELLOW);
				setfillcolor(WHITE);
				settextstyle(30, 0, L"΢���ź�");
				outtextxy(Width * 0.3, High * 0.45, TEXT("CONGRADULATION!"));
				FlushBatchDraw();
				Sleep(1000);
				break;
			}
			//���سɹ�
			/*	settextstyle(30, 0, L"΢���ź�");
			outtextxy(Width*0.3, High*0.45, TEXT("CONGRADULATION!"));*/

			round++;
			cleardevice();
		}
	}
	gameover();  // ��Ϸ��������������
	return 0;
}
