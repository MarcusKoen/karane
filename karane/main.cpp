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



    }

    std::string makeTokens()
    {
        std::string tokens;

        while(pos < text.size())
        {
            switch(currentChar)
            {
            case ' ':
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


    std::string makeNumber()
    {
        bool inDigits = true;
        int dotCount = 0;
        std::string numString = "";
        /*
        for(int i = 0; i< sTest.size(); i++)
        {
            {
                for(auto x:test)
                    if(sTest[i] == x)
                    {
                        cout << x << endl;
                    }
            }

        }


        while(currentChar != '\0' && )
*/
        return "1";
    }



};

int main()
{

    cout << "Enter Expression" << endl;
    std::string exp;
    std::getline(std::cin, exp);
    Lexer lex(exp);
    cout << lex.makeTokens();

    return 0;
}