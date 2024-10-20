// #include "staff.h"
#include "function.h"
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

Staff::Staff(string username, string password, string role, string id, string status, string isFirstLogin, string isLocked) : Account(username, password, role, id, status, isFirstLogin, isLocked) {}

void Staff::addAccount()
{
    system("cls");
    ShowCursor(true);
    Customer customer;
    cin >> customer;
    addCustomerToFile(customer);
    addNewAccountToFile(customer);
    MessageBoxW(NULL, L"Thêm tài khoản thành công", L"Thông báo", MB_OK);
    system("cls");
    ShowCursor(false);
}

void Staff::addComputer()
{
    system("cls");
    ShowCursor(true);
    int amountOfComputer;
    cout << "Nhập số lượng máy tính cần thêm: ";
    cin >> amountOfComputer;
    cin.ignore();

    for (int i = 0; i < amountOfComputer; i++)
    {
        Computer computer;
        generateIDComputer(computer);
        addNewComputerToFile(computer);
    }
    MessageBoxW(NULL, L"Thêm máy tính thành công", L"Thông báo", MB_OK);
    system("cls");
    ShowCursor(false);
}
void Staff::removeComputer()
{
    system("cls");
    ShowCursor(true);
    string idComputer;
    cout << "Nhập id máy cần xóa: ";
    cin >> idComputer;
    toUpper(idComputer);
    Computer computer;
    computer.setId(idComputer);
    removeComputerFromFile(computer);
    ShowCursor(false);
    system("cls");
}
void Staff::viewComputerStatus()
{
    /*
      ┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐
      │   MÁY    │    TRẠNG THÁI      │      KHÁCH HÀNG          │   THỜI GIAN SỬ DỤNG  │
      ├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤
      │  COM01   │    Đang sử dụng    │      dangkhoaw           │       00:30:00       │
      │  COM02   │      Trống         │         -                │          -           │
      │  COM03   │      Trống         │         -                │          -           │
      │  COM04   │      Trống         │      grayzy              │          -           │
      └──────────┴────────────────────┴──────────────────────────┴──────────────────────┘
    */
    system("cls");
    vector<Computer> prevComputers;
    Gotoxy(0, 0);
    cout << "┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐" << endl;
    Gotoxy(0, 1);
    cout << "│   MÁY    │     TRẠNG THÁI     │        KHÁCH HÀNG        │   THỜI GIAN SỬ DỤNG  │" << endl;
    Gotoxy(0, 2);
    cout << "├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤" << endl;
    while (true)
    {
        vector<Computer> computers = getComputers();

        for (int i = 0; i < computers.size(); i++)
        {
            if (prevComputers.empty() || prevComputers[i].getUsageTime() != computers[i].getUsageTime())
            {
                ClearLine(i + 3);
                Gotoxy(0, i + 3);
                cout << "│  " << computers[i].getId() << "   ";
                Gotoxy(11, i + 3);
                (computers[i].getStatus() == "Using") ? cout << "│    Đang sử dụng" : cout << "│       Trống";

                if (computers[i].getCustomerUsingName() == "")
                {
                    Gotoxy(32, i + 3);
                    cout << "│             -";
                }
                else
                {
                    Gotoxy(32, i + 3);
                    cout << "│        " << computers[i].getCustomerUsingName();
                }
                if (computers[i].getUsageTime().isZero())
                {
                    Gotoxy(59, i + 3);
                    cout << "│           -";
                }
                else
                {
                    Gotoxy(59, i + 3);
                    cout << "│       " << computers[i].getUsageTime();
                }
                Gotoxy(82, i + 3);
                cout << "│";
            }
        }
        prevComputers = computers;
        Gotoxy(0, computers.size() + 3);
        cout << "└──────────┴────────────────────┴──────────────────────────┴──────────────────────┘" << endl;
        Gotoxy(0, computers.size() + 5);
        cout << "(Nhấn phím q để thoát)";
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q')
            {
                break;
            }
            else
            {
                continue;
            }
        }
        Sleep(1000);
    }
    system("cls");
}

void Staff::topUpAccount()
{
    system("cls");
    ShowCursor(true);
    string userName;
    Customer customer;
    Date currentDate = Date().getCurrentDate();
    Revenue revenue = Revenue().getDoanhThuByDate(currentDate);
    revenue.setDate(currentDate);
    int count = 0;

    while (true)
    {
        ClearLine(3);
        ClearLine(4);

        Gotoxy(0, 3);

        cout << "(Nhập sai 3 lần sẽ thoát: " << count << " lần nhập sai)";

        ClearLine(0);
        Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        cin >> userName;

        if (isValidUsername(userName))
        {
            if (++count == 4)
            {
                system("cls");
                cout << "Nhập sai 3 lần. Hãy thử lại sau" << endl;
                pressKeyQ();
                ShowCursor(false);
                return;
            }
        }
        else
        {
            ClearLine(3);
            ClearLine(4);
            break;
        }
    }
    float amount;
    do
    {
        Gotoxy(0, 1);
        cout << "Nhập số tiền cần nạp (10k/h): ";
        cin >> amount;

        if (amount < 1000)
        {
            MessageBoxW(NULL, L"Số tiền được nhập phải là số nguyên dương và lớn hơn 1000", L"Thông báo", MB_ICONWARNING);
        }
    } while (amount < 1000);
    cin.ignore();
    revenue = revenue + amount;
    revenue.updateDoanhThu(revenue);

    customer.setUserName(userName);
    getCustomerFromFile(customer);

    float minutes = (amount * 60) / 10000;
    Time time(0, minutes, 0);
    customer.setTimeToFile(time + customer.getTime());
    customer.setBalance(customer.getBalance() + amount);

    updateCustomerToFile(customer);

    cout << "\nNạp tiền thành công" << endl;

    pressKeyQ();

    ShowCursor(false);
}

void Staff::lockAccount()
{
    system("cls");
    ShowCursor(true);
    string userName;
    Account account;
    int count = 0;

    while (true)
    {
        ClearLine(3);
        ClearLine(4);

        Gotoxy(0, 3);

        cout << "(Nhập sai 3 lần sẽ thoát: " << count << " lần nhập sai)";

        ClearLine(0);
        Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        cin >> userName;

        if (isValidUsername(userName))
        {
            if (++count == 4)
            {
                system("cls");
                cout << "Nhập sai 3 lần. Hãy thử lại sau" << endl;
                pressKeyQ();
                ShowCursor(false);
                return;
            }
        }
        else
        {
            ClearLine(3);
            ClearLine(4);
            break;
        }
    }

    account.setUserName(userName);
    getAccountFromFile(account);

    if (account.getIsLocked() == "Locked")
    {
        cout << "Tài khoản đã bị khóa" << endl;
        pressKeyQ();
        ShowCursor(false);
        return;
    }

    account.setLocked("Locked");
    updateAccountToFile(account);

    cout << "Khóa tài khoản thành công" << endl;
    pressKeyQ();
    ShowCursor(false);
}
