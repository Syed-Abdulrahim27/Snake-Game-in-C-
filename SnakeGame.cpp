#include <iostream>
#include<Windows.h>
#include<conio.h>
enum Direction { UP, DOWN, LEFT, RIGHT };
using namespace std;
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct Position
{
	int y;
	int x;
};
struct Snake
{
	Position* Ps;
	int size;
	char sym;
	int score;
	string Snake1name;
	Direction Dir;
	int Rightkey, Leftkey, Upkey, Downkey;
};
struct Food
{
	Position fP;
	bool isAlive;
	int score;
	char sym;
};
void square(int height,int width)
{
	SetClr(4);
	for (int i = 0; i <=width; i++)
	{
		gotoRowCol(0, i);
		cout << char(-37);
	}
	for (int i = 0; i <=height; i++)
	{
		gotoRowCol(i, 0);
		cout << char(-37);
	}
	for (int i = 0; i <=height; i++)
	{
		gotoRowCol(i, width);
		cout << char(-37);
	}
	for (int i = 0; i <=width; i++)
	{
		gotoRowCol(height, i);
		cout << char(-37);
	}
	SetClr(2);
}
bool isLegalFoodCoordinate(Food f,Snake S1)
{
	for (int i = 0; i < S1.size; i++)
	{
		if (f.fP.x == S1.Ps[i].x && f.fP.y == S1.Ps[i].y)
		{
			return false;
		}
	}
	return true;
}
void foodGeneration(Snake *S, Food& f, int height, int width,int i)
{
	bool isLegal;
	do
	{
		isLegal = true;
		f.fP.y = rand() % height;
		f.fP.x = rand() % width;
		for (int j = 0; j < i; j++)
		{
			if (!isLegalFoodCoordinate(f, S[j]))
			{
				isLegal = false;
			}
		}
	} while (isLegal = false);
	f.isAlive = true;
	f.score = 1;
	f.sym = -37;
}
void init(Snake & S1,Food &f,int height, int width,int i)
{
	S1.score = 0;
	S1.size = 3;
	S1.sym = -37;
	S1.Ps = new Position[3];
	S1.Ps[0].y = height / 2;
	S1.Ps[0].x = width / 2;
	S1.Ps[1].y = height / 2;
	S1.Ps[1].x = width / 2 - 1;
	S1.Ps[2].y = height / 2;
	S1.Ps[2].x = width / 2 - 2;
	if (i == 0)
	{
		S1.Dir = RIGHT;
		S1.Rightkey = 77, S1.Leftkey = 75, S1.Upkey = 72, S1.Downkey = 80;
	}
	if (i == 1)
	{
		S1.Dir = DOWN;
		S1.Rightkey = 100, S1.Leftkey = 97, S1.Upkey = 119, S1.Downkey = 115;
	}
	if (i == 2)
	{
		S1.Dir = LEFT;
		S1.Rightkey = 106, S1.Leftkey = 103, S1.Upkey = 121, S1.Downkey = 104;
	}
	if (i == 3)
	{
		S1.Dir = UP;
		S1.Rightkey = 39, S1.Leftkey = 108, S1.Upkey = 112, S1.Downkey = 59;
	}
}
void Displaysnake(Snake S1)
{
	for (int i = 0; i < S1.size; i++)
	{
		gotoRowCol(S1.Ps[i].y, S1.Ps[i].x);
		cout << S1.sym;
	}
}
void Erasesnake(Snake S1)
{
	for (int i = 0; i < S1.size; i++)
	{
		gotoRowCol(S1.Ps[i].y, S1.Ps[i].x);
		cout << ' ';
	}
}
void MoveSnake(Snake &S1,int height,int width)
{
	for (int i = S1.size - 1; i > 0; i--)
	{
		S1.Ps[i] = S1.Ps[i-1];
	}
	switch (S1.Dir)
	{
	case(RIGHT):
	{
			S1.Ps[0].x++;
			if (S1.Ps[0].x == width)
			{
				S1.Ps[0].x = 0;
			}
		break;
	}
	case(LEFT):
	{
			S1.Ps[0].x--;
			if (S1.Ps[0].x == -1)
			{
				S1.Ps[0].x = width-1;
			}
		break;
	}
	case(DOWN):
	{
			S1.Ps[0].y++;
			if (S1.Ps[0].y == height)
			{
				S1.Ps[0].y = 0;
			}
		break;
	}
	case(UP):
	{
			S1.Ps[0].y--;
			if (S1.Ps[0].y == -1)
			{
				S1.Ps[0].y = height - 1;
			}
		break;
	}
	}
}

void changeDirection(Snake& S1, int ch)
{
	if (S1.Downkey == ch)
	{
		if (S1.Dir != UP)
		{
			S1.Dir = DOWN;
		}
	}
	else if (S1.Rightkey == ch)
	{
		if (S1.Dir != LEFT)
		{
			S1.Dir = RIGHT;
		}
	}
	else if (S1.Leftkey==ch)
	{
		if (S1.Dir != RIGHT)
		{
			S1.Dir = LEFT;
		}
	}
	else if(S1.Upkey==ch)
	{
		if (S1.Dir != DOWN)
		{
			S1.Dir = UP;
		}
	}
}
bool isFoodeaten(Snake S1,Food& f)
{
	return(S1.Ps[0].y == f.fP.y && S1.Ps[0].x == f.fP.x);
}
void DisplayFood(Food f)
{
	SetClr(7);
	gotoRowCol(f.fP.y, f.fP.x);
	cout << f.sym;
}
void expandsnake(Snake& S1)
{
	Position *HP =new Position[S1.size+1];
	for (int i = 0; i < S1.size; i++)
	{
		HP[i] = S1.Ps[i];
	}
	HP[S1.size] = S1.Ps[S1.size - 1];
	S1.size++;
	delete[] S1.Ps;
	S1.Ps = HP;
}
void sleep(int t)
{
	for (int i = 0; i < 1000000 * t; i++);
}
int main()
{
	int i = 0;
	srand(time(0));
	int height = 60, width = 80;
	cout << "Enter Number Of Players:" << endl;
	cin >> i;
	Snake* S = new Snake[i]{};
	Food f{};
	for (int j = 0; j < i; j++)
	{
		init(S[j], f, height, width, j);
	}
	foodGeneration(S,f,height,width,i);
	DisplayFood(f);
	square(height, width);
	char ch;
	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			for (int j = 0; j < i; j++)
			{
				changeDirection(S[j], ch);
			}
		}
		for (int j = 0; j < i; j++)
		{
			if (j == 0)
				SetClr(5);
			else if (j == 1)
				SetClr(2);
			else if (j == 2)
				SetClr(1);
			else if (j == 3)
				SetClr(6);
			Displaysnake(S[j]);
		}
		sleep(30);
		for (int j = 0; j < i; j++)
		{
			Erasesnake(S[j]);
			MoveSnake(S[j], height, width);
		}
		for (int j = 0; j < i; j++)
		{
			if (isFoodeaten(S[j], f))
			{
				S[j].score++;
				expandsnake(S[j]);
				f.isAlive = false;
				foodGeneration(S, f, height, width,i);
				DisplayFood(f);
			}
		}
		for (int j = 0; j < i; j++)
		{
			if (j == 0)
				SetClr(5);
			else if (j == 1)
				SetClr(2);
			else if (j == 2)
				SetClr(1);
			else if (j == 3)
				SetClr(6);
			gotoRowCol(height + j + 1, 5);
			cout << "Snake " << j + 1 << "score -" << S[j].score;
			SetClr(2);
		}
		square(height, width);
	}
}
