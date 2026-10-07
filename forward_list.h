#pragma once
#include <string>
using namespace std;

struct FNode {
    string data;
    FNode* next;
};

struct FList {
    string name;
    FNode* head;
    bool created;
};

void FInit(FList* f);
bool FCreate(FList* f, const string& name);
bool FCheck(FList* f);

void FPUSH(FList* f, const string& value);
void FPUSH_END(FList* f, const string& value);
void FPUSH_BEFORE(FList* f, const string& anchor, const string& value);
void FPUSH_AFTER(FList* f, const string& anchor, const string& value);

void FDEL(FList* f, const string& anchor);
void FDEL_VALUE(FList* f, const string& value);
void FDEL_BEFORE(FList* f, const string& anchor);
void FDEL_AFTER(FList* f, const string& anchor);

string FGET(FList* f, const string& anchor);
int    FSEARCH(FList* f, const string& value);

void FPRINT(FList* f);