#include <iostream>
#include <vector>
using namespace std;

const std::string TT_INT = "INT";
const std::string TT_FLOAT = "FLOAT";
const std::string TT_PLUS = "PLUS";
const std::string TT_MINUS = "MINUS";
const std::string TT_MUL = "MUL";
const std::string TT_DIV = "DIV";
const std::string TT_LPAREN = "LPAREN";
const std::string TT_RPAREN = "RPAREN";


class Token
{

};

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
        currentChar = '\0';
        advance();
    }

    void advance()
    {
        pos++;
        // Standard ensure position does not exceed text length
        if(pos < text.length())
            currentChar = text[pos];
        else
            currentChar = '\0';// Initially I wanted this to be NULL, but this is recommended fix
    }
/*
    std::string makeTokens()
    {
        std::string tokens;

        while(currentChar != '\0')
        {
            switch(currentChar)
            {
            case '\t':
                advance();
                break;
            case '+':
                tokens.append(TT_PLUS);
                advance();
                break;
            case '-':
                tokens.append(TT_MINUS);
                advance();
                break;
            case '*':
                tokens.append(TT_MUL);
                advance();
                break;
            case '(':
                tokens.append(TT_LPAREN);
                advance();
                break;
            case ')':
                tokens.append(TT_RPAREN);
                advance();
                break;
            case '/':
                tokens.append(TT_DIV);
                advance();
                break;
            case '0':
                tokens.append(makeNumber());
                break;
            case '1':
                tokens.append(makeNumber());
                break;
            case '2':
                tokens.append(makeNumber());
                break;
            case '3':
                tokens.append(makeNumber());
                break;
            case '4':
                tokens.append(makeNumber());
                break;
            case '5':
                tokens.append(makeNumber());
                break;
            case '6':
                tokens.append(makeNumber());
                break;
            case '7':
                tokens.append(makeNumber());
                break;
            case '8':
                tokens.append(makeNumber());
                break;
            case '9':
                tokens.append(makeNumber());
                break;
            }
        }
        return tokens;

    }
*/
    /*
    std::string makeNumber()
    {
        int dotCount = 0;
        std::string numString = "";

        while(currentChar != '\0' && )
    }
*/
};

int main()
{

    std::vector<char> test;
    test.push_back('0');
    test.push_back('1');

    std::string sTest = "10a11a1";

    for(auto x:test)
    {
        for(int i = 0; i< sTest.size(); i++)
        {
            if(sTest[i] == x)
            {
                cout << "found one" << endl;
            }
        }

    }


    return 0;
}
