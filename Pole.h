#pragma once
const int s = 22, c = 61;
char map[s][c];
char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char symbols[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

void in_mass_net(void);
void str_net(int k, int y);
void num_str(int j, int k, int y);
void symbols_str(int x, int y);
void space_input(int x, int y, int n);

void map_init(); 
void show(); 
int input(int&, int&);
bool turn(int symbol, int number); 
bool turn(); 
int check_ending();

int menu();
void menu_start();
void menu_win();
void menu_not_win();
int menu_validation(int border);
