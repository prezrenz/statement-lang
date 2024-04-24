#ifndef AST_HPP
#define AST_HPP

#include <string>

struct Expr {};
struct Stmt {};

struct VarStmt: Stmt
{
    std::string name;
    Expr value;
};

struct PrintStmt: Stmt
{
    Expr value;
};

template<typename T>
struct PrimaryExpr: Expr
{
    std::string exprType = "PrimaryExpr";
    T value;
};

struct BinaryExpr: Expr
{
    std::string exprType = "BinaryExpr";
    std::string operation;
    Expr left;
    Expr right;
};

#endif
