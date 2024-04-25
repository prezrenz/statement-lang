#ifndef AST_HPP
#define AST_HPP

#include <string>

// TODO: Convert to classes and abstract class

class Expr
{
    virtual ~Expr() = 0;
};

class Stmt
{
    virtual ~Stmt() = 0;
};

class DeclStmt: Stmt
{
    std::string name;
    Expr* expr;

    ~DeclStmt();
};

class AssignStmt: Stmt
{
    std::string name;
    Expr* expr;

    ~AssignStmt();
};

class PrintStmt: Stmt
{
    Expr* expr;

    ~PrintStmt();
};

class InputStmt: Stmt
{
    std::string name;
    
    ~InputStmt();
};

template<typename T>
class PrimaryExpr: Expr
{
    T value;
    
    ~PrimaryExpr();
};

class BinaryOpExpr: Expr
{
    char op;
    Expr* left;
    Expr* right;
    
    ~BinaryOpExpr();
};

class GroupingExpr: Expr
{
    Expr* expr;

    ~GroupingExpr();
};

#endif
