#include <iostream>
#include "Sign.h"
#include "Keeper.h"
#include <conio.h>
#include <cstdlib>

using namespace std;

void menu() {
    cout << "1. Add an Sign" << endl <<
        "2. Show a list of Sign" << endl <<
        "3. Delete Sign" << endl <<
        "4. Edit Sign" << endl <<
        "5. Get daya by sign" << endl <<
        "6. Save data" << endl <<
        "7. Load data" << endl <<
        "0. Exit" << endl <<
        "Select the menu item: ";
}

int main() {
    Keeper* keeper;
    keeper = new Keeper;

    int input_point = 1;
    int input_number;
    string input_string, passKey;
    while (input_point != 0) {
        menu();
        cin >> input_point;
        system("cls");
        switch (input_point) {
        case 1:
            Sign * new_Sign;
            new_Sign = new Sign();
            new_Sign->edit();
            keeper->add(new_Sign);
            break;
        case 2:
            cout << "\033[94mCount Sign: " << keeper->get_len() << "\033[0m" << endl;
            keeper->show();
            break;
        case 3:
            cout << "Enter index of Sign to remove: ";
            cin >> input_number;
            keeper->remove(input_number);
            break;
        case 4:
            cout << "Enter index of Sign to edit: ";
            cin >> input_number;
            keeper->edit(input_number);
            break;
        case 5:
            cout << "Enter destination to get Sign: ";
            cin >> input_string;
                keeper->getBySign(input_string);
            break;
        case 6:
            keeper->save();
            break;
        case 7:
            keeper->load();
            break;
        default:
            break;
        }
        cout << "Press any key to continue...";
        _getch();
        system("cls");
    }
    keeper->~Keeper();
    cout << "Program shutdown by user.";
    return 0;
}