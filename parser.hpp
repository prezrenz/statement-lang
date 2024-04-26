#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "token.hpp"

#include <vector>

class Parser
{
    public:
        Parser(std::vector<Token*> _tokens): tokens(_tokens) {};
        std::vector<Stmt*> parse();
    private:
        std::vector<Token*> tokens;
        std::vector<Stmt*> stmts;
        std::vector<Token*>::iterator current = tokens.begin();

        void advance();
        bool match(TokenTypes type);

        Stmt* parseStmt();
        DeclStmt* parseDeclStmt();
        Stmt* parseAssignStmt();
        Stmt* parsePrintStmt();
        Stmt* parseInputStmt();

        Expr* parseExpr();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* primary();
};

#endif
