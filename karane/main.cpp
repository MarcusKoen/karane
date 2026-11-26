#include <iostream>
#include <fstream>
#include "lexer.h"
using namespace std;


// Testing this quickly, no value for operators, but values for int and float
// Might be better later when parsing and interpreting, possible conflict is no value forops
//vector<std::pair<std::string, float >>;



class Token
{

};

class Error
{
public:
    std::string errorName;
    std::string details;

    Error(std::string e, std::string d)
    {
        errorName = e;
        details = d;
    }

    void toString()
    {
        cout << errorName << endl;
        cout << details << endl;
    }

};

// Sub-class inheriting from Error, have not used OOP in a year, nostalgic
/*
class IllegalCharError:Error
{
public:
    IllegalCharError(std::string d)
    {
        details = d;
    }

};
*/



int main()
{

    std::string exp;
    std::ifstream file("test.k");

    if(!file.is_open())
    {
        cout << "Not open" << endl;
        return 1;
    }



    while(std::getline(file, exp))
    {
        Lexer lex(exp);
        lex.makeTokens();
        lex.toString();

    }



    return 0;
}