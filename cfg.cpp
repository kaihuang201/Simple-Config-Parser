#include "cfg.h"

bool CFGParser::load()
{
    ifstream infile(cfgfile);
    if (!infile.is_open())
        return false;

    string line;
    while (getline(infile, line))
    {
        lines.push_back(line);
        parseLine(line);
    }

    return true;
}

void CFGParser::parseLine(string line)
{
    line = trim(line);
    int line_num = lines.size();
    if (line.empty() || line[0]=='#')
        return;
    
    try {
        int firstSpace = line.find_first_of(" \t");
        if (firstSpace == string::npos)
            return;

        CfgEntry entry;
        entry.key = line.substr(0, firstSpace);
        entry.line = lines.size();
        string valstr = trim(line.substr(firstSpace));
        
        if (valstr.length()>2 && valstr[0]=='0' && valstr[1]=='x')
        {
            // Hex
            valstr = valstr.substr(2);
            unsigned u = std::stol(valstr, (size_t)0, 16);
            entry.set(u);
            cout << u << endl;
        }
        else if (valstr.length()>1 && valstr[0]=='"' && valstr[valstr.size()-1]=='"')
        {
            // String
            valstr = valstr.substr(1, valstr.size()-2);
            entry.set(valstr);
        }
        else if (valstr.find(".")==string::npos)
        {
            // int
            int i = std::stoi(valstr);
            entry.set(i);
        }
        else
        {
            // float
            float f = std::stof(valstr);
            entry.set(f);
        }

        dict.emplace(entry.key, entry);
    } catch(...) {
        cout << line_num << "Error parsing line: " << line << endl;
    }
}

bool CFGParser::save(string filename)
{
    return true;
}


CfgEntry* CFGParser::get(string key)
{
    auto it = dict.find(key);
    if (it == dict.end())
        return NULL;
    return &it->second;
}

string CFGParser::trim(const string& str)
{
    string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}
