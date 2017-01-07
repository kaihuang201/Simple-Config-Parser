#ifndef __CFGPARSER_H__
#define __CFGPARSER_H__

#include <stdlib.h>
#include <utility>
#include <mutex>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::mutex;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

enum DataType { Int, Float, Hex, String };

struct CfgEntry {
    string key;
    DataType type;
    bool valid;
    int line;

    int iVal;
    float fVal;
    unsigned hVal;
    string sVal;

    CfgEntry() {};
    CfgEntry(string k, DataType t): key(k), type(t), valid(false) {};

    CfgEntry(string k, const string v): key(k), type(String), sVal(v), valid(true) {};
    CfgEntry(string k, const int& v): key(k), type(Int), iVal(v), valid(true) {};
    CfgEntry(string k, const float& v): key(k), type(Float), fVal(v), valid(true) {};
    CfgEntry(string k, const unsigned& v): key(k), type(Hex), hVal(v), valid(true) {};

    void set(string v) { type = String; sVal = v; valid = true; }
    void set(int& v) { type = Int; iVal = v; valid = true; }
    void set(float& v) { type = Float; fVal = v; valid = true; }
    void set(unsigned& v) { type = Hex; hVal = v; valid = true; }

    DataType getType() const { return type; }
    
    int getInt() const { assert(type==Int); return iVal; }
    float getFloat() const { assert(type==Float); return fVal; }
    unsigned getHex() const { assert(type==Hex); return hVal; }
    string getStr() const { assert(type==String); return sVal; }
};

/**
 * A simple config file parser.
 * - Supports string, int, float, hexidecimal values
 * - Comment lines starts with "#"
 * - Leading and trailing spaces are ignored
 * - keys and values should be seperated by one or more space.
 *
 * example_string "Hello World!"
 * example_int 10
 * example_float 3.14159
 * example_hex 0xCAFEBABE
 */
class CFGParser {
    public:
        CFGParser(string filename): cfgfile(filename) {};
        
        bool load();
        bool save();
        bool save(string filename);

        CfgEntry* get(string key);

        void clear();

    private:
        void parseLine(string line);
        string trim(const string& str);

        string cfgfile;
        vector<string> lines;
        unordered_map<string, CfgEntry> dict;
};

#endif
