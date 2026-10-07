#pragma once
#include <string>
using namespace std;

struct SNode {
    string data;
    SNode* next;
};

struct Stack {
    SNode* head;
};

void SInit(Stack* s);
bool SIsEmpty(Stack* s);
void SPUSH(Stack* s, const string& value);
string SPOP(Stack* s);
string SPEAK(Stack* s);
void SPRINT(Stack* s);