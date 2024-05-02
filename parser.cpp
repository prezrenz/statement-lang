#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <iostream>
#include <ostream>
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
    catch (std::string& e)
    {
        // Error handling and reporting
        std::cout << e << std::endl;
    }

    return stmts;
}

void Parser::advance()
{
    previous = **current;
    current++;
}

bool Parser::match(TokenTypes type)
{
    Token tok = **current;

    if(tok.type == type)
    {
        advance();
        return true;
    }

    return false;
}

Stmt* Parser::parseStmt()
{
    if(match(TOK_VAR)) return parseDeclStmt();
    if(match(TOK_PRINT)) return parsePrintStmt();
    if(match(TOK_WORD)) return parseWordStmt();

    throw std::string("Parser Error: invalid statement") + std::string("'") + (**current).token + std::string("'");
}

Stmt* Parser::parseDeclStmt()
{
    std::string name;
    Expr* expr;

    if(match(TOK_WORD))
    {
        name = previous.token;
    }
    else
    {
        throw std::string("Parser Error: expected word after var keyword");
    }

    if(match(TOK_EQUAL))
    {
        expr = parseExpr(); 
    }
    else
    {
        expr = 0; // TODO: should new variables default to a null value?
    }

    DeclStmt* newDeclStmt = new DeclStmt(name, expr);

    if(!match(TOK_SCOLON))
    {
        throw std::string("Parser Error: expected semicolon at the end of statement");
    }
   
    return newDeclStmt;
}

Stmt* Parser::parseWordStmt()
{
    std::string name = previous.token;

    if(match(TOK_EQUAL))
    {
        Expr* expr;
        expr = parseExpr();

        if(!match(TOK_SCOLON))
        {
            throw std::string("Parser Error: expected semicolon at the end of assign statement");
        }

        return new AssignStmt(name, expr);
    }
    else if(match(TOK_COLON))
    {
        return new LabelStmt(name);
    }
    else
    {
        throw std::string("Parser Error: expected ':' or '=' after word, for label or assign statements respectively");
    }
}

Stmt* Parser::parsePrintStmt()
{
    Expr* expr;

    expr = parseExpr();
    PrintStmt* newPrintStmt = new PrintStmt(expr);

    if(!match(TOK_SCOLON))
    {
        throw std::string("Parser Error: expected semicolon at the end of print statement");
    }

    return newPrintStmt;
}
    
Stmt* Parser::parseInputStmt()
{
    // TODO
}


Expr* Parser::parseExpr()
{
    return equality();
}

Expr* Parser::equality()
{
    Expr* left = comparison();

    while(match(TOK_EEQUAL) || match(TOK_NEQUAL))
    {
        Token op = previous;

        Expr* right = comparison();
        left = new BinaryOpExpr(op.token, left, right);
    }

    return left;
}

Expr* Parser::comparison()
{
    Expr* left = term();

    while(match(TOK_LESS_THAN) || match(TOK_GREATER_THAN) || match(TOK_EGREATER) || match(TOK_ELESS))
    {
        Token op = previous;

        Expr* right = term();
        left = new BinaryOpExpr(op.token, left, right);
    }

    return left;
}

Expr* Parser::term()
{
    Expr* left = factor();

    while(match(TOK_PLUS) || match(TOK_MINUS))
    {
        Token op = previous;

        Expr* right = factor();
        left = new BinaryOpExpr(op.token, left, right);
    }

    return left;
}

Expr* Parser::factor()
{
    Expr* left = primary();

    while(match(TOK_STAR) || match(TOK_SLASH))
    {
        Token op = previous;

        Expr* right = primary();
        left = new BinaryOpExpr(op.token, left, right);
    }

    return left;
}

Expr* Parser::primary()
{
    if(match(TOK_NUM))
    {
         return new NumExpr(previous.num_literal);
    }
    else if(match(TOK_STR))
    {
        return new StrExpr(previous.token); 
    }
    else if(match(TOK_WORD))
    {
        return new VarExpr(previous.token);
    }
    else if(match(TOK_TRUE))
    {
        return new BoolExpr(true);
    }
    else if(match(TOK_FALSE))
    {
        return new BoolExpr(false);
    }
    else if(match(TOK_NONE))
    {
        return new NoneExpr();
    }
    else
    {
        throw std::string("Parser Error: invalid expression");
        /*std::cout << (**current).token << std::endl;
        advance();
        return new StrExpr(previous.token);*/ // catch all till other primaries are implemented
    }
}
