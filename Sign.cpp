#include "Sign.h"

using namespace std;

Sign::Sign() {
    cout << "\033[90mSign constructor called\033[0m" << endl;
}
Sign::Sign(string sFirstName, string sSecondName, string sSign, int *sBirthday) : firstName(sFirstName), secondName(sSecondName), sign{sSign} {
    this->birthday[0] = sBirthday[0];
    this->birthday[1] = sBirthday[1];
    this->birthday[2] = sBirthday[2];
    cout << "\033[90mSign constructor called\033[0m" << endl;
}
Sign::Sign(const Sign &sCopy) : firstName(sCopy.firstName), secondName(sCopy.secondName), sign{sCopy.sign} {
    this->birthday[0] = sCopy.birthday[0];
    this->birthday[1] = sCopy.birthday[1];
    this->birthday[2] = sCopy.birthday[2];
    cout << "\033[90mSign constructor called\033[0m" << endl;
}
Sign::~Sign() {
    cout << "\033[90mSign destructor called\033[0m" << endl;
}

string Sign::getName() const {
    return firstName + " " + secondName;
};
string Sign::getBirthday() const {
    return to_string(birthday[0]) + "." + to_string(birthday[1]) + "." + to_string(birthday[2]);
}
string Sign::getSign() const {
    return sign;
}

void Sign::setName(const string& sFirstName, const string& sSecondName) {
    this->firstName = sFirstName;
    this->secondName = sSecondName;
}
void Sign::setSign(const string& sSign) {
    this->sign = sSign;
}
void Sign::setBirthday(const int sBirthday[3]) {
    this->birthday[0] = sBirthday[0];
    this->birthday[1] = sBirthday[1];
    this->birthday[2] = sBirthday[2];
}


void Sign::printInfo() {
    cout << "\033[94m[" << getName() << "] - " << getSign() << " (" << getBirthday() << ")\033[0m" << endl;
}
void Sign::edit() {
    if (firstName.empty() || secondName.empty())
        cout << "Enter name (format: first_name second_name): ";
    else
        cout << "Enter name (format: first_name second_name; current - " << getName() << "): ";
    cin >> firstName >> secondName;
    if (sign.empty())
        cout << "Enter sign: ";
    else
        cout << "Enter sign (current - " << getSign() << "): ";
    cin >> sign;
    if (birthday[0]==0 && birthday[1]==0 && birthday[2]==0)
        cout << "Enter birthday (format: DD MM YY): ";
    else
        cout << "Enter birthday (format: DD MM YY; current - " << getBirthday() << "): ";
    cin >> birthday[0] >> birthday[1] >> birthday[2];
    cout << "\033[0m" << endl;
    printInfo();
}
void Sign::save() {
    ofstream file;
    string file_name = "Sign.txt";
    file.open(file_name, ios::app);
    if (!file) {
        cout << "\033[91mError while opening file " << file_name << " to load data.\033[0m";
        return;
    }
    file << firstName << " " << secondName << endl << sign << endl << birthday[0] << " " << birthday[1] << " " << birthday[2] << endl;
    file.close();
}


