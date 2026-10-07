#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array.h"
#include "forward_list.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"

using namespace std;

Array    g_array;
FList    g_flist;
LList    g_llist;
Stack    g_stack;
Queue    g_queue;
CBTree   g_tree;

void TSaveHelper(TNode* node, ostream& out) {
    if (node == nullptr) return;
    out << " " << node->data;
    TSaveHelper(node->left, out);
    TSaveHelper(node->right, out);
}

void saveToFile(const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) return;

    out << "M";
    for (int i = 0; i < g_array.size; i++) out << " " << g_array.data[i];
    out << "\n";

    out << "F " << g_flist.name;
    FNode* fcur = g_flist.head;
    while (fcur != nullptr) { out << " " << fcur->data; fcur = fcur->next; }
    out << "\n";

    out << "L " << g_llist.name;
    LNode* lcur = g_llist.head;
    while (lcur != nullptr) { out << " " << lcur->data; lcur = lcur->next; }
    out << "\n";

    out << "S";
    string* stackBuf = new string[1024];
    int stackCount = 0;
    SNode* scur = g_stack.head;
    while (scur != nullptr && stackCount < 1024) {
        stackBuf[stackCount++] = scur->data;
        scur = scur->next;
    }
    for (int i = stackCount - 1; i >= 0; i--) out << " " << stackBuf[i];
    delete[] stackBuf;
    out << "\n";

    out << "Q";
    QNode* qcur = g_queue.head;
    while (qcur != nullptr) { out << " " << qcur->data; qcur = qcur->next; }
    out << "\n";

    out << "T";
    TSaveHelper(g_tree.root, out);
    out << "\n";

    out.close();
}

void loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return;

    MInit(&g_array);
    FInit(&g_flist);
    LInit(&g_llist);
    SInit(&g_stack);
    QInit(&g_queue);
    TInit(&g_tree);

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        char type;
        iss >> type;

        if (type == 'F') {
            string name;
            if (iss >> name) {
                FCreate(&g_flist, name);
                string token;
                while (iss >> token) FPUSH_END(&g_flist, token);
            }
        }
        else if (type == 'L') {
            string name;
            if (iss >> name) {
                LCreate(&g_llist, name);
                string token;
                while (iss >> token) LPUSH_END(&g_llist, token);
            }
        }
        else {
            string token;
            while (iss >> token) {
                switch (type) {
                    case 'M': MPUSH(&g_array, token); break;
                    case 'S': SPUSH(&g_stack, token); break;
                    case 'Q': QPUSH(&g_queue, token); break;
                    case 'T': {
                        try { TINSERT(&g_tree, stoi(token)); } catch (...) {}
                        break;
                    }
                }
            }
        }
    }
    in.close();
}

void processQuery(const string& query) {
    istringstream iss(query);
    string cmd;
    iss >> cmd;

    if (cmd == "MPUSH") {
        string a, b;
        if (iss >> a >> b) {
            try {
                int idx = stoi(a);
                MPUSH(&g_array, idx, b);
                cout << b << endl;
            } catch (...) {
                MPUSH(&g_array, a);
                cout << a << endl;
            }
        } else if (!a.empty()) {
            MPUSH(&g_array, a);
            cout << a << endl;
        }
    }
    else if (cmd == "MGET") {
        int i; iss >> i;
        cout << MGET(&g_array, i) << endl;
    }
    else if (cmd == "MDEL") {
        int i; iss >> i;
        MDEL(&g_array, i);
        cout << "OK" << endl;
    }
    else if (cmd == "MSET") {
        int i; string v; iss >> i >> v;
        MSET(&g_array, i, v);
        cout << "OK" << endl;
    }
    else if (cmd == "MLEN") {
        cout << MLEN(&g_array) << endl;
    }

    else if (cmd == "FCREATE") {
        string name; iss >> name;
        if (FCreate(&g_flist, name)) cout << "OK" << endl;
    }
    else if (cmd == "FPUSH") {
        string a, b;
        if (!(iss >> a)) {
            cout << "ERROR: list name is required" << endl;
        } else if (iss >> b) {
            if (b == "END") {
                FPUSH_END(&g_flist, a);
            } else {
                FPUSH_BEFORE(&g_flist, b, a);
            }
            cout << "OK" << endl;
        } else {
            FPUSH(&g_flist, a);
            cout << "OK" << endl;
        }
    }
    else if (cmd == "FPUSH_BEFORE") {
        string anchor, v;
        if (iss >> anchor >> v) {
            FPUSH_BEFORE(&g_flist, anchor, v);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor and value required" << endl;
        }
    }
    else if (cmd == "FPUSH_AFTER") {
        string anchor, v;
        if (iss >> anchor >> v) {
            FPUSH_AFTER(&g_flist, anchor, v);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor and value required" << endl;
        }
    }
    else if (cmd == "FGET") {
        string anchor;
        if (iss >> anchor) {
            string res = FGET(&g_flist, anchor);
            if (!res.empty()) cout << res << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "FDEL") {
        string arg;
        if (iss >> arg) {
            if (arg == "VALUE") {
                string v; iss >> v;
                FDEL_VALUE(&g_flist, v);
            } else {
                FDEL(&g_flist, arg);
            }
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "FDEL_BEFORE") {
        string anchor;
        if (iss >> anchor) {
            FDEL_BEFORE(&g_flist, anchor);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "FDEL_AFTER") {
        string anchor;
        if (iss >> anchor) {
            FDEL_AFTER(&g_flist, anchor);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "FSEARCH") {
        string v;
        if (iss >> v) {
            cout << FSEARCH(&g_flist, v) << endl;
        } else {
            cout << "ERROR: value required" << endl;
        }
    }

    else if (cmd == "LCREATE") {
        string name; iss >> name;
        if (LCreate(&g_llist, name)) cout << "OK" << endl;
    }
    else if (cmd == "LPUSH") {
        string a, b;
        if (!(iss >> a)) {
            cout << "ERROR: list name is required" << endl;
        } else if (iss >> b) {
            if (b == "END") {
                LPUSH_END(&g_llist, a);
            } else {
                LPUSH_BEFORE(&g_llist, b, a);
            }
            cout << "OK" << endl;
        } else {
            LPUSH(&g_llist, a);
            cout << "OK" << endl;
        }
    }
    else if (cmd == "LPUSH_BEFORE") {
        string anchor, v;
        if (iss >> anchor >> v) {
            LPUSH_BEFORE(&g_llist, anchor, v);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor and value required" << endl;
        }
    }
    else if (cmd == "LPUSH_AFTER") {
        string anchor, v;
        if (iss >> anchor >> v) {
            LPUSH_AFTER(&g_llist, anchor, v);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor and value required" << endl;
        }
    }
    else if (cmd == "LGET") {
        string anchor;
        if (iss >> anchor) {
            string res = LGET(&g_llist, anchor);
            if (!res.empty()) cout << res << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "LDEL") {
        string arg;
        if (iss >> arg) {
            if (arg == "VALUE") {
                string v; iss >> v;
                LDEL_VALUE(&g_llist, v);
            } else {
                LDEL(&g_llist, arg);
            }
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "LDEL_BEFORE") {
        string anchor;
        if (iss >> anchor) {
            LDEL_BEFORE(&g_llist, anchor);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "LDEL_AFTER") {
        string anchor;
        if (iss >> anchor) {
            LDEL_AFTER(&g_llist, anchor);
            cout << "OK" << endl;
        } else {
            cout << "ERROR: anchor required" << endl;
        }
    }
    else if (cmd == "LSEARCH") {
        string v;
        if (iss >> v) {
            cout << LSEARCH(&g_llist, v) << endl;
        } else {
            cout << "ERROR: value required" << endl;
        }
    }

    else if (cmd == "SPUSH") {
        string v; iss >> v;
        SPUSH(&g_stack, v);
        cout << v << endl;
    }
    else if (cmd == "SPOP") {
        cout << SPOP(&g_stack) << endl;
    }
    else if (cmd == "SPEEK") {
        cout << SPEAK(&g_stack) << endl;
    }

    else if (cmd == "QPUSH") {
        string v; iss >> v;
        QPUSH(&g_queue, v);
        cout << v << endl;
    }
    else if (cmd == "QPOP") {
        cout << QPOP(&g_queue) << endl;
    }
    else if (cmd == "QPEEK") {
        cout << QPEEK(&g_queue) << endl;
    }

    else if (cmd == "TINSERT") {
        int v; iss >> v;
        TINSERT(&g_tree, v);
        cout << v << endl;
    }
    else if (cmd == "TGET") {
        int v; iss >> v;
        TNode* node = TSEARCH(&g_tree, v);
        if (node == nullptr) cout << "NOT FOUND" << endl;
        else cout << node->data << endl;
    }
    else if (cmd == "TSEARCH") {
        int v; iss >> v;
        TNode* node = TSEARCH(&g_tree, v);
        cout << (node == nullptr ? "FALSE" : "TRUE") << endl;
    }
    else if (cmd == "TCHECK") {
        cout << (TCHECK_COMPLETE(&g_tree) ? "TRUE" : "FALSE") << endl;
    }

    else if (cmd == "PRINT") {
        string what; iss >> what;
        if (what == "M") MPRINT(&g_array);
        else if (what == "F") FPRINT(&g_flist);
        else if (what == "L") LPRINT(&g_llist);
        else if (what == "S") SPRINT(&g_stack);
        else if (what == "Q") QPRINT(&g_queue);
        else if (what == "T") TPRINT(&g_tree);
        else cout << "Unknown container" << endl;
    }
    else if (cmd == "PRINT_REVERSE") {
        string what; iss >> what;
        if (what == "L") LPRINT_REVERSE(&g_llist);
        else cout << "Unknown container" << endl;
    }
    else {
        cout << "Unknown command: " << cmd << endl;
    }
}

int main(int argc, char* argv[]) {
    string filename;
    string query;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    MInit(&g_array);
    FInit(&g_flist);
    LInit(&g_llist);
    SInit(&g_stack);
    QInit(&g_queue);
    TInit(&g_tree);

    if (!filename.empty()) loadFromFile(filename);

    if (!query.empty()) {
        processQuery(query);
        if (!filename.empty()) saveToFile(filename);
    } else {
        cout << "Usage: ./dbms --file <file.data> --query '<COMMAND> [args]'" << endl;
    }

    return 0;
}