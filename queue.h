#pragma once
#include <string>
using namespace std;

struct QNode {
    string data;
    QNode* next;
};

struct Queue {
    QNode* head;
    QNode* tail;
};

void QInit(Queue* q);
bool QIsEmpty(Queue* q);
void QPUSH(Queue* q, const string& value);
string QPOP(Queue* q);
string QPEEK(Queue* q);
void QPRINT(Queue* q);