#include "stack.h"
#include <iostream>

void SInit(Stack* s) { s->head = nullptr; }

bool SIsEmpty(Stack* s) { return s->head == nullptr; }

void SPUSH(Stack* s, const string& value) {
    SNode* newNode = new SNode{value, s->head};
    s->head = newNode;
}

string SPOP(Stack* s) {
    if (SIsEmpty(s)) { cout << "Stack is empty" << endl; return ""; }
    SNode* del = s->head;
    string val = del->data;
    s->head = del->next;
    delete del;
    return val;
}

string SPEAK(Stack* s) {
    if (SIsEmpty(s)) return "";
    return s->head->data;
}

void SPRINT(Stack* s) {
    SNode* cur = s->head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}