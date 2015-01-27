// kv_db.cpp : Defines the entry point for the console application.
//

#include "KvDb.h"
#include <iostream>
#include <string>

void TestKvDb()
{
    KvDb test;
    test.Set("a", "20");
    std::cout << "Val of a is:" << test.Get("a") << std::endl;
    test.Set("b", "20");
    std::cout << "Count of 20 is:" << test.Count("20") << std::endl;
    test.Delete("a");
    std::cout << "Val of a is:" << test.Get("a") << std::endl;
    std::cout << "Count of 20 is:" << test.Count("20") << std::endl;
}

void SplitInput(std::string input, std::string &command, std::string &key, std::string &val)
{
    int pos1 = input.find(" ");
    command = input.substr(0, pos1);
    
    int pos2 = input.find(" ", pos1 + 1);
    key = input.substr(pos1 + 1, pos2 - pos1 - 1);
    
    int pos3 = input.find(" ", pos2 + 1);
    val = input.substr(pos2 + 1, pos3 - pos2 - 1);
}

int main(int argc, char* argv[])
{
    KvDb masterDb;
    std::string command;
    while (command != "END")
    {
        std::string user_input,key,val;
        std::cout << ">>>";
        std::getline(std::cin, user_input);

        SplitInput(user_input, command, key, val);
        if (command == "SET")
        {
            masterDb.Set(key, val);
            std::cout << key << "=" << val;
        }
        else if (command == "GET")
        {
            std::cout<<masterDb.Get(key);
        }
        else if (command == "COUNT")
        {
            std::cout << masterDb.Count(key);
        }
        else if (command == "DELETE")
        {
            std::cout << masterDb.Delete(key);
        }
        else if (command == "BEGIN")
        {
            masterDb.Begin();
        }
        else if (command == "COMMIT")
        {
            masterDb.Commit();
        }
        else if (command == "ROLLBACK")
        {
            masterDb.Rollback();
        }
        std::cout << std::endl;
        
    }
	return 0;
}

