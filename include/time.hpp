#ifndef MY_TIME
#define MY_TIME 1

#include <iostream>

class Time
{
private:
    int hour, minute, second;
    char colon;

public:
    Time(double hour = 0, double minute = 0, double second = 0);
    ~Time();

    bool isZero();
    bool isValid();
    Time getCurrentTime();
    friend Time &operator++(Time &time);
    friend Time &operator--(Time &time);
    friend Time operator++(Time &time, int);
    friend Time operator--(Time &time, int);
    Time operator+(const Time &time);
    Time operator-(const Time &time);
    friend std::ostream &operator<<(std::ostream &os, const Time &time);
    friend std::istream &operator>>(std::istream &is, Time &time);
    friend bool operator==(const Time &time1, const Time &time2);
    friend bool operator!=(const Time &time1, const Time &time2);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
    int getHour();
    int getMinute();
    int getSecond();

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif