#include "array.h"
#include <iostream>

void MInit(Array* a) {
    a->capacity = 4;
    a->size = 0;
    a->data = new string[a->capacity];
}

static void MGrow(Array* a) {
    int newCap = a->capacity * 2;
    string* newData = new string[newCap];
    for (int i = 0; i < a->size; i++) newData[i] = a->data[i];
    delete[] a->data;
    a->data = newData;
    a->capacity = newCap;
}

void MPUSH(Array* a, const string& value) {
    if (a->size >= a->capacity) MGrow(a);
    a->data[a->size] = value;
    a->size++;
}

void MPUSH(Array* a, int index, const string& value) {
    if (index < 0 || index > a->size) return;
    if (a->size >= a->capacity) MGrow(a);
    for (int i = a->size; i > index; i--) {
        a->data[i] = a->data[i - 1];
    }
    a->data[index] = value;
    a->size++;
}

string MGET(Array* a, int index) {
    if (index < 0 || index >= a->size) return "";
    return a->data[index];
}

void MDEL(Array* a, int index) {
    if (index < 0 || index >= a->size) return;
    for (int i = index; i < a->size - 1; i++) {
        a->data[i] = a->data[i + 1];
    }
    a->data[a->size - 1] = "";
    a->size--;
}

void MSET(Array* a, int index, const string& value) {
    if (index < 0 || index >= a->size) return;
    a->data[index] = value;
}

int MLEN(Array* a) {
    return a->size;
}

void MPRINT(Array* a) {
    for (int i = 0; i < a->size; i++) {
        cout << a->data[i] << " ";
    }
    cout << endl;
}