#include<iostream>
#include<windows.h>
#include<time.h>
#include<ctime>
#include<stdlib.h>
#include<vector>
#include<conio.h>
#include<vector>
using namespace std;
const int width = 100;
const int height = 24;
const COORD ori = { 0,0 };
const COORD bird_ori = { 20,12 };
const COORD block_ori = { 30,8 };
const int accelaration = 1;
int score = 0;
vector<COORD> pos_vect;
const short block_width = 2;
const short block_diff = 20;
const short gap = 10;
const short dist = 15;
class bird
{
private:
	COORD bird_pos;
public:
	bird()
	{
		bird_pos.Y = bird_ori.Y;
		bird_pos.X = bird_ori.X;
	}
	COORD getpos()
	{
		return bird_pos;
	}
	void downacc()
	{
		bird_pos.Y += accelaration;
	}
	void upforce()
	{
		bird_pos.Y -= 5;
	}
	bool collision()
	{
		if (bird_pos.Y <= 0 || bird_pos.Y >= height)
			return true;
		else
		{
			for (int i = 0;i < pos_vect.size();i++)
			{
				if (((bird_pos.X >= pos_vect[i].X && bird_pos.X <= pos_vect[i].X + block_width) && (bird_pos.Y == pos_vect[i].Y || bird_pos.Y == pos_vect[i].Y + gap)) ||
					((bird_pos.X == pos_vect[i].X || bird_pos.X == pos_vect[i].X + block_width) && (bird_pos.Y <= pos_vect[i].Y || bird_pos.Y >= pos_vect[i].Y + gap)))
					return true;					
			}
			return false;
		}
	}
};
class block
{
public:
	block() {}
	void push_if_req()
	{
		if (pos_vect[0].X <= -block_width)
		{
			pos_vect.erase(pos_vect.begin());
			short temp = 2 + rand() % dist;
			if(pos_vect.back().X + block_width + block_diff <= width)
				pos_vect.push_back({ pos_vect.back().X + block_width + block_diff, temp });
		}

		if((width - pos_vect.back().X) >= block_width + block_diff)
		{
			short temp = 2 + rand() % dist;
			if (pos_vect.back().X + block_width + block_diff <= width)
				pos_vect.push_back({ pos_vect.back().X + block_width + block_diff, temp });
		}
	}
	void move()
	{
		for (int i = 0;i < pos_vect.size();i++)
		{
			pos_vect[i].X -= 1;
		}
	}
};
bird bird_obj;
block block_obj;
void board()
{
	system("color 8C");
	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{
			if (i == 0 || i == height - 1)
				cout << "-";
			else if (j == 0 || j == width - 1)
				cout << "|";
			else if (i == bird_obj.getpos().Y && j == bird_obj.getpos().X)
				cout << "o";
			else
			{
				bool print = false;
				for (int k = 0;k < pos_vect.size();k++)
				{
					if ((i <= pos_vect[k].Y || i >= pos_vect[k].Y + gap) && (j >= pos_vect[k].X && j <= pos_vect[k].X + block_width))
					{
						print = true;
						cout << "*";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << "\n";
	}
	cout << "score = " << score << endl;
	return;
}
int main()
{
	system("pause");
	system("cls");
	int count = 0;
	srand(time(NULL));
	pos_vect.push_back(block_ori);
	bool game_over = false;
	while (!game_over)
	{
		board();
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 32)
				bird_obj.upforce();
			else if (ch == 'p')
			{
				system("pause");
			}
			else
				bird_obj.downacc();
		}
		else
			bird_obj.downacc();
		block_obj.move();
		block_obj.push_if_req();

		game_over =  bird_obj.collision();
		if (count++ == 22)
		{
			score++;
			count = 0;
		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ori);
	}
	system("cls");
	system("color 0D");
	cout << "\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\tYour score is = " << score << endl;
	cout << "\n\n";
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t--------------GAME OVER-----------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t\t----------------------------------------" << endl;
	cin.get();
	return 0;
}