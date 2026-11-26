#include <iostream>
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

class Position
{
public:
    int index, lineNum, colNum;
    //fileName
    //fileText
    Position(int i, int l, int c)
    {
        index = i;
        lineNum = l;
        colNum = c;
    }

    void advance(char currentChar)
    {
        index++;
        colNum++;

        if(currentChar == '\n')
        {
            lineNum++;
            colNum = 0;
        }
    }

    //WTF?
    Position copy()
    {
        return Position(index, lineNum, colNum);
    }

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

class IllegalCharError:public Error
{
public:
    // I think?
    IllegalCharError(std::string e, std::string d):Error("Illegal Character",d)
    {

    }

};


class Lexer
{
public:
    std::string text;
    Position* pos;
    char currentChar;

    // Constructor
    Lexer(std::string Text)
    {
        text = Text;
        pos = new Position(-1,0,1);
        advance();
    }

    void advance()
    {

        pos->advance(currentChar);

        // Standard ensure position does not exceed text length
        if(pos->index < text.size())
        {
            currentChar = text[pos->index];
        }
        // else return?
    }

    std::string makeTokens()
    {
        std::string tokens;

        while(pos->index < text.size())
        {
            switch(currentChar)
            {
            case ' ':
                advance();
                break;
            case '+':
                tokens.append(TT_PLUS);
                tokens.append(" ");
                advance();
                break;
            case '-':
                tokens.append(TT_MINUS);
                tokens.append(" ");

                advance();
                break;
            case '*':
                tokens.append(TT_MUL);
                tokens.append(" ");

                advance();
                break;
            case '(':
                tokens.append(TT_LPAREN);
                tokens.append(" ");

                advance();
                break;
            case ')':
                tokens.append(TT_RPAREN);
                tokens.append(" ");

                advance();
                break;
            case '/':
                tokens.append(TT_DIV);
                tokens.append(" ");

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
                // TODO ERROR CASE
            default:
                //char c = currentChar;
                advance();
                cout << "Illegal character";
            }
        }
        return tokens;

    }


    std::string makeNumber()
    {
        bool inDigits = true;
        int dotCount = 0;
        std::string numString = "";

        // I would use .contains but this version of C++ is 16, due to distro constraints on debian g++ version
        while((pos->index < text.size()) && (currentChar == '0' ||  currentChar == '1' ||currentChar == '2' ||currentChar == '3' ||
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
            return TT_INT + ":" +numString +" "  ;
        }
        else
        {
            // same as above TODO float
            return TT_FLOAT + ":" + numString +" " ;
        }

    }

};

int main()
{

    cout << "Enter Expression" << endl;
    std::string exp;
    std::getline(std::cin, exp);
    Lexer lex(exp);
    cout << lex.makeTokens() << endl;

    return 0;
}