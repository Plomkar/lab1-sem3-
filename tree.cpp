#include "tree.h"
#include <iostream>
#include <queue>
using namespace std;

void TInit(CBTree* t) {
    t->root = nullptr;
}

void TINSERT(CBTree* t, int value) {
    TNode* newNode = new TNode{value, nullptr, nullptr};
    if (t->root == nullptr) {
        t->root = newNode;
        return;
    }
    TNode* cur = t->root;
    while (true) {
        if (value < cur->data) {
            if (cur->left == nullptr) { cur->left = newNode; return; }
            cur = cur->left;
        } else {
            if (cur->right == nullptr) { cur->right = newNode; return; }
            cur = cur->right;
        }
    }
}

TNode* TSEARCH(CBTree* t, int value) {
    TNode* cur = t->root;
    while (cur != nullptr) {
        if (cur->data == value) return cur;
        if (value < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    return nullptr;
}

bool TCHECK_COMPLETE(CBTree* t) {
    if (t->root == nullptr) return true;

    queue<TNode*> q;
    q.push(t->root);
    bool sawMissing = false;

    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();

        if (cur->left != nullptr) {
            if (sawMissing) return false;
            q.push(cur->left);
        } else {
            sawMissing = true;
        }

        if (cur->right != nullptr) {
            if (sawMissing) return false;
            q.push(cur->right);
        } else {
            sawMissing = true;
        }
    }
    return true;
}

void TPRINT(CBTree* t) {
    if (t->root == nullptr) { cout << endl; return; }
    queue<TNode*> q;
    q.push(t->root);
    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();
        cout << cur->data << " ";
        if (cur->left != nullptr) q.push(cur->left);
        if (cur->right != nullptr) q.push(cur->right);
    }
    cout << endl;
}