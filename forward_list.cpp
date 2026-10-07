#include "forward_list.h"
#include <iostream>

void FInit(FList* f) {
    f->name = "";
    f->head = nullptr;
    f->created = false;
}

bool FCreate(FList* f, const string& name) {
    if (name.empty()) {
        cout << "ERROR: list name is required" << endl;
        return false;
    }
    f->name = name;
    f->created = true;
    f->head = nullptr;
    return true;
}

bool FCheck(FList* f) {
    if (!f->created || f->name.empty()) {
        cout << "ERROR: list name is required" << endl;
        return false;
    }
    return true;
}

void FPUSH(FList* f, const string& value) {
    if (!FCheck(f)) return;
    FNode* newNode = new FNode{value, f->head};
    f->head = newNode;
}

void FPUSH_END(FList* f, const string& value) {
    if (!FCheck(f)) return;
    FNode* newNode = new FNode{value, nullptr};
    if (f->head == nullptr) { f->head = newNode; return; }
    FNode* cur = f->head;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = newNode;
}

void FPUSH_BEFORE(FList* f, const string& anchor, const string& value) {
    if (!FCheck(f)) return;
    if (f->head == nullptr) return;
    if (f->head->data == anchor) {
        FNode* newNode = new FNode{value, f->head};
        f->head = newNode;
        return;
    }
    FNode* cur = f->head;
    while (cur->next != nullptr && cur->next->data != anchor) cur = cur->next;
    if (cur->next == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    FNode* newNode = new FNode{value, cur->next};
    cur->next = newNode;
}

void FPUSH_AFTER(FList* f, const string& anchor, const string& value) {
    if (!FCheck(f)) return;
    FNode* cur = f->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    FNode* newNode = new FNode{value, cur->next};
    cur->next = newNode;
}

void FDEL(FList* f, const string& anchor) {
    if (!FCheck(f)) return;
    if (f->head == nullptr) return;
    if (f->head->data == anchor) {
        FNode* del = f->head;
        f->head = f->head->next;
        delete del;
        return;
    }
    FNode* cur = f->head;
    while (cur->next != nullptr && cur->next->data != anchor) cur = cur->next;
    if (cur->next == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    FNode* del = cur->next;
    cur->next = del->next;
    delete del;
}

void FDEL_VALUE(FList* f, const string& value) {
    if (!FCheck(f)) return;
    if (f->head == nullptr) return;
    if (f->head->data == value) {
        FNode* del = f->head;
        f->head = f->head->next;
        delete del;
        return;
    }
    FNode* cur = f->head;
    while (cur->next != nullptr && cur->next->data != value) cur = cur->next;
    if (cur->next == nullptr) {
        cout << "ERROR: value not found" << endl;
        return;
    }
    FNode* del = cur->next;
    cur->next = del->next;
    delete del;
}

void FDEL_BEFORE(FList* f, const string& anchor) {
    if (!FCheck(f)) return;
    if (f->head == nullptr || f->head->data == anchor) {
        cout << "ERROR: no element before anchor" << endl;
        return;
    }
    FNode* cur = f->head;
    while (cur->next != nullptr && cur->next->data != anchor) cur = cur->next;
    if (cur->next == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    FNode* del = cur->next;
    cur->next = del->next;
    delete del;
}

void FDEL_AFTER(FList* f, const string& anchor) {
    if (!FCheck(f)) return;
    FNode* cur = f->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return;
    }
    if (cur->next == nullptr) {
        cout << "ERROR: no element after anchor" << endl;
        return;
    }
    FNode* del = cur->next;
    cur->next = del->next;
    delete del;
}

string FGET(FList* f, const string& anchor) {
    if (!FCheck(f)) return "";
    FNode* cur = f->head;
    while (cur != nullptr && cur->data != anchor) cur = cur->next;
    if (cur == nullptr) {
        cout << "ERROR: anchor not found" << endl;
        return "";
    }
    return cur->data;
}

int FSEARCH(FList* f, const string& value) {
    if (!FCheck(f)) return -1;
    FNode* cur = f->head;
    int idx = 0;
    while (cur != nullptr) {
        if (cur->data == value) return idx;
        cur = cur->next;
        idx++;
    }
    return -1;
}

void FPRINT(FList* f) {
    if (!FCheck(f)) return;
    cout << f->name << ": ";
    FNode* cur = f->head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}