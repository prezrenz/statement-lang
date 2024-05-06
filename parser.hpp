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
        Token previous;

        void advance();
        bool match(TokenTypes type);

        Stmt* parseStmt();
        Stmt* parseDeclStmt();
        Stmt* parseWordStmt();
        Stmt* parsePrintStmt();
        Stmt* parseInputStmt();
        Stmt* parseIfStmt();

        Expr* parseExpr();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* primary();
};

#endif
