#include "lexer.h"
#include <cctype>
#include <iostream>

const std::string TT_INT = "INT";
const std::string TT_FLOAT = "FLOAT";
const std::string TT_PLUS = "PLUS";
const std::string TT_MINUS = "MINUS";
const std::string TT_MUL = "MUL";
const std::string TT_DIV = "DIV";
const std::string TT_LPAREN = "LPAREN";
const std::string TT_RPAREN = "RPAREN";

Lexer::Lexer(std::string t)
    : text(std::move(t)), pos(0), currentChar(text.empty() ? '\0' : text[0])
{
}

void Lexer::advance()
{
    pos++;
    if (pos < text.size())
    {
        currentChar = text[pos];
    }
    else
    {
        currentChar = '\0';
    }
}

void Lexer::makeTokens()
{
    tokens.clear();

    while (pos < text.size())
    {
        if (std::isspace(static_cast<unsigned char>(currentChar)))
        {
            advance();
        }
        else if (currentChar == '+')
        {
            tokens.push_back({TT_PLUS, "+"});
            advance();
        }
        else if (currentChar == '-')
        {
            tokens.push_back({TT_MINUS, "-"});
            advance();
        }
        else if (currentChar == '*')
        {
            tokens.push_back({TT_MUL, "*"});
            advance();
        }
        else if (currentChar == '/')
        {
            tokens.push_back({TT_DIV, "/"});
            advance();
        }
        else if (currentChar == '(')
        {
            tokens.push_back({TT_LPAREN, "("});
            advance();
        }
        else if (currentChar == ')')
        {
            tokens.push_back({TT_RPAREN, ")"});
            advance();
        }
        else if (std::isdigit(static_cast<unsigned char>(currentChar)) || currentChar == '.')
        {
            makeNumber();
        }
        else
        {
            std::cerr << "Lexer error: unexpected character '" << currentChar << "'\n";
            advance();
        }
    }
}

void Lexer::makeNumber()
{
    int dotCount = 0;
    std::string numString;

    while (pos < text.size() &&
           (std::isdigit(static_cast<unsigned char>(currentChar)) || currentChar == '.'))
    {
        if (currentChar == '.')
        {
            if (dotCount == 1)
            {
                break;
            }
            dotCount++;
            numString += '.';
        }
        else
        {
            numString += currentChar;
        }
        advance();
    }

    if (dotCount == 0)
    {
        tokens.push_back({TT_INT, numString});
    }
    else
    {
        tokens.push_back({TT_FLOAT, numString});
    }
}

void Lexer::toString() const
{
    for (const auto& tok : tokens)
    {
        std::cout << tok.first << " (" << tok.second << ")\n";
    }
}