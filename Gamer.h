#pragma once
#include "Pole.h"
enum direction { X, Y };
class Gamer
{
public:
	bool defeat_flag;
	int hits[10][10];
	int tanks[10][10];
	Gamer()
	{
		defeat_flag = 0;
	}

	void tanks_init_first();
	void tanks_init_second();
	void tanks_init(); 
	void set(int field); 
	int place_tank(int x, int y, direction dir, int field); 
};

Gamer human;
Gamer computer;


void Gamer::tanks_init()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			tanks[i][j] = 1;
			hits[i][j] = 0;
		}

	set(4); set(3); set(3); set(2); set(2); set(2); set(1); set(1); set(1); set(1);
}

void Gamer::tanks_init_first()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			tanks[i][j] = 1;
			hits[i][j] = 0;
		}

	set(8);
}

void Gamer::tanks_init_second() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			tanks[i][j] = 1;
			hits[i][j] = 0;
		}

	set(5); set(4); set(3);
}

void Gamer::set(int field)
{
	int my = field - 1;
	bool coor, isset = 0;
	direction dir;
	int x, y, res;
	while (isset == 0)
	{
		coor = 0;
		res = rand() % 2;
		if (res == 0) {
			dir = X;
		}
		else {
			dir = Y;
		}
		while (coor == 0)
		{
			x = rand() % 10;
			y = rand() % 10;
			if (tanks[x][y] == 1) {
				coor = 1;
			}
		}
		int e = 0;
		switch (dir)
		{
		case X:
			if (tanks[x][y + my] == 1)
			{
				if ((y + my) >= 10) break;
				e = place_tank(x, y, dir, field); 
				if (e == 0)
				{
					for (int i = 0; i < field; i++)
						tanks[x][y + i] = 2;
					isset = 1;
				}
			}
			break;

		case Y:
			if (tanks[x + my][y] == 1)
			{
				e = place_tank(x, y, dir, field);
				if (e == 0)
				{
					for (int i = 0; i < field; i++)
						tanks[x + i][y] = 2;
					isset = 1;
				}
			}
			break;
		}
	}
}

int Gamer::place_tank(int x, int y, direction dir, int field)
{
	bool res = 0;
	switch (dir)
	{
	case X: 
		if (y == 0)
			if (x == 0)
			{
				for (int i = 0; i <= field; i++)
					if (tanks[x + 1][y + i] != 1) {
						res = 1;
						break;
					}
				if (tanks[x][y + field] != 1) {
					res = 1;
				}
				break;
			}
			else if (x == 9)
			{
				for (int i = 0; i <= field; i++)
					if (tanks[x - 1][y + i] != 1) {
						res = 1;
						break;
					}
				if (tanks[x][y + field] != 1) {
					res = 1;
				}
				break;
			}
			else
			{
				for (int i = 0; i <= field; i++)
				{
					if (tanks[x + 1][y + i] != 1) {
						res = 1;
						break;
					}
					if (tanks[x - 1][y + i] != 1) {
						res = 1;
						break;
					}
				}
				if (tanks[x][y + field] != 1) {
					res = 1;
				}
				break;
			}
		else if (y == (10 - field))
			if (x == 0)
			{
				for (int i = -1; i < field; i++)
					if (tanks[x + 1][y + i] != 1) {
						res = 1;
						break;
					}
				if (tanks[x][y - 1] != 1) {
					res = 1;
				}
				break;
			}
			else if (x == 9)
			{
				for (int i = -1; i < field; i++)
					if (tanks[x - 1][y + i] != 1) {
						res = 1;
						break;
					}
				if (tanks[x][y - 1] != 1) {
					res = 1;
				}
				break;
			}
			else
			{
				for (int i = -1; i < field; i++)
				{
					if (tanks[x + 1][y + i] != 1) {
						res = 1;
						break;
					}
					if (tanks[x - 1][y + i] != 1) {
						res = 1;
						break;
					}

				}
				if (tanks[x][y - 1] != 1) {
					res = 1;
				}
				break;
			}
		else
			if (x == 0)
			{
				for (int i = -1; i <= field; i++)
					if (tanks[x + 1][y + i] != 1) {
						res = 1;
						break;
					}
				if (tanks[x][y - 1] != 1) {
					res = 1;
					break;
				}
				if (tanks[x][y + field] != 1) {
					res = 1;
				}
				break;
			}
			else if (x == 9)
			{
				for (int i = -1; i <= field; i++)
					if (tanks[x - 1][y + i] != 1) {
						res = 1;
						break;
					}
				if (tanks[x][y - 1] != 1) {
					res = 1;
					break;
				}
				if (tanks[x][y + field] != 1) {
					res = 1;
				}
				break;
			}
			else
			{
				for (int i = -1; i <= field; i++)
				{
					if (tanks[x + 1][y + i] != 1) {
						res = 1;
						break;
					}
					if (tanks[x - 1][y + i] != 1) {
						res = 1;
						break;
					}
				}
				if (tanks[x][y - 1] != 1) {
					res = 1;
					break;
				}
				if (tanks[x][y + field] != 1) {
					res = 1;
				}
				break;
			}

	case Y:
		if (x == 0)
			if (y == 0)
			{
				for (int i = 0; i <= field; i++)
					if (tanks[x + i][y + 1] != 1) {
						res = 1;
						break;
					}
				if (tanks[x + field][y] != 1) {
					res = 1;
				}
				break;
			}
			else if (y == 9)
			{
				for (int i = 0; i <= field; i++)
					if (tanks[x + i][y - 1] != 1) {
						res = 1;
						break;
					}
				if (tanks[x + field][y] != 1) {
					res = 1;
				}
				break;
			}
			else
			{
				for (int i = 0; i <= field; i++)
				{
					if (tanks[x + i][y + 1] != 1) {
						res = 1;
						break;
					}
					if (tanks[x + i][y - 1] != 1) {
						res = 1;
						break;
					}
				}
				if (tanks[x + field][y] != 1) {
					res = 1;
				}
				break;
			}
		else if (x == (10 - field))
			if (y == 0)
			{
				for (int i = -1; i < field; i++)
					if (tanks[x + i][y + 1] != 1) {
						res = 1;
						break;
					}
				if (tanks[x - 1][y] != 1) {
					res = 1;
				}
				break;
			}
			else if (y == 9)
			{
				for (int i = -1; i < field; i++)
					if (tanks[x + i][y - 1] != 1) {
						res = 1;
						break;
					}
				if (tanks[x - 1][y] != 1) {
					res = 1;
				}
				break;
			}
			else
			{
				for (int i = -1; i < field; i++)
				{
					if (tanks[x + i][y + 1] != 1) {
						res = 1;
						break;
					}
					if (tanks[x + i][y - 1] != 1) {
						res = 1;
						break;
					}
				}
				if (tanks[x - 1][y] != 1) {
					res = 1;
				}
				break;
			}
		else
			if (y == 0)
			{
				for (int i = -1; i <= field; i++)
					if (tanks[x + i][y + 1] != 1) {
						res = 1;
						break;
					}
				if (tanks[x - 1][y] != 1) {
					res = 1;
					break;
				}
				if (tanks[x + field][y] != 1) {
					res = 1;
				}
				break;
			}
			else if (y == 9)
			{
				for (int i = -1; i <= field; i++)
					if (tanks[x + i][y - 1] != 1) {
						res = 1;
						break;
					}
				if (tanks[x - 1][y] != 1) {
					res = 1;
					break;
				}
				if (tanks[x + field][y] != 1) {
					res = 1;
				}
				break;
			}
			else
			{
				for (int i = -1; i <= field; i++)
				{
					if (tanks[x + i][y + 1] != 1) {
						res = 1;
						break;
					}
					if (tanks[x + i][y - 1] != 1) {
						res = 1;
						break;
					}
				}
				if (tanks[x - 1][y] != 1) {
					res = 1;
					break;
				}
				if (tanks[x + field][y] != 1) {
					res = 1;
				}
				break;
			}
	}
	return res;
}