#include <iostream>
#include "cfg.h"

using std::cout;
using std::endl;

int main() {

    CfgEntry pe = CfgEntry("key", "string");
    CfgEntry pe2 = pe;

    cout << pe2.getStr() << endl;
    //*
    CFGParser cfg("config.cfg");
    cfg.load();

    CfgEntry* e;
    if (e = cfg.get("int"))
        cout << e->getInt() << endl;

    //if (e = cfg.get("string"))
    //    cout << e->getStr() << endl;

    CfgEntry s = CfgEntry("key", "value");
    CfgEntry i = CfgEntry("key", 100);
    CfgEntry f = CfgEntry("key", (float)3.14);
    CfgEntry h = CfgEntry("key", (unsigned)100);

    cout << s.getStr() << endl;
    cout << i.getInt() << endl;
    cout << f.getFloat() << endl;
    cout << h.getHex() << endl;
    //*/

    return 0;
}
