#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include "ErrorCodes.h"
#include <set>
using namespace std;

class Table
{
    std::string mName;
    unordered_map<int, string> mStorage;
public:
    Table(std::string Name)
    {
        mName = Name;
    }

    ReturnStatus Insert(int key, string val);

    optional<string> Get(int key);

    void Clear();

    set<string> InnerJoin(Table& B);

    set<string> LeftOnlyJoin(Table& B);
};
