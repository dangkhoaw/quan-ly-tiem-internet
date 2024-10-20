#ifndef STAFF
#define STAFF 1

#include "customer.h"
#include <vector>
#include "computer.h"
#include "mtime.h"
#include "revenue.h"

using namespace std;

class Staff : public Account
{
public:
    Staff(string username = "", string password = "", string role = "", string id = "", string status = "", string isFirstLogin = "", string isLocked = "");

    void viewComputerStatus();
    void topUpAccount();
    void viewCustomerInfo();
    void addComputer();
    void viewRevenue();
    void lockAccount();
    void addAccount();
    void removeComputer();
    void viewListCustomer();
};

#endif