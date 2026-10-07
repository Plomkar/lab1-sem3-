#pragma once
#include <string>
using namespace std;

struct LNode {
    string data;
    LNode* prev;
    LNode* next;
};

struct LList {
    string name;
    LNode* head;
    LNode* tail;
    bool created;
};

void LInit(LList* l);
bool LCreate(LList* l, const string& name);
bool LCheck(LList* l);

void LPUSH(LList* l, const string& value);
void LPUSH_END(LList* l, const string& value);
void LPUSH_BEFORE(LList* l, const string& anchor, const string& value);
void LPUSH_AFTER(LList* l, const string& anchor, const string& value);

void LDEL(LList* l, const string& anchor);
void LDEL_VALUE(LList* l, const string& value);
void LDEL_BEFORE(LList* l, const string& anchor);
void LDEL_AFTER(LList* l, const string& anchor);

string LGET(LList* l, const string& anchor);
int    LSEARCH(LList* l, const string& value);

void LPRINT(LList* l);
void LPRINT_REVERSE(LList* l);