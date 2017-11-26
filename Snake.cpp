#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<windows.h>
#include<conio.h>
#include<thread>
using namespace std;

struct snakeBody {
	int posX;
	int posY;
};
struct meatCl {
	int posX;
	int posY;
	bool exist=false;
};

vector<snakeBody> eatSnake{ { 20,8 },{ 20,9 },{ 20,10 },{ 20,11 } ,{ 20,12 } };
int forWard[4][2] = { { 0,-1 },{ 0,1 },{ -1,0 },{ 1,0 } };
bool gameOver = false;
meatCl meat;
int (*pfor)[2] = &forWard[0];

void randMeat() {
	if (!meat.exist) {
		meat.exist = true;
		meat.posX = rand() % 40;
		meat.posY = rand() % 20;
		for (auto beg = eatSnake.begin(); beg != eatSnake.end(); ++beg) {
			if (meat.posX == (*beg).posX && meat.posY == (*beg).posY||meat.posX<1||meat.posX>20||meat.posY<1||meat.posY>40){
				meat.posX = rand() % 40;
				meat.posY = rand() % 20;
				beg = eatSnake.begin();
			}
		}
	}
}

void move() {
	int newX = eatSnake[0].posX + (*pfor)[0];
	int newY = eatSnake[0].posY + (*pfor)[1];
	if (newX > 0 && newX < 41 && newY > 0 && newY <21) {
		eatSnake.insert(eatSnake.begin(), { newX,newY });
		if (newX == meat.posX&&newY == meat.posY) {
			meat.exist = false;
		}
		else {
			eatSnake.pop_back();
		}
	}
	else {
		gameOver = true;
	}
}

void game() {
	//the main loop of game;
	while (!gameOver) {
		move();
		randMeat();
		system("cls");
		cout << "+----------------------------------------+" << endl;
		for (int i = 1; i<21; ++i) {

			string line(42, ' ');
			*(line.begin()) = '|';
			*(line.end() - 1) = '|';

			if (i == meat.posY) {
				line[meat.posX] = 'X';
			}
			auto snakeBeg = eatSnake.begin();
			while (snakeBeg != eatSnake.end()) {
				if ((*snakeBeg).posY == i) {
					if (line[(*snakeBeg).posX] == '@') {
						gameOver = true;
						break;
					}
					else line[(*snakeBeg).posX] = '@';
				}
				++snakeBeg;
			}

			cout << line << endl;
		}
		cout << "+----------------------------------------+" << endl;
		Sleep(300);
		cout << meat.exist << ' ' << meat.posX << ' ' << meat.posY;
	}
}

void control() {
	while (!gameOver) {
		Sleep(100);
		if (_kbhit()) {
			int keyVal = _getch();
			switch (keyVal) {
			case 119://key "w";
				if(pfor!=&forWard[1])
					pfor = &forWard[0];
				break;
			case 115:
				if (pfor != &forWard[0])
					pfor = &forWard[1];
				break;
			case 97:
				if(pfor!=&forWard[3])
					pfor = &forWard[2];
				break;
			case 100:
				if(pfor!=&forWard[2])
					pfor = &forWard[3];
				break;
			}
		}
	}
}

int main() {
	thread first(game);
	thread second(control);
	first.join();
	second.join();
	return 0;
}