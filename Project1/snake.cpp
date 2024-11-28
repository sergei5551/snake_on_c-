#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <windows.h>

using namespace std;

bool gameOver; // ���������� ��� ��������� ��������� ��� ���������

enum eDirection { STOP, LEFT, RIGHT, UP, DOWN };
eDirection dir; // ���������� ����������� �������� � ���� �� ������
int speed_snake = 200; // �������� ��� ������

class snake {
private:
	int x, y;
	int fruitX, fruitY;
	int score;
	int tailX[100], tailY[100];
	int nTail = 0;

	int w = 25;
	int h = 25;

public:


	snake() {
		int par;
		cout << "������� ������� ��������� ����" << endl;
		cout << "1 - ������" << endl;
		cout << "2 - ��������" << endl;
		cout << "3 - �������" << endl;
		cin >> par;
		// Change_the_difficulty, ���� �� ����� ������, �� ����� ����� ����� �������
		if (par == 1) { // ������ �����
			this->w = 10;
			this->h = 10;
			speed_snake = 300;
		}
		else if (par == 2) { // ������� �����
			this->w = 20;
			this->h = 20;
			speed_snake = 250;
		}
	}

	void Setup() {
		gameOver = false;
		dir = STOP;
		this->x = w / 2 - 1;
		this->y = h / 2 - 1;
		srand(time(0));
		fruitX = rand() % (w - 1);
		fruitY = rand() % h;
		score = 0;
	}

	void Draw() {
		// ����������� ��������
		system("cls");
		// ������� �������
		for (int i = 0; i < w + 1; i++) {
			cout << "#";
		}
		cout << endl;
		// ������� �������
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {

				if (j == 0 || j == w - 1) {
					cout << "#";
				}
				if (i == y && j == x) {
					cout << "�";
				}
				else if (i == fruitY && j == fruitX) {
					cout << "&";
				}
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "�";
						}
					}
					if (!print) {
						cout << " ";
					}

				}
			}
			cout << endl;
		}



		// ������ �������
		for (int i = 0; i < w + 1; i++) {
			cout << "#";
		}
		cout << endl;
		printf("Score: %i", score);
	}

	void Input() {
		if (_kbhit()) {
			char ch = _getch();
			switch (ch) {

			case 'a': 
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's': 
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
			}
		}
	}

	void Logic() {
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2x, prev2y;
		tailX[0] = x;
		tailY[0] = y;

		for (int i = 1; i < nTail; i++) {
			prev2x = tailX[i];
			prev2y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2x;
			prevY = prev2y;
		}

		switch (dir)
		{

		case LEFT:
			this->x--;
			break;
		case RIGHT:
			this->x++;
			break;
		case UP:
			this->y--;
			break;
		case DOWN:
			this->y++;
			break;
		}


		//
		if (this->x >= w - 1) {
			this->x = 0;
		}
		else if (this->x < 0) {
			this->x = w - 2;
		}

		if (this->y >= h) {
			this->y = 0;
		}
		else if (this->y < 0) {
			this->y = h - 1;
		}
		//

		for (int i = 0; i < nTail; i++) {
			if (tailX[i] == x && tailY[i] == y) {
				gameOver = true;
			}
		}

		if (x == fruitX && y == fruitY) {
			score += 1;
			srand(time(0));
			fruitX = rand() % (w - 1);
			fruitY = rand() % h;
			nTail++;
		}
	}
};

int main() {

	setlocale(0, "RUS");
	snake obj;


	// ��������� ��������� ����
	obj.Setup();

	// ���� ��������� � ������ ����
	while (!gameOver) {
		obj.Draw();
		obj.Input();
		obj.Logic();
		Sleep(speed_snake);
	}



	cout << endl;
	system("pause");
	return 0;
}