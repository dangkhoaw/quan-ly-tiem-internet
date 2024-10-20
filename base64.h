#ifndef BASE64
#define BASE64 1

#include <iostream>

using namespace std;

class Base64
{
private:
    string str;

public:
    Base64(const string);

    /// @brief Mã hóa
    /// @return
    string encode();

    /// @brief Giải mã
    /// @return Chuỗi được giải mã
    string decode();

    ~Base64();
};

#endif