#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <utility>
#include <vector>

using TokenPair = std::pair<std::string, std::string>;

class Lexer
{
public:
    std::vector<TokenPair> tokens;
    std::string text;
    size_t pos;
    char currentChar;

    explicit Lexer(std::string Text);
    void advance();
    void makeTokens();
    void makeNumber();
    void toString() const;
};

#endif // LEXER_H