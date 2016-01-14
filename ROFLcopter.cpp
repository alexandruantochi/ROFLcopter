// ROFLcopter.cpp : Defines the entry point for the console application.
//

/*string text;
	
	*/

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

struct scoreboard {
	string name, difficulty;
	unsigned int points;
};

int difficulty = 1;
int yU, yD, xO,score=-1;
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
	int x, y;
	x = 0;
	y = 15;
	bool exit = false;
	ifstream ecranPrincipal, animation1, animation2;
	ecranPrincipal.open("F:\\Scoala\\Anul I\\Sem I\\IP\\ROFLcopter\\Art\\startScreen.txt");
	animation1.open("F:\\Scoala\\Anul I\\Sem I\\IP\\ROFLcopter\\Art\\animation1.txt");
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
	yU = rand() % 35 + 5 - difficulty;
	yD = yU + 18 - 2 * difficulty;
	xO = 210;
	score++;
	system("CLS");
}

void animation(int yC,int xO) {
	int xC = 10;
	for (int k = 0;k < 3;k++) {
		gotoxy(xC, yC - k);
		cout <<"                           ";
		gotoxy(xC, yC + 7 + k);
		cout <<"                           ";
	}
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
	cout << "         :LOL:ROFL:ROFL";
	Sleep(50);
	gotoxy(xC, yC);
	cout << "  ROFL:ROFL:LOL:           ";
	Sleep(50);
	gotoxy(xC, yC);
	cout << "         :LOL:ROFL:ROFL";
	for (int i = 0;i < 49;i++)
		if (i <= yU || i >= yD) {
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
	over.open("F:\\Scoala\\Anul I\\Sem I\\IP\\ROFLcopter\\Art\\gameOver.txt");
	gotoxy(0, 15);
	while (!over.eof()) {
		getline(over, text);
		cout << setw(55) << "";
		cout << text << endl;
	}
	Beep(300, 700);
	over.close();
	gotoxy(90, 30);
	cout << "Your score is: " << score << endl;
	gotoxy(90, 33);
	cout << "Enter your name: ";
	cin >> name;
	if (difficulty == 1) diff = "(EASY)";
	else if (difficulty == 2) diff = "(NORMAL)";
	else diff = "(EPILEPTIC)";
	scoreBoard.open("F:\\Scoala\\Anul I\\Sem I\\IP\\ROFLcopter\\scoreBoard.txt", ios::app);
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
		animation(yC, xO);
		yC+=1;
		xO -= 5+ceil(difficulty*2.5);
		if (xO < 7) resetxO();
		if (_kbhit()) {
			_getch();
			yC -= 3;
			Sleep(50);
		}
		gotoxy(0, 48);
		cout << "SCORE:" << score;
		if (yC > 41 || yC<1) collision = true;
		if (xO<26 && (yC<yU || (yC+7) > yD)) collision = true;
	}
	gameOver();
};

void scoreBoard() {
	system("CLS");
	string board,points,diff;
	int k=0,i = 0;
	ifstream scoreBoard;
	scoreBoard.open("F:\\Scoala\\Anul I\\Sem I\\IP\\ROFLcopter\\scoreBoard.txt");
	gotoxy(90, 14);
	cout << "**********SCORE BOARD**********"; //31
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
};

void credits() {
	int y=45;
	ifstream credits;
	string text;
	system("CLS");
	credits.open("F:\\Scoala\\Anul I\\Sem I\\IP\\ROFLcopter\\Art\\credits.txt");
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

};

int main()
{
	char again;
		system("Color 1A");
		system("Mode 650");
		startScreen();
		startMenu();
		system("CLS");
		gotoxy(90, 30);
		cout << "Play again? [Y/N]";
		cin >> again;
		if (again == 'y' || again == 'Y') play();
		else 
		{
			system("CLS");
			gotoxy(90, 30);
			cout << "Go back to Menu? [Y/N]";
			cin >> again;
			if (again == 'y' || again == 'Y') startMenu();
			else {
				system("CLS");
				gotoxy(90, 30);
				cout << "Thank you for playing!";
			}
			Sleep(1750);
			return 0;
		}
};




