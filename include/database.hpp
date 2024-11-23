#ifndef DATABASE
#define DATABASE 1

#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include "account.hpp"
#include "customer.hpp"
#include "computer.hpp"
#include "list.hpp"
#include "base64.hpp"
#include "process.hpp"

using namespace std;

template <class T>
class Database
{
private:
    static bool openFile(fstream &file, string path, ios_base::openmode mode);
    static bool closeFile(fstream &file);
    static bool writeToFile(fstream &file, T &obj);

public:
    static bool add(T &obj);
    static bool remove(T &obj);
    static bool update(T &obj);
    static bool get(T &obj);
    static List<T> gets(string field = "", string value = "");
};

template <class T>
bool Database<T>::openFile(fstream &file, string path, ios_base::openmode mode)
{
    file.open(path, mode);
    if (!file.is_open())
    {
        return false;
    }
    return true;
}

template <class T>
bool Database<T>::closeFile(fstream &file)
{
    file.close();
    if (file.is_open())
    {
        return false;
    }
    return true;
}

template <class T>
bool Database<T>::writeToFile(fstream &file, T &obj)
{
    file << obj << endl;
    return file.good();
}

template <class T>
bool Database<T>::add(T &obj)
{
    if constexpr (is_same<T, Account>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/account/account.txt", ios::app))
                throw "Không thể mở file account";

            if (!writeToFile(file, obj))
                throw "Không thể ghi vào file account";

            closeFile(file);
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Customer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/customer/customer.txt", ios::app))
                throw "Không thể mở file customer";

            if (!writeToFile(file, obj))
                throw "Không thể ghi vào file customer";

            closeFile(file);

            if (!openFile(file, "./data/time/" + obj.getId() + ".txt", ios::out))
                throw "Không thể tạo file t/g customer";

            file << obj.getTime();
            closeFile(file);
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Computer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/computer/computer.txt", ios::app))
                throw "Không thể mở file computer";

            if (!writeToFile(file, obj))
                throw "Không thể ghi vào file computer";

            closeFile(file);

            if (!openFile(file, "./data/time/" + obj.getId() + ".txt", ios::out))
                throw "Không thể tạo file t/g computer";

            file << obj.getUsageTime();
            closeFile(file);
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
}

template <class T>
bool Database<T>::remove(T &obj)
{
    if constexpr (is_same<T, Account>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/account/account.txt", ios::in))
                throw "Không thể mở file account";

            fstream tempFile;
            if (!openFile(tempFile, "./data/account/temp.txt", ios::out))
                throw "Không thể mở file temp";

            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string id;
                getline(ss, id, '|');
                if (id != obj.getId())
                    tempFile << line << endl;
            }

            closeFile(file);
            closeFile(tempFile);
            std::remove("./data/account/account.txt");
            std::rename("./data/account/temp.txt", "./data/account/account.txt");
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Customer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/customer/customer.txt", ios::in))
                throw "Không thể mở file customer";

            fstream tempFile;
            if (!openFile(tempFile, "./data/customer/temp.txt", ios::out))
                throw "Không thể mở file temp";

            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string id;
                getline(ss, id, '|');
                if (id != obj.getId())
                    tempFile << line << endl;
            }

            Database<Account>::remove(obj);

            closeFile(file);
            closeFile(tempFile);
            std::remove("./data/customer/customer.txt");
            std::rename("./data/customer/temp.txt", "./data/customer/customer.txt");
            std::remove(("./data/time/" + obj.getId() + ".txt").c_str());
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Computer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/computer/computer.txt", ios::in))
                throw "Không thể mở file computer";

            fstream tempFile;
            if (!openFile(tempFile, "./data/computer/temp.txt", ios::out))
                throw "Không thể mở file temp";

            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string id;
                getline(ss, id, '|');
                if (id != obj.getId())
                    tempFile << line << endl;
            }

            closeFile(file);
            closeFile(tempFile);
            std::remove("./data/computer/computer.txt");
            std::rename("./data/computer/temp.txt", "./data/computer/computer.txt");
            std::remove(("./data/time/" + obj.getId() + ".txt").c_str());
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
}

template <class T>
bool Database<T>::update(T &obj)
{
    if constexpr (is_same<T, Account>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/account/account.txt", ios::in))
                throw "Không thể mở file account";

            fstream tempFile;
            if (!openFile(tempFile, "./data/account/temp.txt", ios::out))
                throw "Không thể mở file temp";

            string line;
            Account account;
            while (getline(file, line))
            {
                account.unserialize(line);
                if (account.getId() == obj.getId())
                    tempFile << obj << endl;
                else
                    tempFile << line << endl;
            }

            closeFile(file);
            closeFile(tempFile);
            std::remove("./data/account/account.txt");
            std::rename("./data/account/temp.txt", "./data/account/account.txt");
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Customer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/customer/customer.txt", ios::in))
                throw "Không thể mở file customer";

            fstream tempFile;
            if (!openFile(tempFile, "./data/customer/temp.txt", ios::out))
                throw "Không thể mở file temp";

            string line;
            Customer customer;
            while (getline(file, line))
            {
                customer.unserialize(line);
                if (customer.getId() == obj.getId())
                    tempFile << obj << endl;
                else
                    tempFile << line << endl;
            }

            closeFile(file);
            closeFile(tempFile);
            std::remove("./data/customer/customer.txt");
            std::rename("./data/customer/temp.txt", "./data/customer/customer.txt");
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Computer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/computer/computer.txt", ios::in))
                throw "Không thể mở file computer";

            fstream tempFile;
            if (!openFile(tempFile, "./data/computer/temp.txt", ios::out))
                throw "Không thể mở file temp";

            string line;
            Computer computer;
            while (getline(file, line))
            {
                computer.unserialize(line);
                if (computer.getId() == obj.getId())
                    tempFile << obj << endl;
                else
                    tempFile << line << endl;
            }

            closeFile(file);
            closeFile(tempFile);
            std::remove("./data/computer/computer.txt");
            std::rename("./data/computer/temp.txt", "./data/computer/computer.txt");
            return true;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
}

template <class T>
bool Database<T>::get(T &obj)
{
    if constexpr (is_same<T, Account>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/account/account.txt", ios::in))
                throw "Không thể mở file account";

            string line;
            Account account;
            while (getline(file, line))
            {
                account.unserialize(line);
                if (account.getUserName() == obj.getUserName() || account.getId() == obj.getId())
                {
                    obj = account;
                    closeFile(file);
                    return true;
                }
            }

            closeFile(file);
            return false;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Customer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/customer/customer.txt", ios::in))
                throw "Không thể mở file customer";

            string line;
            Customer customer;
            while (getline(file, line))
            {
                customer.unserialize(line);
                if (customer.getUserName() == obj.getUserName() || customer.getId() == obj.getId())
                {
                    obj = customer;
                    closeFile(file);
                    obj.setTime(obj.getTimeFromFile());
                    Database<Account>::get(obj);
                    return true;
                }
            }

            closeFile(file);
            return false;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
    else if constexpr (is_same<T, Computer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/computer/computer.txt", ios::in))
                throw "Không thể mở file computer";

            string line;
            Computer computer;
            while (getline(file, line))
            {
                computer.unserialize(line);
                if (computer.getId() == obj.getId())
                {
                    obj = computer;
                    closeFile(file);
                    obj.setUsageTime(obj.getUsageTimeFromFile());
                    return true;
                }
            }

            closeFile(file);
            return false;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return false;
        }
    }
}

/// @brief Hàm lấy danh sách các đối tượng từ file
/// @tparam T
/// @param field lọc theo trường, nếu là Computer thì field là typeOfComputer (Bỏ trống nếu muốn lấy tất cả)
/// @param value giá trị cần lọc, nếu là Computer thì value là status (Bỏ trống nếu muốn lấy tất cả)
/// @return
template <class T>
List<T> Database<T>::gets(string field, string value)
{
    List<T> objs;
    if constexpr (is_same<T, Account>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/account/account.txt", ios::in))
                throw "Không thể mở file account";

            string line;
            Account account;
            while (getline(file, line))
            {
                account.unserialize(line);

                bool match = false;

                if (field == "")
                    match = (toLower(account.getId()).find(toLower(value)) != string::npos || toLower(account.getUserName()).find(toLower(value)) != string::npos || toLower(account.getRole()).find(toLower(value)) != string::npos || toLower(account.getStatus()).find(toLower(value)) != string::npos || toLower(account.getIsFirstLogin()).find(toLower(value)) != string::npos);
                else if (field == "id")
                    match = toLower(account.getId()).find(toLower(value)) != string::npos;
                else if (field == "username")
                    match = toLower(account.getUserName()).find(toLower(value)) != string::npos;
                else if (field == "role")
                    match = toLower(account.getRole()).find(toLower(value)) != string::npos;
                else if (field == "status")
                    match = toLower(account.getStatus()).find(toLower(value)) != string::npos;
                else if (field == "isFirstLogin")
                    match = toLower(account.getIsFirstLogin()).find(toLower(value)) != string::npos;

                if (match || value == "")
                    objs.push_back(account);
            }

            closeFile(file);
            return objs;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return objs;
        }
    }
    else if constexpr (is_same<T, Customer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/customer/customer.txt", ios::in))
                throw "Không thể mở file customer";

            string line;
            Customer customer;
            while (getline(file, line))
            {
                customer.unserialize(line);
                customer.setTime(customer.getTimeFromFile());

                bool match = false;

                if (field == "")
                    match = (toLower(customer.getId()).find(toLower(value)) != string::npos || toLower(customer.getName()).find(toLower(value)) != string::npos || toLower(customer.getUserName()).find(toLower(value)) != string::npos || toLower(customer.getPhone()).find(toLower(value)) != string::npos || toLower(to_string(customer.getBalance())).find(toLower(value)) != string::npos || toLower(customer.getComputer().getId()).find(toLower(value)) != string::npos);
                else if (field == "id")
                    match = toLower(customer.getId()).find(toLower(value)) != string::npos;
                else if (field == "name")
                    match = toLower(customer.getName()).find(toLower(value)) != string::npos;
                else if (field == "username")
                    match = toLower(customer.getUserName()).find(toLower(value)) != string::npos;
                else if (field == "phone")
                    match = toLower(customer.getPhone()).find(toLower(value)) != string::npos;
                else if (field == "balance")
                    match = toLower(to_string(customer.getBalance())).find(toLower(value)) != string::npos;
                else if (field == "idComputer")
                    match = toLower(customer.getComputer().getId()).find(toLower(value)) != string::npos;

                if (match || value == "")
                    objs.push_back(customer);
            }

            closeFile(file);
            return objs;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return objs;
        }
    }
    else if constexpr (is_same<T, Computer>::value)
    {
        try
        {
            fstream file;
            if (!openFile(file, "./data/computer/computer.txt", ios::in))
                throw "Không thể mở file computer";

            string line;
            Computer computer;
            while (getline(file, line))
            {
                computer.unserialize(line);

                if ((field == "" || toLower(computer.getTypeOfComputer()).find(toLower(field)) != string::npos) && (value == "" || toLower(computer.getStatus()).find(toLower(value)) != string::npos))
                {
                    computer.setUsageTime(computer.getUsageTimeFromFile());
                    objs.push_back(computer);
                }
            }

            closeFile(file);
            return objs;
        }
        catch (const string &error)
        {
            cerr << error << endl;
            return objs;
        }
    }
}

#endif