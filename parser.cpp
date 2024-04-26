#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<Stmt*> Parser::parse()
{
    try
    {
        while(current != tokens.end())
        {
            stmts.push_back(parseStmt());
        }
    }
    catch (const char* e)
    {
        // Error handling and reporting
    }

    return stmts;
}

void Parser::advance()
{
    current++;
}

bool Parser::match(TokenTypes type)
{
    Token tok = **current;

    if(tok.type == type) return true;

    return false;
}

Stmt* Parser::parseStmt()
{
    if((*current)->type == TOK_VAR) return parseDeclStmt();
}

Stmt* Parser::parseDeclStmt()
{
    advance();

    std::string name;
    Expr* expr;

    if(match(TOK_WORD))
    {
        name = (*current)->token;
        advance();
    }
    else
    {
        // error here, expected name
    }

    if(match(TOK_EQUAL))
    {
        advance();

        
    }

    DeclStmt* newDeclStmt = new DeclStmt(name, expr);

    return newDeclStmt;
}

Stmt* Parser::parseAssignStmt()
{

}

Stmt* Parser::parsePrintStmt()
{

}
    
Stmt* Parser::parseInputStmt()
{

}


Expr* Parser::parseExpr()
{
    return equality();
}

Expr* Parser::equality()
{
    Expr* left = comparison();

    while(match(TOK_EEQUAL)) // TODO: Fix scanner to include != token
    {
        Token op = **current;
        advance();

        Expr* right = comparison();
        left = new BinaryOpExpr(op.token, left, right);
    }
}

Expr* Parser::comparison()
{

}

Expr* Parser::term()
{

}

Expr* Parser::factor()
{

}

Expr* Parser::primary()
{

}
