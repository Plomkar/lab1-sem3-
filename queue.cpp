#include "queue.h"
#include <iostream>

void QInit(Queue* q) { q->head = nullptr; q->tail = nullptr; }

bool QIsEmpty(Queue* q) { return q->head == nullptr; }

void QPUSH(Queue* q, const string& value) {
    QNode* newNode = new QNode{value, nullptr};
    if (q->tail != nullptr) q->tail->next = newNode;
    else q->head = newNode;
    q->tail = newNode;
}

string QPOP(Queue* q) {
    if (QIsEmpty(q)) { cout << "Queue is empty" << endl; return ""; }
    QNode* del = q->head;
    string val = del->data;
    q->head = del->next;
    if (q->head == nullptr) q->tail = nullptr;
    delete del;
    return val;
}

string QPEEK(Queue* q) {
    if (QIsEmpty(q)) return "";
    return q->head->data;
}

void QPRINT(Queue* q) {
    QNode* cur = q->head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}