#ifndef _FUNCTION_H
#define _FUNCTION_H 1

#include <iostream>
#include <windows.h>
#include "menu.h"
using namespace std;

void printMenuOption(string typeMenu, int option, bool isSelected);
void showMenu(string typeMenu, int selectOption);
void optionMenu(string typeMenu, int option);
void admin();
void user();

#endif