#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include "DataBase.h"
#include <sstream>
#include <iostream>

using namespace std;

class CommandInterpreter {

public:
    string receive(string incoming_string, DataBase& DB)
    {
        string result = interpret(incoming_string, DB);
        cout << result << endl;
        return result;
    }

    string interpret(string incoming_string, DataBase& DB)
    {
        std::vector<std::string> command_and_args;
        std::istringstream iss(incoming_string);
        for(std::string s; iss >> s;)
            command_and_args.push_back(s);

        auto command = command_and_args[0];
        string to_return = "";
        if (command == "INSERT") {
            if (command_and_args.size() != 4)
                return StatusMap[WRONG_ARG_NUM];
            auto result = DB.INSERT(command_and_args[1], stoi(command_and_args[2]), command_and_args[3]);
            return StatusMap[result];
        } else if (command =="TRUNCATE") {
            if (command_and_args.size() != 2)
                return StatusMap[WRONG_ARG_NUM];
            auto result = DB.TRUNCATE(command_and_args[1]);
            return StatusMap[result];
        } else if (command == "INTERSECTION") {
            return DB.INTERSECT();
        } else if (command == "SYMMETRIC_DIFFERENCE") {
            return DB.SYMMETRIC_DIFFERENCE();
        }
        return StatusMap[UNKNOWN_COMMAND];
    }
};

