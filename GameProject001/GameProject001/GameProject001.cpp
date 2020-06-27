// GameProject001.cpp : Defines the entry point for the console application.
	
//
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <stdio.h>
#include <ctime>
#include <conio.h>



using namespace std;

int LENGTH = 2;
#define MAXLENGTH 1000

int Dwidth = 70;
int Dheight = 50;
HANDLE screen;


int colorchanger;
int arrayPos2 = 0;
int speed;
bool LEFT = false, RIGHT = false, DOWN = false, UP = false;
bool foodAlive = false;
bool backtomenu = false;

//int tailINFO[LENGTH];

int pastdir = 5; // 0 = LEFT, 1 = RIGHT, 2 = UP, 3 = DOWN


int gameBorderX;
int gameBorderY;
bool startagain = false;
bool gameEnd = false;
COORD areas[1000];
COORD stats;
bool ingame = false;
bool diditstart = false;

//int SnakePX[1000];
//int snakePY[1000];


struct snake {

	COORD coordinate[MAXLENGTH];

	void drawS() {


		SetConsoleCursorPosition(screen, coordinate[0]);
		SetConsoleTextAttribute(screen, 2);
		cout << 'o';

		SetConsoleCursorPosition(screen, coordinate[LENGTH-1]);
		cout << ' ';
	}
};

struct food {

	COORD fcor;

	void drawS() {
		SetConsoleCursorPosition(screen, fcor);
		SetConsoleTextAttribute(screen, 4);
		cout << 'x';

		if (foodAlive == false) {
			SetConsoleCursorPosition(screen, fcor);
			SetConsoleTextAttribute(screen, 2);
			cout << 'o';
		}
	}
};

struct border {

	COORD bcor;

	void drawS() {
		if (pastdir == 5) {
			SetConsoleCursorPosition(screen, bcor);
			SetConsoleTextAttribute(screen, 9);
			cout << '#';


			

		}
	}

};


void update(bool &end, snake &p, food &f);
void setup(snake &p, border &b);
void MainMenu();
void screenclear();


void playerchanger(snake &player, bool &rt);
//void taileater();


int main()
{
	int i = 0;
	char endgame;
	char startover;

	snake player;
	food food1;
	border border1;
	//srand(time(NULL));

		screen = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT DisplayArea = { 0, 0, Dwidth, Dheight };
		SetConsoleWindowInfo(screen, TRUE, &DisplayArea);

		CONSOLE_CURSOR_INFO ConCurInf;
		ConCurInf.dwSize = 10;
		ConCurInf.bVisible = false;
		SetConsoleCursorInfo(screen, &ConCurInf);


		while (i == 0) {
			diditstart = false;
			gameEnd = false;
			do {
				MainMenu();
			}while(backtomenu == true);
			screenclear();
			if (diditstart == true) {

				setup(player, border1);
				srand(time(NULL));

				while (gameEnd == false) {
					update(gameEnd, player, food1);
				}

				stats.X = gameBorderX / 2;
				stats.Y = gameBorderY / 2;
				SetConsoleCursorPosition(screen, stats);
				SetConsoleTextAttribute(screen, 4);
				cout << "GAME OVER";

				LEFT = false, RIGHT = false, DOWN = false, UP = false;
				foodAlive = false;
				arrayPos2 = 0;
				speed;
				LENGTH = 2;
				startagain = false;
				gameEnd = false;
				ingame = false;
				pastdir = 5;
				cout << "\n\tRESTARTING IN: ";
				
				Sleep(1000);

				cout << " 3";

				Sleep(1000);

				cout << " 2";

				Sleep(1000);

				cout << " 1";

				Sleep(1000);

				screenclear();
			}
			if (diditstart == false) {
				i = 1;
			}
		}

	return 0;
}


void MainMenu() {
		COORD pointer;

		COORD pointerSUbs;

		int key = NULL;
		char name[100];
		int diffuculty;
		bool start = false;
		bool down = false, up = false;
		bool keypressed = false;

		stats.X = 0;
		stats.Y = 1;
		int menX;
		int menY;

		SetConsoleCursorPosition(screen, stats);
		SetConsoleTextAttribute(screen, 2);
		cout << " ______       ___   __       ________       ___   ___      ______ ";
		cout << "\n/_____/\\     /__/\\ /__/\\    /_______/\\     /___/\\/__/\\    /_____/\\     ";
		cout << "\n\\::::_\\/_    \\::\\_\\\\  \\ \\   \\::: _  \\ \\    \\::.\\ \\\\ \\ \\   \\::::_\\/_    ";
		cout << "\n \\:\\/___/\\    \\:. `-\\  \\ \\   \\::(_)  \\ \\    \\:: \\/_) \\ \\   \\:\\/___/\\   ";
		cout << "\n  \\_::._\\:\\    \\:. _    \\ \\   \\:: __  \\ \\    \\:. __  ( (    \\::___\\/_  ";
		cout << "\n    /____\\:\\    \\. \\`-\\  \\ \\   \\:.\\ \\  \\ \\    \\: \\ )  \\ \\    \\:\\____/\\ ";
		cout << "\n    \\_____\\/     \\__\\/ \\__\\/    \\__\\/\\__\\/     \\__\\/\\__\\/     \\_____\\/ ";
		cout << "\n";
		for (int i = 0; i < Dwidth; i++) {
			cout << '-';
		}
		cout << "\n";
		for (int i = 0; i < Dwidth; i++) {
			cout << '=';
		}
		cout << "\n\t<USE ARROW KEYS TO NAVIGATE> \t\t version 0.1.0";
		/////////////////////////////////////////////
		if (ingame == false) {

			stats.X = Dwidth / 2;


			stats.Y = 15; // LOCATION START

			menX = stats.X;
			menY = stats.Y;

			SetConsoleCursorPosition(screen, stats);
			SetConsoleTextAttribute(screen, 2);
			cout << "START";

			stats.Y = 17; //LOCATION EXIT

			SetConsoleCursorPosition(screen, stats);
			SetConsoleTextAttribute(screen, 2);
			cout << "EXIT";

			stats.Y = 19; //LOCATION EXIT

			SetConsoleCursorPosition(screen, stats);
			SetConsoleTextAttribute(screen, 2);
			cout << "CREDITS";




			pointer.X = menX - 10;
			pointer.Y = menY;


			SetConsoleTextAttribute(screen, 2);
			SetConsoleCursorPosition(screen, pointer);
			cout << "-->";

			while (start == false) {
				key = _getch();
				pointerSUbs.X = pointer.X;
				pointerSUbs.Y = pointer.Y;
				if (key == 80 && pointer.Y < 19) //down arrow
				{
					pointer.Y += 2;
					SetConsoleCursorPosition(screen, pointer);
					cout << "-->";
				}
				else if (key == 72 && pointer.Y > 15)//up arrow
				{
					pointer.Y -= 2;
					SetConsoleCursorPosition(screen, pointer);
					cout << "-->";
				}



				if (pointer.Y == 15 && key == 32) {
					start = true;

					screenclear();
				}
				else if (pointer.Y == 19 && key == 32) {
					screenclear();
					bool done = false;

					while (done == false) {
						stats.X = 0;
						stats.Y = 1;

						SetConsoleCursorPosition(screen, stats);
						SetConsoleTextAttribute(screen, 2);
						cout << "PRESS ESC TO RETURN TO HOME PAGE";

						cout << "\n		     _           _ ";
						cout << "\n                    | |         | |";
						cout << "\n  ___ _ __ ___  __ _| |_ ___  __| |";
						cout << "\n / __| '__/ _ \\/ _` | __/ _ \\/ _` |";
						cout << "\n| (__| | |  __/ (_| | ||  __/ (_| |";
						cout << "\n \\___|_|  \\___|\\__,_|\\__\\___|\\__,_|";

						cout << "\n\t _           ";
						cout << "\n\t| |          ";
						cout << "\n\t| |__  _   _ ";
						cout << "\n\t| '_ \\| | | |";
						cout << "\n\t| |_) | |_| |";
						cout << "\n\t|_.__/ \\__, |";
						cout << "\n\t        __/ |";
						cout << "\n\t       |___/                     ";

						cout << "\n   ___  _____ _____ _   _ _   _  ___  ";
						cout << "\n  |_  ||  _  /  ___| | | | | | |/ _ \\ ";
						cout << "\n    | || | | \\ '--.| |_| | | | / /_\\ \\'";
						cout << "\n    | || | | |`--. \\  _  | | | |  _  |";
						cout << "\n/\\__/ /\\ \\_/ /\\__/ / | | | |_| | | | |";
						cout << "\n\\____/  \\___/\\____/\\_| |_/\\___/\\_| |_/";

						key = _getch();
						if (key == 27) {
							done = true;
							start = true;
							backtomenu = true;
							screenclear();
						}
					}
				}
				
				else if (pointer.Y == 17 && key == 32) {
					start = true;
					backtomenu = false;

				}



				SetConsoleCursorPosition(screen, pointerSUbs);
				cout << "   ";
				key = NULL;

			}


			/////////////////////////////////////////////


			if (start == true && pointer.Y == 15) {
				stats.X = 1;
				stats.Y = 1;
				backtomenu = false;
				diditstart = true;


				/* 
				do{
					SetConsoleCursorPosition(screen, stats);
					SetConsoleTextAttribute(screen, 2);


					SetConsoleCursorPosition(screen, stats);
					SetConsoleTextAttribute(screen, 2);
					cout << "SET DIFFICULTY (5: Easy, 1 HARD) *press enter when done* :   ";
					SetConsoleCursorPosition(screen, stats);
					cout << "SET DIFFICULTY (5: Easy, 1 HARD) *press enter when done* : ";
					cin >> diffuculty;

					speed = (diffuculty * 100) / 2;
				} while (diffuculty > 5 || diffuculty < 1);
				*/






				stats.X = 25;


				stats.Y = 3;
				SetConsoleCursorPosition(screen, stats);
				SetConsoleTextAttribute(screen, 2);
				cout << "SELECT DIFFUCULTY <use arrow keys>";



				stats.Y = 5; // LOCATION 1

				menX = stats.X;
				menY = stats.Y;

				SetConsoleCursorPosition(screen, stats);
				SetConsoleTextAttribute(screen, 2);
				cout << "1 HARD";

				stats.Y = 7; //LOCATION 2

				SetConsoleCursorPosition(screen, stats);
				SetConsoleTextAttribute(screen, 2);
				cout << "2 MEDIUM";

				stats.Y = 9; //LOCATION 3

				SetConsoleCursorPosition(screen, stats);
				SetConsoleTextAttribute(screen, 2);
				cout << "3 EASY";




				pointer.X = menX - 10;
				pointer.Y = menY;

				
				SetConsoleTextAttribute(screen, 2);
				SetConsoleCursorPosition(screen, pointer);
				cout << "-->";
				
				key = NULL;
				diffuculty = NULL;
				while(diffuculty > 3 || diffuculty < 1){

					key = _getch();
					pointerSUbs.X = pointer.X;
					pointerSUbs.Y = pointer.Y;
					if (key == 80 && pointer.Y < 9) //down arrow
					{
						pointer.Y += 2;
						SetConsoleCursorPosition(screen, pointer);
						cout << "-->";
					}
					else if (key == 72 && pointer.Y > 5)//up arrow
					{
						pointer.Y -= 2;
						SetConsoleCursorPosition(screen, pointer);
						cout << "-->";
					}

					if (pointer.Y == 5 && key == 32) {
						diffuculty = 1;
					}

					else if (pointer.Y == 7 && key == 32) {
						diffuculty = 2;
					}

					else if (pointer.Y == 9 && key == 32) {
						diffuculty = 3;
					}

					SetConsoleCursorPosition(screen, pointerSUbs);
					cout << "   ";
					key = NULL;
				}

				speed = (diffuculty * 100) / 2;
				
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Welcome to Snake! CONTROLS: UP,DOWN,LEFT,RIGHT. Score is determined\n by the length of snake. Good Luck!!!";
				stats.X = Dwidth - 25;
				stats.Y = Dheight - 25;

				SetConsoleCursorPosition(screen, stats);
				SetConsoleTextAttribute(screen, 5);

				cout << "PRESS SPACE TO CONITNUE..";


				while (key != 32) {
					key = _getch();
				}
			}
		}
	}


void screenclear() {
	COORD clear;
	for (int y = 0; y < Dheight; y++) {
		for (int x = 0; x < Dwidth; x++) {
			clear.X = x;
			clear.Y = y;
			SetConsoleCursorPosition(screen, clear);
			SetConsoleTextAttribute(screen, 3);
			cout << "#";
		}
	}
	for (int y = 0; y < Dheight; y++) {
		for (int x = 0; x < Dwidth; x++) {
			clear.X = x;
			clear.Y = y;
			SetConsoleCursorPosition(screen, clear);
			cout << " ";
		}
	}
}




void setup(snake &p, border &b) {


	bool start = false;


	b.bcor.X = 0;
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i <= Dheight - (Dheight / 2); i++) {
			b.bcor.Y = i;
			b.drawS();
		}
		b.bcor.X = (Dwidth/2);
	}
	b.bcor.Y = 0;
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i <= Dwidth - (Dwidth / 2); i++) {
			b.bcor.X = i;
			b.drawS();
		}
		b.bcor.Y = (Dheight / 2);
	}

	gameBorderX = Dwidth/2;
	gameBorderY = Dheight/2;


	if (gameBorderX % 2 != 0) {
		gameBorderX++;
	}




	for (int y = 1; y < gameBorderY; y++) {
		for (int x = 2; x < gameBorderX-1; x=x+2) {
			areas[arrayPos2].X = x;
			areas[arrayPos2].Y = y;
			arrayPos2++;
		}
	}
	playerchanger(p, start);
	p.drawS();
	//cout << arrayPos2;
}

void update(bool &end, snake &p, food &f) {

	char stopper;
	bool start = true;
	
	int validP = 0;
	int randomCra;
	int validcord = 0;
	bool has = false;

	/*
	for (int arrayPos = 0; arrayPos < LENGTH; arrayPos++) {
		if (areas[arrayPos].X != p.coordinate[arrayPos].X && areas[arrayPos].Y != p.coordinate[arrayPos].Y && areas[arrayPos].X != 0) {
			XvalidPositions[validP] = areas[arrayPos].X;
			YvalidPositions[validP] = areas[arrayPos].Y;

		}
		validP++;
	}
		
	for (arrayPos; arrayPos <= arrayPos2; arrayPos++) {
		while (cordleng < LENGTH) {
			if (areas[arrayPos].X != p.coordinate[cordleng].X && areas[arrayPos].Y != p.coordinate[cordleng].Y) {
				
			}
			else {
				cordleng++;
			}
		}
		
	}

	for(arrayPos; arrayPos <= arrayPos2; arrayPos++) {
	while (sfind < LENGTH) {
	if (areas[arrayPos].X != p.coordinate[sfind].X && areas[arrayPos].Y != p.coordinate[sfind].Y) {
	XvalidPositions[validcord] = areas[arrayPos].X;
	YvalidPositions[validcord] = areas[arrayPos].Y;
	validcord++;
	arrayPos++;
	}
	else {
	sfind++;
	arrayPos++;
	}
	}
	XvalidPositions[validcord] = areas[arrayPos].X;
	YvalidPositions[validcord] = areas[arrayPos].Y;
	validcord++;
	}

	position 0
	*/
	bool good = false;
	int sub;
	int arrayPos = 0;
	int sfind = 0;
	int XvalidPositions[1000];
	int YvalidPositions[1000];
		while(arrayPos < arrayPos2) {
			for(sfind = 0; sfind < LENGTH; sfind++){
				sub = validcord;
				if (areas[arrayPos].X == p.coordinate[sfind].X && areas[arrayPos].Y == p.coordinate[sfind].Y) {
					validcord = sub;
					sfind = LENGTH+1;
					good = false;
				}
				else {
					XvalidPositions[validcord] = areas[arrayPos].X;
					YvalidPositions[validcord] = areas[arrayPos].Y;
					good = true;
				}
			}
			if (good == true) {
				validcord++;
			}
			arrayPos++;
		}
	





	randomCra = rand() % validcord;
	if (foodAlive == false) {
		f.fcor.X = XvalidPositions[randomCra];
		f.fcor.Y = YvalidPositions[randomCra];
		foodAlive = true;
	}
	
	if (p.coordinate[0].X == f.fcor.X && p.coordinate[0].Y == f.fcor.Y) {
		LENGTH++;

		foodAlive = false;
	
	}
	playerchanger(p, start);


	if (p.coordinate[0].X >= gameBorderX || p.coordinate[0].X <= 0) {
		gameEnd = true;
	}
	if (p.coordinate[0].Y >= gameBorderY || p.coordinate[0].Y <= 0) {
		gameEnd = true;
	}

	bool hit = false;
	if (pastdir < 5) {
		for (int any = 1; any < LENGTH; any++) {
			if (p.coordinate[0].X == p.coordinate[any].X && p.coordinate[0].Y == p.coordinate[any].Y) {
				hit = true;
			}
			else {
				hit = false;
			}
			if (hit == true) {
				gameEnd = true;
			}
		}
	}
	




	stats.X = gameBorderX + 2;
	stats.Y = 8;

	SetConsoleCursorPosition(screen, stats);
	SetConsoleTextAttribute(screen, 8);
	cout << "Points: " << LENGTH-2;




	f.drawS();
	p.drawS();
	Sleep(speed);
}

void playerchanger(snake &p, bool &rt) {

	if (rt == false) {
		for (int i = 0; i < LENGTH; i++) {
			p.coordinate[i].X = areas[90].X;
			p.coordinate[i].Y = areas[90].Y;
		}
	}
	else if(rt == true){


		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && pastdir != 1) {
			pastdir = 0;
			LEFT = true;
			RIGHT = false, DOWN = false, UP = false;
		}

		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && pastdir != 0) {
			pastdir = 1;
			RIGHT = true;
			DOWN = false, UP = false, LEFT = false;

		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000 && pastdir != 3) {
			pastdir = 2;
			UP = true;
			LEFT = false, RIGHT = false, DOWN = false;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && pastdir != 2) {
			pastdir = 3;
			DOWN = true;
			LEFT = false, RIGHT = false, UP = false;
		}




		// 0 = LEFT, 1 = RIGHT, 2 = UP, 3 = DOWN

		if (RIGHT == true && pastdir != 0) {
			pastdir = 1;
			for (int i = (LENGTH - 1); i >= 0 ; i--) {
				if (i > 0) {
					p.coordinate[i].X = p.coordinate[i-1].X;
					p.coordinate[i].Y = p.coordinate[i-1].Y;
				}
			}
			p.coordinate[0].X += 2;

		}
		else if (LEFT == true && pastdir != 1) {
			pastdir = 0;
			for (int i = (LENGTH - 1); i >= 0; i--) {
				if (i > 0) {
					p.coordinate[i].X = p.coordinate[i - 1].X;
					p.coordinate[i].Y = p.coordinate[i - 1].Y;
				}
			}
			p.coordinate[0].X -= 2;


		}
		else if (DOWN == true && pastdir != 2) {
			pastdir = 3;
			for (int i = (LENGTH - 1); i >= 0; i--) {
				if (i > 0) {
					p.coordinate[i].X = p.coordinate[i - 1].X;
					p.coordinate[i].Y = p.coordinate[i - 1].Y;
				}
			}
			p.coordinate[0].Y += 1;


		}
		else if (UP == true && pastdir != 3) {
			pastdir = 2;
			for (int i = (LENGTH - 1); i >= 0; i--) {
				if (i > 0) {
					p.coordinate[i].X = p.coordinate[i - 1].X;
					p.coordinate[i].Y = p.coordinate[i - 1].Y;
				}
			}
			p.coordinate[0].Y -= 1;
		}

	}
}


