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

class NumberNode
{
public:
    std::pair<std::string, std::string> token;
    NumberNode(std::pair<std::string, std::string> t)
    {
        token = t;
    }

};

class BinOpNode
{
public:

    NumberNode left;
    std::string opToken;
    NumberNode right;

    BinOpNode(NumberNode l, std::string o, NumberNode r)
    {
        left = l;
        right  = r;
        opToken = o;
  //      opToken = currentToken.first
    }


};

class Parser
{
public:
    std::vector<std::pair<std::string, std::string>> tokens;
    std::pair<std::string, std::string> currentToken;
    int tokenIndex;

    Parser(std::vector<std::pair<std::string, std::string>> t)
    {
        tokenIndex = -1;
        advance();
    }

    std::pair<std::string, std::string> advance()
    {
        tokenIndex++;

        if(tokenIndex < tokens.size())
        {
            currentToken = tokens[tokenIndex];

        }

        return currentToken;
    }

    NumberNode F()
    {
      //  std::pair<std::string, std::string> token;
       /// token = currentToken;

        if((currentToken.first == "INT") || (currentToken.first == "FLOAT"))
        {
            advance();
            return NumberNode(currentToken);

        }
    }

    void T()
    {
        NumberNode left = F();
            while((currentToken.first == "MUL")||(currentToken.first == "DIV"))
            {
                //optoken = currentToken.second();
                NumberNode right = F();
                left = BinOpNode(left, currentToken.second, right);
            }
    }

    void E()
    {

    }







};



int main()
{

    std::string exp;
    std::ifstream file("test.k");

    if(!file.is_open())
    {
        cout << "Not open" << endl;
        return 1;
    }

    std::vector<std::pair<std::string, std::string>> list;

    while(std::getline(file, exp))
    {
        Lexer lex(exp);
        lex.makeTokens();

        //cout << lex.tokens[0].first;

        for(auto x  : lex.tokens)
        {

            //cout << x;
            list.push_back(x);
            //cout << x.first << ", " << x.second << endl;
        }

       /* //scan token
        for(auto x: list)
        {
            cout << x.first << ", " << x.second << endl;


        }*/
        //cout << lex.token



        //lex.toString();

    }
  //  cout << list[14].first;
    std::pair<std::string, std::string> currentToken;


    return 0;
}