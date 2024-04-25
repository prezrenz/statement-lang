#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

#include "token.hpp"
#include "scanner.hpp"
#include "ast.hpp"
#include "parser.hpp"

using namespace std;

std::string tokenStrings[28] = {
    "TOK_WORD", "TOK_STR", "TOK_NUM",
    "TOK_TRUE", "TOK_FALSE", "TOK_NONE",
    
    "TOK_EQUAL", "TOK_EEQUAL", "TOK_LESS_THAN",
    "TOK_GREATER_THAN", "TOK_EGREATER", "TOK_ELESS",

    "TOK_PLUS", "TOK_MINUS", "TOK_STAR",
    "TOK_SLASH", "TOK_BANG", "TOK_SCOLON",
    "TOK_COLON", "TOK_QUOTE", "TOK_LPAREN",
    "TOK_RPAREN",

    "TOK_PRINT", "TOK_VAR", "TOK_INPUT",
    "TOK_IF", "TOK_ELSE", "TOK_LABEL"
};

int main(int argc, char** argv)
{
   if(argc <= 1)
    {
        cout << "Usage: statement <program>";
        return 1;
    }

    ifstream file;
    vector<Token*> tokens;
    vector<Stmt*> statements;

    file.open(argv[1]);

    if(!file.is_open())
    {
        cout << "Error: file " << "\"" << argv[1] << "\"" << " not found, exiting...";
        return 1;
    }

    Scanner scanner(&file);
    tokens = scanner.scan();

    Parser parser(tokens);
    statements = parser.parse();

    if(tokens.empty()) return 1; 

    for (size_t i = 0; i < tokens.size(); i++)
    {
        cout << tokenStrings[tokens[i]->type] << endl;
        cout << tokens[i]->token << endl;
        cout << tokens[i]->num_literal << endl;
        cout << "----------------" << endl;
    }

    return 0;
}
