// ROFLcopter - A C++ Console Game.



#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

const char version[] = "v1.2.3 [1080p compatible]";
int difficulty = 1;
int upperWallOpening, lowerWallOpening, wallPosition,score=-1;
bool collision = false;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void startScreen() {
	string text;
	ifstream ecranPrincipal, animation1, animation2;
	ecranPrincipal.open("startScreen.dat");
	animation1.open("animation1.dat");
	gotoxy(0, 15);
	while (!ecranPrincipal.eof()) {
		getline(ecranPrincipal, text);
		cout << setw(55) << "";
		cout << text << endl;
		}
	ecranPrincipal.close();
	while (!animation1.eof()) {
		getline(animation1, text);
		cout << setw(90) << "";
		cout << text << endl;
		}
	gotoxy(90, 26);
	cout << "          LOL           ";
	gotoxy(155, 16);
	cout << version;
	do {
	gotoxy(89, 26);
	cout << "          ";
	gotoxy(103, 26);
	cout << ":ROFL:ROFL";
	gotoxy(90, 35);
	cout << "[Press any key to continue]";
	Sleep(100);
	gotoxy(103, 26);
	cout << "          ";
	gotoxy(90, 26);
	cout<<"ROFL:ROFL:";
	Sleep(100);
	} while (!_kbhit());
};

void chooseDif() {
	system("CLS");
	int x = 0;
	gotoxy(100, 20);
	cout << "CHOOSE DIFFICULTY" << endl;
	gotoxy(100, 22);
	cout << "1 - EASY" << endl;
	gotoxy(100, 24);
	cout << "2 - NORMAL" << endl;
	gotoxy(100, 26);
	cout << "3 - EPILEPTIC" << endl;
	x = _getch();
	switch (x) {
	case 49:
		difficulty = 1;
		break;
	case 50:
		difficulty = 2;
		break;
	case 51:
		difficulty = 3;
		break;
	default:
		chooseDif();
		break;
	}
};

void resetxO() {
	srand(time(NULL));
	upperWallOpening = rand() % 35 + 5 - difficulty;
	lowerWallOpening = upperWallOpening + 18 - 2 * difficulty;
	wallPosition = 195;
	score++;
	system("CLS");
}

void animation(int yC,int xO) {
	int xC = 10;
	gotoxy(xC, yC + 1);
	cout << "           |           ";
	gotoxy(xC, yC + 2);
	cout << " L    /---------       ";
	gotoxy(xC, yC + 3);
	cout << " O=====       []\\     ";
	gotoxy(xC, yC + 4);
	cout << " L     \\         \\   ";
	gotoxy(xC, yC + 5);
	cout << "        \\_______-+|   ";
	gotoxy(xC, yC + 6);
	cout << "       ____T____T___/) ";
	gotoxy(xC, yC);
	cout << "         :LOL:ROFL:ROFL"; //23 spaces
	Sleep(50);
	gotoxy(xC, yC);
	cout << "  ROFL:ROFL:LOL:           ";
	Sleep(50);
	gotoxy(xC, yC);
	cout << "         :LOL:ROFL:ROFL";
	for (int i = 0;i < 47;i++)
		if (i <= upperWallOpening || i >= lowerWallOpening) {
			gotoxy(xO, i);
			cout << "WTF:WTF:WTF";
			gotoxy(xO +11, i);
			cout << "                 ";
		}
};

void gameOver() {
	ifstream over;
	ofstream scoreBoard;
	string text, name, again,diff;
	over.open("gameOver.dat");
	gotoxy(0, 15);
	while (!over.eof()) {
		getline(over, text);
		cout << setw(55) << "";
		cout << text << endl;
	}
	if (difficulty == 1) diff = "(EASY)";
	else if (difficulty == 2) diff = "(NORMAL)";
	else diff = "(EPILEPTIC)";
	Beep(300, 700);
	over.close();
	gotoxy(90, 30);
	cout << "Your score is: " << score << endl;
	gotoxy(90, 33);
	cout << "Enter your name: ";
	cin >> name;
	/*for (int i = 0;i < 9;i++) {
		if (board.pts[i] < score)
		{
			aux.pts[0] = board.pts[i];
			aux.name[0] = board.name[i];
			aux.level[0] = board.level[i];
			board.pts[i + 1] = aux.pts[0];
			board.name[i + 1] = aux.name[0];
			board.level[i + 1] = aux.level[0];
			board.pts[i] = score;
			board.name[i] = name;
			board.level[i] = diff;
		}
	}
	*/
	scoreBoard.open("scoreBoard.dat", ios::app);
	scoreBoard << name << " "<<diff<<"\n";
	scoreBoard << score << "\n";
	scoreBoard.close();
	Sleep(200);
};

void play() {
	score = 0;
	system("CLS");
	chooseDif();
	system("CLS");
	int d = difficulty;
	int xC = 10, yC = 25;
	collision = false;
	resetxO();
	while (!collision) {
		animation(yC, wallPosition);
		yC+=1;
			gotoxy(xC, yC - 1);
			cout << "                           ";
		wallPosition -= 5+ceil(difficulty*2.5);
		if (wallPosition < 7) resetxO();
		if (_kbhit()) {
			_getch();
			yC -= 3;
			for (int k = 0;k < 3;k++) {
				gotoxy(xC, yC + 7 + k);
				cout << "                           ";
			}
		}
		gotoxy(0, 45);
		cout << "SCORE: " << score << endl;
		cout << "DIFFICULTY: " << difficulty;
		if (yC > 41 || yC<1) collision = true;
		if (wallPosition<26 && (yC<=upperWallOpening || (yC+7) >= lowerWallOpening)) collision = true;
	}
	gameOver();
};

void scoreBoard() {
	system("CLS");
	string board,points,diff;
	int k=0,i = 0;
	ifstream scoreBoard;
	scoreBoard.open("scoreBoard.dat");
	gotoxy(90, 14);
	cout << "**********SCORE BOARD**********"; //31
	/*for (int i = 0; i < 9; i++) {
		gotoxy(90, 15 + k);
		cout << "*   " << board.name[i]<<" "<<board.level[i];
		gotoxy(117, 15 + k);
		cout << board.pts[i];
		gotoxy(120, 15 + k);
		cout << "*";
		k++;
	}
	*/  
	while (!scoreBoard.eof()) {
		getline(scoreBoard, board);
		getline(scoreBoard, points);
		gotoxy(90, 15+k);
		cout << "*   " << board;
		gotoxy(117, 15 + k);
		cout << points;
		gotoxy(120, 15 + k);
		cout << "*";
		k++;
		}
	cout << endl;
	gotoxy(90, 15 + k-1);
	cout << "*******************************" << endl;
	scoreBoard.close();
	gotoxy(90, 15 + k + 1);
	system("pause");
	system("CLS");
};

void credits() {
	int y=45;
	ifstream credits;
	string text;
	system("CLS");
	credits.open("credits.dat");
	do {
		while (!credits.eof()) {
			getline(credits, text);
			gotoxy(35, y);
			cout << text;
			y++;
		}
		Sleep(400);
		system("CLS");
		y -= 13;
		credits.seekg(0);
		} while (y > 10);
	while (!credits.eof()) {
		getline(credits, text);
		gotoxy(35, y);
		cout << text;
		y++;
		}
	credits.close();

		const int C = 261;
		const int Cis = 277;
		const int D = 293;
		const int Dis = 311;
		const int E = 329;
		const int F = 349;
		const int Fis = 369;
		const int G = 391;
		const int Gis = 415;
		const int A = 440;
		const int Ais = 466;
		const int H = 493;
		const int Takt = 1700;

		Beep(E * 2, Takt / 4);
		Beep(H * 1, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(D * 2, Takt / 4);
		Beep(C * 2, Takt / 8);
		Beep(H * 1, Takt / 8);
		Beep(A * 1, Takt / 4);
		Beep(A * 1, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(D * 2, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(H * 1, Takt / 2.5);
		Beep(C * 2, Takt / 8);
		Beep(D * 2, Takt / 4);
		Beep(E * 2, Takt / 4);
		Beep(C * 2, Takt / 4);
		Beep(A * 1, Takt / 4);
		Beep(A * 1, Takt / 4);
		Sleep(Takt / (8 / 3));
		Beep(D * 2, Takt / 3.25);
		Beep(F * 2, Takt / 8);
		Beep(A * 2, Takt / 8);
		Beep(A * 2, Takt / 8);
		Beep(G * 2, Takt / 8);
		Beep(F * 2, Takt / 8);
		Beep(E * 2, Takt / 3);
		Beep(C * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(D * 2, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(H * 1, Takt / 4);
		Beep(H * 1, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(D * 2, Takt / 4);
		Beep(E * 2, Takt / 4);
		Beep(C * 2, Takt / 4);
		Beep(A * 1, Takt / 4);
		Beep(A * 1, Takt / 4);

};

void startMenu() {
	system("CLS");
	int x=0;
	gotoxy(100, 20);
	cout << "MENU" << endl;
	gotoxy(100, 22);
	cout << "1 - PLAY" << endl;
	gotoxy(100, 24);
	cout << "2 - SCOREBOARD" << endl;
	gotoxy(100, 26);
	cout  <<"3 - CREDITS" << endl;
	x = _getch();
	switch (x) {
	case 49:
		play();
		break;
	case 50:
		scoreBoard();
		break;
	case 51:
		credits();
		break;
	default:
		startMenu();
		break;
	}
	startMenu();
};

int main()
{
		system("Color 1A");
		system("Mode 650");
		startScreen();
		startMenu();
		return 0;
};




