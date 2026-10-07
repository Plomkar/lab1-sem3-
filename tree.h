#pragma once

struct TNode {
    int data;
    TNode* left;
    TNode* right;
};

struct CBTree {
    TNode* root;
};

void TInit(CBTree* t);
void TINSERT(CBTree* t, int value);
bool TCHECK_COMPLETE(CBTree* t);
TNode* TSEARCH(CBTree* t, int value);
void TPRINT(CBTree* t);