#ifndef FUNCTION
#define FUNCTION 1

#include <windows.h>
#include "list.h"
#include "mtime.h"
#include "staff.h"
#include "account.h"
#include "customer.h"
#include "computer.h"

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
void printMenuOption(string typeMenu, int option, bool isSelected, List<Computer> computers = List<Computer>());
void showMenu(string typeMenu, int selectOption, string typeComputer = "");
void optionMenu(string typeMenu, int option, List<Computer> computers = List<Computer>());
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
string menuSelectTypeOfComputer();
string menuSelectComputer(string typeOfComputer);
void printItemsOrdered(Customer &customer);
/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer);
void showUsageTimeOfComputer(Computer *computer);
/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool addNewAccountToFile(Account &account);
bool removeAccountFromFile(string id_account);
bool isExistUsername(string &username);
/*------------------------------------CUSTOMER------------------------------------*/
bool addCustomerToFile(Customer &customer);
bool removeCustomerFromFile(string id_customer);
void generateID(Account &account);
bool checkFirstLogin(Account &account);
bool checkIsOrdered(Customer &customer, string nameFood);
void makeFileOrdered(Customer &customer);
string getTypesOfComputerFromFile(string idComputer);
List<Customer> getCustomers();

/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers();
bool addNewComputerToFile(Computer &computer); // setnewcomputer cho hay , tự dưng get rồi mà sài add
void updateCountOfComputerToFile(string typeOfComputer, int count = 1);
void generateIDComputer(Computer &computer);
List<Computer> getComputersByStatus(string status);
List<Computer> getAllComputers();
List<Computer> getComputers(string typeOfComputer = "all", string status = "all");
void assignRandomComputer(Customer &customer, Computer &computer);
void removeComputerFromFile(Computer &computer);
string getIdComputerFromFile(string username);
bool isFullAllComputer();
bool isStatusAdmin();
/*------------------------------------DISH------------------------------------*/
// void generateID(Dish &dish);
/*------------------------------------OTHER------------------------------------*/
bool isRegisterComputer(string username);
void enterPassword(string &password);
string formatMoney(double money);
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
void enterString(string &str, int length = 0);
void enterLetter(string &str, int length = 0);
void enterNumber(string &num, int length = 0);
void enterMoney(string &num, int length = 0);

#endif