#ifndef FUNCTION
#define FUNCTION 1

#include <thread>
#include <vector>
#include "mtime.h"
#include "staff.h"
#include "account.h"
#include "revenue.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

using namespace std;
/*------------------------------------CONSOLE------------------------------------*/
void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);
void ClearLine(SHORT posY);
void ClearLine(SHORT posX, SHORT posY, SHORT length);
/*------------------------------------MENU------------------------------------*/
void printMenuOption(string typeMenu, int option, bool isSelected);
void showMenu(string typeMenu, int selectOption);
void optionMenu(string typeMenu, int option);
void computerManagementMenu(Staff &staff);
void customerManagementMenu(Staff &staff);
void menuStaff(Staff &staff);
void menuCustomer(Customer &customer, Computer &computer);
void menuRevenue(Staff &staff);
void menuRevenueMonth(Staff &staff);
void menuRevenueYear(Staff &staff);
void menuRevenueDay(Staff &staff);
void menuDish(Customer &customer);
void menuFood(Customer &customer);
void menuQuantity(Customer &customer, string nameFood);
void menuDrink(Customer &customer);
void menuGame();
void setOrderedToFile(Customer &customer, string name, int quantity, int price);
void printItemsOrdered(Customer &customer);
/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer);
void showUsageTimeOfComputer(Computer *computer);
/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool addNewAccountToFile(Account &account);
bool isValidUsername(string &username);
/*------------------------------------CUSTOMER------------------------------------*/
bool addCustomerToFile(Customer &customer);
void generateID(Account &account);
bool checkFirstLogin(Account &account);
bool checkIsOrdered(Customer &customer, string nameFood);
void makeFileOrdered(Customer &customer);

/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers();
void updateNumberOfComputers(int &count);
bool addNewComputerToFile(Computer &computer);
void generateIDComputer(Computer &computer);
vector<Computer> getComputersByStatus(string status);
vector<Computer> getComputers();
void assignRandomComputer(Customer &customer, Computer &computer);
void removeComputerFromFile(Computer &computer);
/*------------------------------------DISH------------------------------------*/
// void generateID(Dish &dish);
/*------------------------------------OTHER------------------------------------*/
void enterPassword(string &password);
string formatMoney(float money);
void pressKeyQ();
void toUpper(string &str);
void toLower(string &str);
bool isNumber(const string &str);
bool isString(const string &str);
bool isPhoneNumber(const string &str);
bool isExistPhoneNumber(const string &str);
void inputMonthAndYear(int &month, int &year);
void inputYear(int &year);
string trim(string &str);
string removeSpecialCharacter(string &str);
string toName(string &str);
bool isFileEmpty(const string &filename);

#endif