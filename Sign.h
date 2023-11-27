#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Sign {
private:
    string firstName;
    string secondName;
    string sign;
    int birthday[3] = {0};

public:
    Sign();
    Sign(string sFirstName, string sSecondName, string sSign, int sBirthday[3]);
    Sign(const Sign& sCopy);
    ~Sign();

    string getName() const;
    string getSign() const;
    string getBirthday() const;
    int getBirthdayMonth();

    void setName(const string& sFirstName, const string& sSecondName);
    void setSign(const string& sSign);
    void setBirthday(const int sBirthday[3]);

    void printInfo();
    void edit();
    void save();

    friend std::ostream& operator<<(std::ostream& os, const Sign& sign);
    friend std::istream& operator>>(std::istream& os, Sign& sign);
};
