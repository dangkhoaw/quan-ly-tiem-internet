#ifndef STAFF
#define STAFF 1

#include "account.hpp"
#include "customer.hpp"

class Staff : public Account
{
public:
    Staff(std::string username = "", std::string password = "", std::string role = "", std::string id = "", std::string status = "", std::string isFirstLogin = "");

    void viewComputerStatus();
    void topUpAccount();
    void viewCustomersInfo();
    void addComputer();
    void viewRevenue();
    void addAccount();
    void removeAccount();
    void removeComputer();
    void viewListCustomer();
    void searchCustomer();
    void registerComputerForCus();
    void viewTypeOfComputer(bool isRegister = false);
};

#endif