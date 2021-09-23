#include <unordered_map>
#include <string>
using namespace std;

enum ReturnStatus
{
    OK,
    WRONG_TABLE_NAME,
    DUBLICATE_KEY,
    WRONG_ARG_NUM,
    UNKNOWN_COMMAND
};

static unordered_map<int, string> StatusMap = {
        {OK, "OK!"},
        {WRONG_TABLE_NAME, "Err wrong table name"},
        {DUBLICATE_KEY, "Err duplicate key"},
        {WRONG_ARG_NUM, "Err wrong number of arguments"},
        {UNKNOWN_COMMAND, "Err unknown command"}
};

