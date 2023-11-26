#include <iostream>
#include <fstream>
#include "Keeper.h"
#include <string>
#include <sstream>

using namespace std;

Keeper::Keeper() : len(0), head(nullptr) {}
Keeper::Keeper(int len) : head(nullptr) { this->len = len; }
Keeper::Keeper(const Keeper& keeper_copy) {
    this->head = keeper_copy.head;
    this->len = keeper_copy.len;
}
Keeper::~Keeper() {
    clear();
}

void Keeper::clear() {
    if (head != nullptr) {
        Queue* obj_ptr;
        while (head != nullptr) {
            obj_ptr = head;
            head = head->next;
        }
    }
    head = nullptr;
}

int Keeper::get_len() { return len; }

void Keeper::edit(int index) {
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;
        if (index == 0) {
            obj_ptr->data->edit();
            return;
        }
        for (int i = 0; i < index; i++) {
            obj_ptr = obj_ptr->next;
        }
        obj_ptr->data->edit();
    }
    else {
        cout << "\033[93mNo data.\033[0m" << endl;
    }
}

void Keeper::add(Sign* new_data) {
    Queue* new_obj = new Queue;
    new_obj->data = new_data;
    new_obj->next = nullptr;

    if (head == nullptr || head->data->getSign() >= new_data->getSign()) {
        new_obj->next = head;
        head = new_obj;
    }
    else {
        Queue* current = head;
        while (current->next != nullptr && current->next->data->getSign() <= new_data->getSign()) {
            current = current->next;
        }
        new_obj->next = current->next;
        current->next = new_obj;
    }
    len++;
}

void Keeper::remove(int index) {
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;
        Queue* tmp_ptr = head;
        for (int i = 0; i < index; i++) {
            tmp_ptr = obj_ptr;
            obj_ptr = obj_ptr->next;
        }
        if (obj_ptr == head) {
            head = obj_ptr->next;
        }
        else {
            tmp_ptr->next = obj_ptr->next;
        }
        obj_ptr->data->~Sign();
        delete(obj_ptr);
        len--;
    }
    else {
        cout << "\033[93mNo data.\033[0m" << endl;
    }
}

void Keeper::save() {
    ofstream file;
    string file_name = "Sign.txt";
    try {
        file.open(file_name);
        if (!file) {
            throw runtime_error("Error while opening file " + file_name + " to save data.");
        }
    }
    catch (const exception& e) {
        cout << "\033[91m" << e.what() << "\033[0m";
        return;
    }
    file << len << endl;
    file.close();
    Queue* obj_ptr = head;
    while (obj_ptr != nullptr) {
        obj_ptr->data->save();
        obj_ptr = obj_ptr->next;
    }
    cout << "\033[92mSaved " << len << " Sign.\033[0m" << endl;

}

void Keeper::load() {
    if (len != 0) { clear(); }
    int input_len;
    string inputName, inputSign, inputBirthday, firstName, secondName;
    int birthday[3];
    ifstream file;
    string file_name = "Sign.txt";
    try {
        file.open(file_name);
        if (!file) {
            throw runtime_error("Error while opening file " + file_name + " to save data.");
        }
    }
    catch (const exception& e) {
        cout << "\033[91m" << e.what() << "\033[0m" << endl;
        return;
    }
    file >> input_len;
    file.ignore(32767, '\n');
    for (int i = 0; i < input_len; i++) {
        getline(file, inputName);
        getline(file, inputSign);
        getline(file, inputBirthday);
        istringstream issn(inputName);
        issn >> firstName >> secondName;
        istringstream issb(inputBirthday);
        issb >> birthday[0] >> birthday[1] >> birthday[2];
        Sign* new_Sign;
        new_Sign = new Sign(firstName, secondName, inputSign, birthday);
        add(new_Sign);
    }
    cout << "\033[92mLoaded  " << len << " Sign.\033[0m" << endl;
}

void Keeper::show() {
    if (head != nullptr) {
        Queue* obj_ptr = head;
        cout << "\033[94m0. ";
        obj_ptr->data->printInfo();
        for (int i = 0; i < len - 1; i++) {
            obj_ptr = obj_ptr->next;
            cout << "\033[94m" << i + 1 << ". ";
            obj_ptr->data->printInfo();
        }
    }
    else {
        cout << "\033[93mNo data.\033[0m" << endl;
    }
}

Sign* Keeper::operator[](int index) {
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;
        if (index == 0) {
            obj_ptr->data->edit();
            return nullptr;
        }
        for (int i = 0; i < index; i++) {
            obj_ptr = obj_ptr->next;
        }
        obj_ptr->data->edit();
    }
    cout << "\033[93mNo data.\033[0m" << endl;
    return nullptr;
}

void Keeper::getByMonth(int month) {
    bool has_obj = false;
    if (head != nullptr) {
        Queue* obj_ptr = head;
        if (obj_ptr->data->getBirthdayMonth() == month) {
            cout << "\033[94m0. ";
            obj_ptr->data->printInfo();
            has_obj = true;
        }
        for (int i = 0; i < len - 1; i++) {
            obj_ptr = obj_ptr->next;
            if (obj_ptr->data->getBirthdayMonth() == month) {
                cout << "\033[94m" << i + 1 << ". ";
                obj_ptr->data->printInfo();
                has_obj = true;
            }
        }
    }
    else
        cout << "\033[93mNo data.\033[0m" << endl;
    if (!has_obj)
        cout << "\033[93mNo data.\033[0m" << endl;
}
