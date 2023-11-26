#pragma once
#include "Sign.h"

typedef struct Queue {
    Sign* data;
    Queue* next;
} Queue;


class Keeper {
private:
    int len = 0;
    Queue* head = NULL;
public:
    Keeper();
    Keeper(int size);
    Keeper(const Keeper& keeper_copy);
    ~Keeper();

    int get_len();

    void getBySign(const string& sign);

    Sign* operator[](int index);
    void add(Sign* n_data);
    void edit(int index);
    void remove(int index);
    void clear();

    void save();
    void load();
    void show();
};

