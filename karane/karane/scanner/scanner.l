%option noyywrap c++

%%

[a-zA-Z]+      { return 1; }
[0-9]+         { return 2; }
[ \t\r\n]+     { /* ignore whitespace */ }
.              {
                   std::cerr << "unrecognized character: " << yytext << '\n';
                   return -1;
               }

%%
