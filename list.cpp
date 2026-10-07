#include "list.h"
#include <iostream>

void LInit(LList* l) {
    l->name = "";
    l->head = nullptr;
    l->tail = nullptr;
    l->created = false;
}

bool LCreate(LList* l, const string& name) {
    if (name.empty()) {
        cout << "ERROR: list name is required" << endl;
        return false;
    }
    l->name = name;
    l->created = true;
    l->head = nullptr;
    l->tail = nullptr;
    return true;
}

bool LCheck(LList* l) {
    if (!l->created || l->name.empty()) {
        cout << "ERROR: list name is required" << endl;
        return false;
    }
    return true;
}

void LPUSH(LList* l, const string& value) {
    if (!LCheck(l)) return;
    LNode* newNode = new LNode{value, nullptr, l->head};
    if (l->head != nullptr) l->head->prev = newNode;
    else l->tail = newNode;
    l->head = newNode;
}

void LPUSH_END(LList* l, const string& value) {
    if (!LCheck(l)) return;
    LNode* newNode = new LNode{value, l->tail, nullptr};
    if (l->tail != nullptr) l->tail->next = newNode;
    else l->head = newNode;
    l->tail = newNode;
}

void LPUSH_BEFORE(LList* l, const string& anchor, const string& value) {
    if (!LCheck(l)) return;
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    LNode* newNode = new LNode{value, cur->prev, cur};
    if (cur->prev != nullptr) cur->prev->next = newNode;
    else l->head = newNode;
    cur->prev = newNode;
}

void LPUSH_AFTER(LList* l, const string& anchor, const string& value) {
    if (!LCheck(l)) return;
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    LNode* newNode = new LNode{value, cur, cur->next};
    if (cur->next != nullptr) cur->next->prev = newNode;
    else l->tail = newNode;
    cur->next = newNode;
}

void LDEL(LList* l, const string& anchor) {
    if (!LCheck(l)) return;
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    if (cur->prev != nullptr) cur->prev->next = cur->next;
    else l->head = cur->next;
    if (cur->next != nullptr) cur->next->prev = cur->prev;
    else l->tail = cur->prev;
    delete cur;
}

void LDEL_VALUE(LList* l, const string& value) {
    if (!LCheck(l)) return;
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != value) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: value not found" << endl;
        return;
    }
    if (cur->prev != nullptr) cur->prev->next = cur->next;
    else l->head = cur->next;
    if (cur->next != nullptr) cur->next->prev = cur->prev;
    else l->tail = cur->prev;
    delete cur;
}

void LDEL_BEFORE(LList* l, const string& anchor) {
    if (!LCheck(l)) return;
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    if (cur->prev == nullptr) {
        cout << "ERROR: no element before anchor" << endl;
        return;
    }
    LNode* del = cur->prev;
    if (del->prev != nullptr) del->prev->next = cur;
    else l->head = cur;
    cur->prev = del->prev;
    delete del;
}

void LDEL_AFTER(LList* l, const string& anchor) {
    if (!LCheck(l)) return;
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    if (cur->next == nullptr) {
        cout << "ERROR: no element after anchor" << endl;
        return;
    }
    LNode* del = cur->next;
    cur->next = del->next;
    if (del->next != nullptr) del->next->prev = cur;
    else l->tail = cur;
    delete del;
}

string LGET(LList* l, const string& anchor) {
    if (!LCheck(l)) return "";
    LNode* cur = l->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return "";
    }
    return cur->data;
}

int LSEARCH(LList* l, const string& value) {
    if (!LCheck(l)) return -1;
    LNode* cur = l->head;
    int idx = 0;
    while (cur != nullptr) {
        if (cur->data == value) return idx;
        cur = cur->next;
        idx++;
    }
    return -1;
}

void LPRINT(LList* l) {
    if (!LCheck(l)) return;
    cout << l->name << ": ";
    LNode* cur = l->head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void LPRINT_REVERSE(LList* l) {
    if (!LCheck(l)) return;
    cout << l->name << " (reverse): ";
    LNode* cur = l->tail;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->prev;
    }
    cout << endl;
}