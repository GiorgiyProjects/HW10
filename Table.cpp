#include "Table.h"
#include <iostream>

ReturnStatus Table::Insert(int key, string val)
{
    if (mStorage.find(key) != mStorage.end())
    {
        return DUBLICATE_KEY; // error: duplicate key
    }
    mStorage[key] = val;
    return OK; // success
}

void Table::Clear()
{
    mStorage.clear();
}

optional<string> Table::Get(int key)
{
    if (mStorage.find(key) != mStorage.end())
        return mStorage[key];
    return nullopt;
}

set<string> Table::InnerJoin(Table& B)
{
    set<string> result;
    for (const auto& pair:mStorage)
    {
        auto tmp = B.Get(pair.first);
        if (tmp) {
            string a = std::to_string(pair.first) + "," + pair.second + "," + tmp.value();
            result.insert(a);
        }
    }
    return result;
}


set<string> Table::LeftOnlyJoin(Table& B)
{
    set<string> result;
    for (const auto& pair:mStorage)
    {
        auto tmp = B.Get(pair.first);
        if (!tmp)
            result.insert(to_string(pair.first) + "," + pair.second);
    }
    return result;
}
