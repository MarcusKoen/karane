#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>


class Lexer
{
public:
    std::vector<std::pair<std::string , std::string >> tokens;

    std::string text;
    int pos;
    char currentChar;


    // Constructor
    Lexer(std::string Text);
    void advance();
    void makeTokens();
    void makeNumber();
    void toString();

};

#endif // LEXER_H
