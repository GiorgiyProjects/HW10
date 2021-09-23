#include <unordered_map>
#include "Table.h"
#include <string>
#include <algorithm>
#include <set>

using namespace std;

class DataBase
{
    unordered_map<string, Table*> mTables;
public:
    DataBase();
    ReturnStatus INSERT(string table_name, int key, string val);
    ReturnStatus TRUNCATE(string table_name);
    string INTERSECT();
    string SYMMETRIC_DIFFERENCE();
};
