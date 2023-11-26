#include <iostream>
#include "Sign.h"
#include "Keeper.h"
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

void menuf() {
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

void task_1_run() {
    Keeper* keeper;
    keeper = new Keeper;

    int input_point = 1;
    int input_number;
    string input_string, passKey;
    while (input_point != 0) {
        menuf();
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
}



using namespace std;

struct Sentence {
    int line_ind;
    int start_ind;
    int end_ind;
    Sentence* next;
};

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
        cout << "\033[91m" << e.what() << "\033[0m";
        return 0;
    }

    Sentence* question_sentences = nullptr;
    Sentence* exclamation_sentences = nullptr;

    string line;
    int line_ind = 0;
    int qcount = 0;
    int ecount = 0;
    while (getline(file, line)) {
        int start_ind = 0;
        while (true) {
            size_t end_ind = line.find_first_of(".?!", start_ind);
            if (end_ind == string::npos) {
                break;
            }
            Sentence* sentence = new Sentence;
            sentence->line_ind = line_ind;
            sentence->start_ind = start_ind;
            sentence->end_ind = end_ind;
            sentence->next = nullptr;
            if (line[end_ind] == '?') {
                qcount++;
                if (question_sentences == nullptr) {
                    question_sentences = sentence;
                }
                else {
                    Sentence* temp = question_sentences;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = sentence;
                }
            }
            else if (line[end_ind] == '!') {
                ecount++;
                if (exclamation_sentences == nullptr) {
                    exclamation_sentences = sentence;
                }
                else {
                    Sentence* temp = exclamation_sentences;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = sentence;

                }
            }
            start_ind = end_ind + 1;
        }
        ++line_ind;
    }
    string line_out;
    Sentence* temp = question_sentences;
    if (qcount) {
        cout << "\033[94mQuestion sentences (total: " << qcount << "):\033[0m " << endl;
        file.clear();
        file.seekg(0);
        line_ind = 0;
        while (getline(file, line)) {
            while (temp != nullptr && temp->line_ind == line_ind) {
                line_out = line.substr(temp->start_ind, temp->end_ind - temp->start_ind + 1);
                cout << line_out.substr(line_out.find_first_not_of(' ')) << endl;

                Sentence* temp2 = temp;
                temp = temp->next;
                delete temp2;
            }
            line_ind++;
        }
    }
    else {
        cout << "\033[91mNo Question sentences.\033[0m" << endl;
    }
    cout << endl;
    if (ecount) {
        cout << "\033[94mExclamation sentences (total: " << ecount << "): \033[0m" << endl;
        file.clear();
        file.seekg(0);
        line_ind = 0;
        temp = exclamation_sentences;
        while (getline(file, line)) {
            while (temp != nullptr && temp->line_ind == line_ind) {
                line_out = line.substr(temp->start_ind, temp->end_ind - temp->start_ind + 1);
                cout << line_out.substr(line_out.find_first_not_of(' ')) << endl;

                Sentence* temp2 = temp;
                temp = temp->next;
                delete temp2;
            }
            line_ind++;
        }
    }
    else {
        cout << "No exclamation sentences." << endl;
    }
    file.close();
    cout << "Press any key to exit...";
    _getch();
    return 0;
}


int main() {
    int task;
    cout << "chouse task (1/2): ";
    cin >> task;
    if (task == 1) {
        task_1_run();
    }
    else {
        task_2_run();
    }
    return 0;
}