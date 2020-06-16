#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <clocale>
#include "Console.h"
#include "Gamer.h"
#include "Pole.h"
using namespace std;

int main()
{
	bool e = 0;
	setlocale(LC_CTYPE, "Russian");
	in_mass_net();//��������� ������ ����
	int message = 0; // ���������� ������ ���� ��������� (0 - �� ��; 1 - �������� �������; 2 - ���� �����������)

	srand(static_cast<unsigned int>(time(NULL)));

	int choise;
	switch (menu())
	{
	case 1:
		human.tanks_init();//�������� ����� � ���� ����
		computer.tanks_init_first();//�������� ����� � ���� ����������
		break;
	case 2:
		human.tanks_init();//�������� ����� � ���� ����
		computer.tanks_init_second();//�������� ����� � ���� ����������
		break;
	case 3:
		human.tanks_init();//�������� ����� � ���� ����
		computer.tanks_init();//�������� ����� � ���� ����������
		break;
	case 4:
		break;
	}

	system("cls");

	menu_start();

	_getch();
	while (message != 2)
	{

		int user_input = 0;
		system("cls");
		map_init();//�������� � ������ ���������� � ������ ������
		show();
		if (message == 1) {// ��� ��������� 1 - ������� �������� ��������
			SetColor(Red, Black);
			cout << "�� ����� �������� ��������!\n";
		}
		SetColor(LightGreen, Black);
		message = 0;
		int symbol, number;

		user_input = input(symbol, number);//���� ��������� x � y ������������� 
		if (user_input == 1)
		{
			message = 1;
			continue;
		}

		e = turn(symbol, number);//��� ������������
		if (e == 1) { continue; }
		e = turn();//��� ����������
		message = check_ending();//�������� �����
	}

	system("cls");

	if (human.defeat_flag == 1) {
		menu_not_win();
	}
	if (computer.defeat_flag == 1) {
		menu_win();
	}
	_getch();
	return 0;
}


/*��������� � ������ map ���������� � ������ ������*/
void map_init()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			if (human.tanks[i][j] == 1)
			{
				map[2 + 2 * i][5 + 2 * j] = ' ';
			}
			else
				if (human.tanks[i][j] == 2)
				{
					map[2 + 2 * i][5 + 2 * j] = 2;
				}
				else
					if (human.tanks[i][j] == 3)
					{
						map[2 + 2 * i][5 + 2 * j] = '.';
					}
					else
						if (human.tanks[i][j] == 4)
						{

							map[2 + 2 * i][5 + 2 * j] = 'X';
						}


			if (human.hits[i][j] == 0)
			{
				map[2 + 2 * i][41 + 2 * j] = ' ';
			}
			else
				if (human.hits[i][j] == 1)
				{
					map[2 + 2 * i][41 + 2 * j] = '*';
				}
				else
					if (human.hits[i][j] == 2)
					{
						map[2 + 2 * i][41 + 2 * j] = 'X';
					}
		}
}

/*���� ��������� ������������*/
int input(int& symbol, int& number)
{
	symbol = -1, number = -1;
	int massage = 0;
	char ch, d;//�����/�����
	SetColor(Yellow, Black);
	cout << "���������!\n";
	cout << "������� ����� �� A �� J:";
	SetColor(LightGreen, Black);
	cin >> ch;
	for (int i = 0; i < 10; i++)
	{
		if (ch == symbols[i]) {
			symbol = i;
		}
	}
	if (symbol == -1) {
		massage = 1;
		return massage;
	}
	SetColor(Yellow, Black);
	cout << "������� ����� �� 0 �� 9:";
	SetColor(LightGreen, Black);
	cin >> d;
	for (int i = 0; i < 10; i++)
	{
		if (d == numbers[i]) {
			number = i;
		}
	}
	if (number == -1) {
		massage = 1;
		return massage;
	}
	return massage;
}
/*����� ����*/
void show()
{
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << map[i][j];
		}
		cout << "\n";
	}
}

/*���� ������������*/
bool turn(int symbol, int number)
{
	bool e = 0;
	if ((human.hits[number][symbol] == 1) || (human.hits[number][symbol] == 2))
	{
		cout << " �� ���� ��� ��������! ���������� ��� ���...";
		e = 1;
		_getch();
	}
	else
	{
		if (computer.tanks[number][symbol] == 1)
		{
			human.hits[number][symbol] = 1;
			SetColor(Red, Black);
			cout << "������!!!";
			SetColor(LightGreen, Black);
			_getch();
		}
		else if (computer.tanks[number][symbol] == 2)
		{
			human.hits[number][symbol] = 2;
			computer.tanks[number][symbol] = 3;
			SetColor(Yellow, Black);
			cout << "���, �� ������ ����������!!!" << endl;
			cout << "������ ������ ��� ��� ";
			SetColor(LightGreen, Black);
			e = 1;
			_getch();
		}
	}
	return e;
}
/*���� ����������*/
bool turn()
{
	bool e = 0;
	while (e == 0)
	{
		int number = rand() % 10;
		int symbol = rand() % 10;
		if (computer.hits[number][symbol] == 1) {
			e = 0;
		}
		else
		{
			if (human.tanks[number][symbol] == 1) {
				computer.hits[number][symbol] = 1;
				human.tanks[number][symbol] = 3;
				e = 1;
			}
			else
			{
				if (human.tanks[number][symbol] == 2) {
					computer.hits[number][symbol] = 1;
					human.tanks[number][symbol] = 4;
					continue;
				}
			}
		}
	}
	return 0;
}
/*�������� �����*/
int check_ending()
{
	bool k1 = 0, k2 = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (human.tanks[i][j] == 2) {
				k1 = 1;
			}
			if (computer.tanks[i][j] == 2) {
				k2 = 1;
			}
		}
	}
	if (k1 == 0) {
		human.defeat_flag = 1;
		return 2;
	}
	if (k2 == 0) {
		computer.defeat_flag = 1;
		return 2;
	}
	return 0;
}

/*���������� �������*/
void in_mass_net(void)
{
	int k = 1;
	space_input(0, 0, 4);
	symbols_str(0, 4);
	space_input(0, 24, 16);
	symbols_str(0, 40);
	space_input(0, 60, 1);
	for (char j = '0'; j < ':'; j++)
	{
		space_input(k, 0, 4);
		str_net(k, 4);
		space_input(k, 24, 16);
		str_net(k, 40);
		k++;
		space_input(k, 0, 2);
		num_str(j, k, 2);
		space_input(k, 24, 14);
		num_str(j, k, 38);
		k++;
	}
	space_input(k, 0, 4);
	str_net(k, 4);
	space_input(k, 24, 16);
	str_net(k, 40);
}

void str_net(int k, int y)
{
	for (int i = 0; i < 10; i++)
	{
		map[k][y + i] = '-';
		y++;
		map[k][y + i] = '-';
	}
	map[k][24] = '-';
	map[k][60] = '-';
}

void num_str(int j, int k, int y)
{
	map[k][y] = j;
	y++;
	map[k][y] = ' ';
	y++;
	/*for (int i = 0; i < 10; i++)
	{
		map[k][y + i] = '|';
		y++;
		map[k][y + i] = ' ';
	}*/
	map[k][24] = '|';
	map[k][60] = '|';
	map[k][4] = '|';
	map[k][40] = '|';
}

void symbols_str(int x, int y)
{
	char ch = 'A';
	for (int i = 0; i < 10; i++)
	{
		map[x][y] = ' ';
		y++;
		map[x][y] = ch;
		ch++;
		y++;
	}
}

void space_input(int x, int y, int n)
{
	for (int i = 0; i < n; i++)
	{
		map[x][y] = ' ';
		y++;
	}

}
int menu()
{
	int choise; 
	SetColor(LightGreen, Black);
	cout << endl;
	cout << "                                         �����                            " << endl;
	cout << "                 ---------------------------------------------------------" << endl;
	cout << "                 �� ���� �������� �����, ��� ����� �� ����� � ����������� " << endl;
	cout << "                 ---------------------------------------------------------" << endl;
	cout << "                 | �������� ������� ���������:                           |" << endl << endl;
	cout << "                 | 1. �������  (���������: 8 ������ ����� �  1 ���)      |" << endl << endl;
	cout << "                 | 2. �������� (���������: ����� 12 ������)              |" << endl << endl;
	cout << "                 | 3. �����    (���������: ����� 20 ������)              |" << endl<<endl;
	cout << "                 | 4. �����                                              |" << endl;
	cout << "                 ---------------------------------------------------------" << endl << endl;

	choise = menu_validation(4);
	return choise;
}
void menu_start() {
	cout << "" << endl;
	cout << "                                  ##  ##   ####  ##  ## ##  ## ###### ##   ##" << endl;
	cout << "                                  ##  ##  ##  ## ##  ## ##  ## ##     ### ###" << endl;
	cout << "                                  ######  ######  ##### ###### ####   ## # ##" << endl;
	cout << "                                  ##  ##  ##  ##     ## ##  ## ##     ##   ##" << endl;
	cout << "                                  ##  ##  ##  ##     ## ##  ## ###### ##   ##" << endl << endl;
	
}
void menu_win() {
	cout << "				#####  ##   ##" << endl;
	cout << "				##  ## ##   ##" << endl;
	cout << "				#####  #### ##" << endl;
	cout << "			    ##  ## ## # ##" << endl;
	cout << "				#####  #### ##" << endl;
	cout << "								 ##" << endl;
	cout << "				#####  ##   ## ##  ## ###### #####   ####     ### ##  ##" << endl;
	cout << "				##  ## ##   ## ##  ## ##     ##  ## ##  ##   # ## ##  ##" << endl;
	cout << "				#####  #### ## ## ### ##     ###### ######  #  ## ## ###" << endl;
	cout << "				##  ## ## # ## ### ## ##     ##     ##  ## ##  ## ### ##" << endl;
	cout << "				#####  #### ## ##  ## ##     ##     ##  ## ##  ## ##  ##" << endl;
}
void menu_not_win() {
	cout << "				#####  ##   ##" << endl;
	cout << "				##  ## ##   ##" << endl;
	cout << "				#####  #### ##" << endl;
	cout << "				##  ## ## # ##" << endl;
	cout << "				#####  #### ##" << endl;

	cout << "				###### #####   ####  ##  ## ###### #####   ####     ### ##  ##" << endl;
	cout << "				##  ## ##  ## ##  ## ##  ## ##     ##  ## ##  ##   # ## ##  ##" << endl;
	cout << "				##  ## ###### ##  ## ## ### ##     ###### ######  #  ## ## ###" << endl;
	cout << "				##  ## ##     ##  ## ### ## ##     ##     ##  ## ##  ## ### ##" << endl;
	cout << "				##  ## ##      ####  ##  ## ##     ##     ##  ## ##  ## ##  ##" << endl;
}
int menu_validation(int border)
{
	int a;
	while (true)
	{
		SetColor(LightGreen, Black);
		cout << "�������� ������� ����  : ";
		cin >> a;
		cout << endl;
		if (cin.get() == '\n') {
			if (a < 0 || a > border) {
				cin.clear();
				SetColor(Red, Black);
				cout << "���������� ������ �� 0 �� " << border << ". ���������� �����." << endl << endl;
				SetColor(Red, Black);

			}
			else break;
		}
		else {
			cin.clear();
			cin.ignore(256, '\n');
			SetColor(Red, Black);
			cout << "������. ���������� ��� ���!" << endl << endl;
			SetColor(LightGreen, Black);
		}
	}
	return a;
}