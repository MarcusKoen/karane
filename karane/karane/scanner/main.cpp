#include <FlexLexer.h>
#include <iostream>

int main() {
    FlexLexer* lexer = new yyFlexLexer;
    int tok;
    while ((tok = lexer->yylex()) != 0) {
        if (tok < 0) {
            return 1;
        }
        std::cout << "token " << tok << ": " << lexer->YYText() << '\n';
    }
    delete lexer;
    return 0;
}
