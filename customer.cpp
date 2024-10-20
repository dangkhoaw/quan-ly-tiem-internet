#include "customer.h"
#include "base64.h"
#include "function.h"
// #include <mutex>

// mutex cus;

Customer::Customer(string username, string password, string role, string id, string status, string isFirstLogin, string isLocked, string name, string phone, float balance, Time time, int moneyforOrder)
    : Account(username, password, role, id, status, isFirstLogin, isLocked), name(name), phone(phone), balance(balance), time(time), moneyforOrder(moneyforOrder) {}
Customer::~Customer() {}

string Customer::getName() { return name; }
string Customer::getPhone() { return phone; }
Time Customer::getTime() { return time; }
float Customer::getBalance() { return balance; }
int Customer::getMoneyforOrder() { return moneyforOrder; }
string Customer::getCurrentComputerID() { return currentComputerID; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(string phone) { this->phone = phone; }
void Customer::setName(string name) { this->name = name; }
void Customer::setmoneyforOrder(int moneyforOrder) { this->moneyforOrder = moneyforOrder; }
void Customer::setBalance(float balance) { this->balance = balance; }
void Customer::setBalance(Time time)
{
    float cost = 10000;
    this->balance = (float(time.getHour()) + float(time.getMinute()) / 60 + float(time.getSecond()) / 3600) * cost;
}
void Customer::setCurrentComputerID(string id) { currentComputerID = id; }

Time Customer::getTimeFromFile()
{
    // lock_guard<mutex> lock(cus);
    Time time;
    fstream file("./time/" + getId() + ".txt", ios::in);
    if (file.is_open())
    {
        file >> time;
        file.close();
    }
    else
    {
        cout << "Không thể mở file t/g customer" << endl;
    }
    return time;
}

void Customer::setTimeToFile(Time time)
{
    // lock_guard<mutex> lock(cus);
    fstream file("./time/" + getId() + ".txt", ios::out);
    if (file.is_open())
    {
        file << time;
        file.close();
    }
}

void Customer::showMyInfo()
{
    system("cls");
    setBalance(getTimeFromFile());
    updateCustomerToFile(*this);
    cout << "Tên khách hàng: " << name << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Số dư: " << formatMoney(balance) << " (VNĐ)" << endl;
    pressKeyQ();
}

bool Customer::isLocked()
{
    // lock_guard<mutex> lock(cus);
    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        // cout << "Không thể mở file account trong isLocked ở file customer.cpp" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, username, password, role, status, isFirstLogin, isLocked;
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, role, '|');
        getline(ss, status, '|');
        getline(ss, isFirstLogin, '|');
        getline(ss, isLocked);

        if (username == this->username)
        {
            if (isLocked == "Locked")
            {
                file.close();
                return true;
            }
            else
            {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return false;
}

bool getCustomerFromFile(Customer &customer)
{
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    string line;
    Customer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        string balance;
        getline(ss, temp.id, '|');
        getline(ss, temp.name, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.phone, '|');
        getline(ss, balance, '|');
        temp.balance = stof(balance);
        getline(ss, temp.currentComputerID);

        if (temp.username == customer.username)
        {
            customer.id = temp.id;
            customer.name = temp.name;
            customer.phone = temp.phone;
            customer.balance = temp.balance;
            customer.currentComputerID = temp.currentComputerID;
            file.close();
            customer.time = customer.getTimeFromFile();
            return true;
        }
    }
    file.close();
    return false;
}

void updateCustomerToFile(Customer &customer)
{
    // lock_guard<mutex> lock(cus);
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    Customer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        string balance;
        getline(ss, temp.id, '|');
        getline(ss, temp.name, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.phone, '|');
        getline(ss, balance, '|');
        temp.balance = stof(balance);
        getline(ss, temp.currentComputerID);

        if (temp.id == customer.id)
        {
            temp = customer;
        }
        tempFile << temp.id << "|" << temp.name << "|" << temp.username << "|" << temp.phone << "|" << temp.balance << "|" << temp.currentComputerID << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\data\\customer.txt");
    system("ren .\\data\\temp.txt customer.txt");
}

istream &operator>>(istream &is, Customer &customer)
{
    is.ignore();
    cout << "Tên khách hàng: ";
    getline(is, customer.name);
    cout << "Số điện thoại: ";
    is >> customer.phone;
    is.ignore();
    while (true)
    {
        cout << "Tên đăng nhập: ";
        getline(is, customer.username);
        if (!isValidUsername(customer.username))
            cout << "Tên đăng nhập đã tồn tại" << endl;
        else
            break;
    }

    customer.password = "123456";
    cout << "Mật khẩu: 123456" << endl;
    customer.role = "customer";
    generateID(customer);
    return is;
}
int Customer::inPutAmountOrder()
{
    system("cls");
    ShowCursor(true);
    int amount;
    do
    {
        cout << "Nhập số lượng: ";
        cin >> amount;
        if (amount <= 0)
        {
            cout << "Số lượng không hợp lệ" << endl;
        }
    } while (amount <= 0);
    return amount;
}
void Customer::order(string nameRefreshment, int quantity, bool isOrder_again)
{
    system("cls");
    ShowCursor(true);
    int price = getPriceOfRefreshment(nameRefreshment, quantity);
    string name;
    int quantity_infile, price_infile;
    if (isOrder_again)
    {
        fstream file("./data/" + getId() + "_ordered.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, line, '|');
            quantity_infile = stoi(line);
            getline(ss, line, '|');
            price_infile = stoi(line);
            if (name == nameRefreshment)
            {
                break;
            }
        }
        if (quantity_infile > quantity)
        {
            this->setmoneyforOrder(this->getMoneyforOrder() - (price_infile - price));
        }
        else if (quantity_infile < quantity)
        {
            this->setmoneyforOrder(this->getMoneyforOrder() + (price - price_infile));
        }
        else
        {
            return;
        }
        file.close();
    }
    else
    {
        this->moneyforOrder += price;
    }
    if (this->balance < this->moneyforOrder)
    {
        if (isOrder_again)
        {
            if (quantity_infile < quantity)
                this->setmoneyforOrder(this->getMoneyforOrder() - (price - price_infile));
        }
        else
        {
            this->moneyforOrder -= price;
        }
        system("cls");
        cout << "Số dư không đủ" << endl;
        pressKeyQ();
        return;
    }
    setOrderedToFile(*this, nameRefreshment, quantity, price);
    cout << "Đã thêm món" << endl;
    pressKeyQ();
}

void Customer::order()
{
    system("cls");
    ShowCursor(false);
    this->balance -= getTotalPrice();
    this->moneyforOrder = 0;
    updateCustomerToFile(*this);
    system(("del .\\data\\" + getId() + "_ordered.txt").c_str());
    cout << " Đang chuẩn bị, vui lòng chờ trong giây lát..!" << endl;
    Sleep(3000);
    return;
}
int Customer::getTotalPrice()
{
    fstream file("./data/" + (*this).getId() + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return 0;
    }
    string line;
    int total = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name;
        int quantity;
        int price;
        getline(ss, name, '|');
        getline(ss, line, '|');
        quantity = stoi(line);
        ss >> price;
        total += quantity * price;
    }
    return total;
}
int Customer::getPriceOfRefreshment(string nameRefreshment, int quantity)
{
    int price = 0;
    if (nameRefreshment == "Bánh mì thịt nướng")
        price = 15000 * quantity;
    else if (nameRefreshment == "Mì tôm trứng")
        price = 15000 * quantity;
    else if (nameRefreshment == "Cơm gà nướng")
        price = 25000 * quantity;
    else if (nameRefreshment == "Cơm gà chiên nước mắm")
        price = 25000 * quantity;
    else if (nameRefreshment == "Xúc xích")
        price = 10000 * quantity;
    else if (nameRefreshment == "Cơm cuộn")
        price = 15000 * quantity;
    else if (nameRefreshment == "Nước suối")
        price = 5000 * quantity;
    else if (nameRefreshment == "Nước cam")
        price = 10000 * quantity;
    else if (nameRefreshment == "Bò húc")
        price = 15000 * quantity;
    else if (nameRefreshment == "Caffee sữa")
        price = 15000 * quantity;
    else if (nameRefreshment == "Caffee đen")
        price = 10000 * quantity;
    else if (nameRefreshment == "Coca lon")
        price = 10000 * quantity;
    return price;
}
