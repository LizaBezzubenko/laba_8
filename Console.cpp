#include "Console.h"

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

bool CheckLetter(string text)
{
	for (int n = 0; n != text.length(); n++)
	{
		switch (text[n])
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
			break;
		default:
			return false;
		}
	}
	return true;
}