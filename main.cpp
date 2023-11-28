#include <iostream>
#include "Sign.h"
#include "Keeper.h"
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void menu() {
    cout << "1. Add an Sign" << endl <<
        "2. Show a list of Sign" << endl <<
        "3. Delete Sign" << endl <<
        "4. Edit Sign" << endl <<
        "5. Get data by birthday month" << endl <<
        "6. Save data" << endl <<
        "7. Load data" << endl <<
        "0. Exit" << endl <<
        "Select the menu item: ";
}

void task_1_run() {
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
            cout << "Count Sign: " << keeper->get_len() << "" << endl;
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
            cout << "Enter month: ";
            cin >> input_number;
            keeper->getByMonth(input_number);
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
}


int task_2_run() {
    cout << "Enter file name to check: ";
    string file_name;
    cin >> file_name;
    ifstream file;
    try {
        file.open(file_name);
        if (!file)
            throw runtime_error("Error while opening file " + file_name + " to load data.");
    }
    catch (const exception& e) {
        cout << "" << e.what() << "";
        return 0;
    }
    string line, word;
    cout << "Enter word to find: ";
    cin >> word;
    while (getline(file, line)) {
        size_t pos = 0;
        string sentence;
        int count = 0;
        while ((pos = line.find_first_of(".!?")) != string::npos) {
            sentence = line.substr(0, pos + 1);
            istringstream iss_sentence(sentence);
            string temp_word;
            while (iss_sentence >> temp_word) {
                if (temp_word == word)
                    count++;
            }
            cout << sentence.substr(sentence.find_first_not_of(' ')) << " " << count << " times" << endl;
            line.erase(0, pos + 1);
            count = 0;
        }
    }
    file.close();
    cout << "Press any key to exit...";
    _getch();
    return 0;
}


int main() {
    int task;
    cout << "Chouse task (1/2): ";
    cin >> task;
    if (task == 1) {
        task_1_run();
    }
    else {
        task_2_run();
    }
    return 0;
}