#pragma once
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <fstream>
#include <functional>
#include <Windows.h>
#include <conio.h>

using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightLightGreen = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

bool CheckLetter(string text);
void SetColor(ConsoleColor text, ConsoleColor background);