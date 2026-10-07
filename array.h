#pragma once
#include <string>
using namespace std;

struct Array {
    string* data;
    int size;
    int capacity;
};

void MInit(Array* a);
void MPUSH(Array* a, const string& value);
void MPUSH(Array* a, int index, const string& value);
string MGET(Array* a, int index);
void MDEL(Array* a, int index);
void MSET(Array* a, int index, const string& value);
int  MLEN(Array* a);
void MPRINT(Array* a);