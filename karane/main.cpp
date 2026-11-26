#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const std::string TT_INT = "INT";
const std::string TT_FLOAT = "FLOAT";
const std::string TT_PLUS = "PLUS";
const std::string TT_MINUS = "MINUS";
const std::string TT_MUL = "MUL";
const std::string TT_DIV = "DIV";
const std::string TT_LPAREN = "LPAREN";
const std::string TT_RPAREN = "RPAREN";

vector<std::string> tokens;

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

class Lexer
{
public:
    std::string text;
    int pos;
    char currentChar;

    // Constructor
    Lexer(std::string Text)
    {
        text = Text;
        pos = -1;
        advance();
    }

    void advance()
    {

        pos++;

        // Standard ensure position does not exceed text length
        if(pos < text.size())
        {
            currentChar = text[pos];
        }
        // else return?
    }

    void makeTokens()
    {
        while(pos < text.size())
        {
            switch(currentChar)
            {
            case ' ':
                advance();
                break;
            case '+':
                tokens.push_back(TT_PLUS);
                advance();
                break;
            case '-':
                tokens.push_back(TT_MINUS);
                advance();
                break;
            case '*':
                tokens.push_back(TT_MUL);
                advance();
                break;
            case '(':
                tokens.push_back(TT_LPAREN);
                advance();
                break;
            case ')':
                tokens.push_back(TT_RPAREN);
                advance();
                break;
            case '/':
                tokens.push_back(TT_DIV);
                advance();
                break;
            case '0':
                makeNumber();
                break;
            case '1':
                makeNumber();
                break;
            case '2':
                makeNumber();
                break;
            case '3':
                makeNumber();
                break;
            case '4':
                makeNumber();
                break;
            case '5':
                makeNumber();
                break;
            case '6':
                makeNumber();
                break;
            case '7':
                makeNumber();
                break;
            case '8':
                makeNumber();
                break;
            case '9':
                makeNumber();
                break;
                // TODO ERROR CASE
                //   default:
            }
        }

    }


    void makeNumber()
    {
        bool inDigits = true;
        int dotCount = 0;
        std::string numString = "";

        // I would use .contains but this version of C++ is 16, due to distro constraints on debian g++ version
        while((pos < text.size()) && (currentChar == '0' ||  currentChar == '1' ||currentChar == '2' ||currentChar == '3' ||
                                       currentChar == '4' ||currentChar == '5' ||currentChar == '6' ||currentChar == '7' ||currentChar == '8' ||
                                       currentChar == '9' || currentChar == '.'))
        {

            if(currentChar == '.')
            {
                // Break if there is more than one dot; invalid
                if(dotCount == 1)
                    break;

                dotCount++;
                numString += '.';
            }
            else
            {
                numString += currentChar;
            }
            advance();

        }

        if(dotCount == 0)
        {
            // Token(TT_INT, int(num_str)
            tokens.push_back(TT_INT);
            //return TT_INT + numString +":" ;
        }
        else
        {
            // same as above TODO float
            tokens.push_back(TT_FLOAT);
           // return TT_FLOAT + numString + ":" ;
        }

    }

};

int main()
{

    cout << "Enter Expression" << endl;
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
    }


    for(auto x: tokens)
        cout << x << endl;
    //cout << lex.makeTokens() << endl;

    return 0;
}