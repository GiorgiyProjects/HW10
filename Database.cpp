#include "DataBase.h"

using namespace std;

DataBase::DataBase()
{
    mTables["A"] = new Table("A");
    mTables["B"] = new Table("B");
}

ReturnStatus DataBase::INSERT(string table_name, int key, string val)
{
    if (mTables.find(table_name) == mTables.end())
    {
        return WRONG_TABLE_NAME; // incorrect table name
    }
    return mTables[table_name]->Insert(key, val);
}

ReturnStatus DataBase::TRUNCATE(string table_name)
{
    if (mTables.find(table_name) == mTables.end())
    {
        return WRONG_TABLE_NAME;
    }
    mTables[table_name]->Clear();
    return OK;
}

string DataBase::INTERSECT()
{
    set<string> i = mTables["A"]->InnerJoin(*mTables["B"]);
    std::string str = "";
    for(const auto& it : i) str += it + ",\n";
    return str;
}

string DataBase::SYMMETRIC_DIFFERENCE()
{
    set<string> iA = mTables["A"]->LeftOnlyJoin(*mTables["B"]);
    set<string> iB = mTables["B"]->LeftOnlyJoin(*mTables["A"]);
    iA.insert(iB.begin(), iB.end());
    std::string str = "";
    for(const auto& it : iA)
    {
        string to_insert=it;
        if (iB.find(it) != iB.end())
        {
            to_insert = to_insert[0] + string(",") + it.substr(1);
        }
        str += to_insert + ",\n";
    }
    return str;
}
