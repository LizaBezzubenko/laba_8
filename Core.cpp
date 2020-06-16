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
	in_mass_net();//заполняем массив поля
	int message = 0; // переменная хранит коды сообщений (0 - всё ок; 1 - неверная клавиша; 2 - игра закончилась)

	srand(static_cast<unsigned int>(time(NULL)));

	int choise;
	switch (menu())
	{
	case 1:
		human.tanks_init();//помещаем танки в наше поле
		computer.tanks_init_first();//помещаем танки в поле компьютера
		break;
	case 2:
		human.tanks_init();//помещаем танки в наше поле
		computer.tanks_init_second();//помещаем танки в поле компьютера
		break;
	case 3:
		human.tanks_init();//помещаем танки в наше поле
		computer.tanks_init();//помещаем танки в поле компьютера
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
		map_init();//помещаем в массив информацию о танках игрока
		show();
		if (message == 1) {// код сообщения 1 - введено неверное значение
			SetColor(Red, Black);
			cout << "Вы ввели неверное значение!\n";
		}
		SetColor(LightGreen, Black);
		message = 0;
		int symbol, number;

		user_input = input(symbol, number);//ввод координат x и y пользователем 
		if (user_input == 1)
		{
			message = 1;
			continue;
		}

		e = turn(symbol, number);//ход пользователя
		if (e == 1) { continue; }
		e = turn();//ход компьютера
		message = check_ending();//проверка конца
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


/*Помещение в массив map информации о танках игрока*/
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

/*Ввод координат пользователя*/
int input(int& symbol, int& number)
{
	symbol = -1, number = -1;
	int massage = 0;
	char ch, d;//буква/цифра
	SetColor(Yellow, Black);
	cout << "Стреляйте!\n";
	cout << "Введите букву от A до J:";
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
	cout << "Введите цифру от 0 до 9:";
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
/*Вывод поля*/
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

/*Ходы пользователя*/
bool turn(int symbol, int number)
{
	bool e = 0;
	if ((human.hits[number][symbol] == 1) || (human.hits[number][symbol] == 2))
	{
		cout << " Вы сюда уже стреляли! Попробуйте еще раз...";
		e = 1;
		_getch();
	}
	else
	{
		if (computer.tanks[number][symbol] == 1)
		{
			human.hits[number][symbol] = 1;
			SetColor(Red, Black);
			cout << "Промах!!!";
			SetColor(LightGreen, Black);
			_getch();
		}
		else if (computer.tanks[number][symbol] == 2)
		{
			human.hits[number][symbol] = 2;
			computer.tanks[number][symbol] = 3;
			SetColor(Yellow, Black);
			cout << "Ура, Вы задели противника!!!" << endl;
			cout << "Можете ходить ещё раз ";
			SetColor(LightGreen, Black);
			e = 1;
			_getch();
		}
	}
	return e;
}
/*Ходы компьютера*/
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
/*Проверка конца*/
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

/*Заполнение массива*/
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
	cout << "                                         ТАНКИ                            " << endl;
	cout << "                 ---------------------------------------------------------" << endl;
	cout << "                 На поле спрятаны танки, Вам нужно их найти и обезвредить " << endl;
	cout << "                 ---------------------------------------------------------" << endl;
	cout << "                 | Выберите уровень сложности:                           |" << endl << endl;
	cout << "                 | 1. Новичок  (подсказка: 8 танков стоят в  1 ряд)      |" << endl << endl;
	cout << "                 | 2. Любитель (подсказка: всего 12 танков)              |" << endl << endl;
	cout << "                 | 3. Профи    (подсказка: всего 20 танков)              |" << endl<<endl;
	cout << "                 | 4. Выход                                              |" << endl;
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
		cout << "Выберите уровень игры  : ";
		cin >> a;
		cout << endl;
		if (cin.get() == '\n') {
			if (a < 0 || a > border) {
				cin.clear();
				SetColor(Red, Black);
				cout << "Необходимо ввести от 0 до " << border << ". Попробуйте снова." << endl << endl;
				SetColor(Red, Black);

			}
			else break;
		}
		else {
			cin.clear();
			cin.ignore(256, '\n');
			SetColor(Red, Black);
			cout << "Ошибка. Попробуйте еще раз!" << endl << endl;
			SetColor(LightGreen, Black);
		}
	}
	return a;
}