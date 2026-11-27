#include "lexer.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Expr
{
    virtual ~Expr() = default;
};

using ExprPtr = std::unique_ptr<Expr>;

struct NumberNode : Expr
{
    TokenPair token;
    explicit NumberNode(TokenPair t) : token(std::move(t)) {}
};

struct BinOpNode : Expr
{
    ExprPtr left;
    std::string op;
    ExprPtr right;

    BinOpNode(ExprPtr l, std::string o, ExprPtr r)
        : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}
};

void printAST(const Expr* node)
{
    if (!node)
    {
        cout << "<null>";
        return;
    }

    if (const auto* num = dynamic_cast<const NumberNode*>(node))
    {
        cout << num->token.second;
    }
    else if (const auto* bin = dynamic_cast<const BinOpNode*>(node))
    {
        cout << "(" << bin->op << " ";
        printAST(bin->left.get());
        cout << " ";
        printAST(bin->right.get());
        cout << ")";
    }
}

class Parser
{
public:
    std::vector<TokenPair> tokens;
    TokenPair currentToken;
    size_t tokenIndex;
    bool hasError = false;

    explicit Parser(std::vector<TokenPair> t)
        : tokens(std::move(t)), tokenIndex(0)
    {
        if (!tokens.empty())
        {
            currentToken = tokens[0];
        }
        else
        {
            currentToken = {"EOF", ""};
        }
    }

    TokenPair advance()
    {
        tokenIndex++;
        if (tokenIndex < tokens.size())
        {
            currentToken = tokens[tokenIndex];
        }
        else
        {
            currentToken = {"EOF", ""};
        }
        return currentToken;
    }

    ExprPtr parse()
    {
        ExprPtr root = E();
        if (!hasError && currentToken.first != "EOF")
        {
            cerr << "Syntax error: unexpected token '" << currentToken.second << "'\n";
            hasError = true;
        }
        return root;
    }

    // Factor: '(' E ')' | INT | FLOAT
    ExprPtr F()
    {
        if (hasError)
        {
            return nullptr;
        }

        if (currentToken.first == "LPAREN")
        {
            advance(); // consume '('
            ExprPtr inner = E();
            if (hasError)
            {
                return nullptr;
            }

            if (currentToken.first != "RPAREN")
            {
                cerr << "Syntax error: expected ')'\n";
                hasError = true;
                return nullptr;
            }

            advance(); // consume ')'
            return inner;
        }

        if ((currentToken.first == "INT") || (currentToken.first == "FLOAT"))
        {
            TokenPair savedToken = currentToken;
            advance();
            return std::make_unique<NumberNode>(savedToken);
        }

        cerr << "Syntax error: expected number or '('\n";
        hasError = true;
        return nullptr;
    }

    // Term: F (('MUL' | 'DIV') F)*
    ExprPtr T()
    {
        ExprPtr left = F();
        while (!hasError && ((currentToken.first == "MUL") || (currentToken.first == "DIV")))
        {
            std::string opToken = currentToken.first;
            advance();
            ExprPtr right = F();
            if (hasError)
            {
                return nullptr;
            }
            left = std::make_unique<BinOpNode>(std::move(left), opToken, std::move(right));
        }
        return left;
    }

    // Expression: T (('PLUS' | 'MINUS') T)*
    ExprPtr E()
    {
        ExprPtr left = T();
        while (!hasError && ((currentToken.first == "PLUS") || (currentToken.first == "MINUS")))
        {
            std::string opToken = currentToken.first;
            advance();
            ExprPtr right = T();
            if (hasError)
            {
                return nullptr;
            }
            left = std::make_unique<BinOpNode>(std::move(left), opToken, std::move(right));
        }
        return left;
    }
};

int main()
{
    std::string exp;
    std::ifstream file("test.k");

    if (!file.is_open())
    {
        cout << "Not open\n";
        return 1;
    }

    while (std::getline(file, exp))
    {
        Lexer lex(exp);
        lex.makeTokens();

        if (!lex.tokens.empty())
        {
            Parser parser(lex.tokens);
            ExprPtr root = parser.parse();
            if (!parser.hasError && root)
            {
                printAST(root.get());
                cout << "\n";
            }
        }
    }

    return 0;
}