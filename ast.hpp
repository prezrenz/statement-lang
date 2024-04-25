#ifndef AST_HPP
#define AST_HPP

#include <string>

// TODO: Convert to classes and abstract class

class Expr
{
    public:
        virtual ~Expr() = 0;
};

class Stmt
{
    public:
        virtual ~Stmt() = 0;
};

class DeclStmt: Stmt
{
    DeclStmt(std::string _name, Expr* _expr): name(_name), expr(_expr) {}

    std::string name;
    Expr* expr;
};

class AssignStmt: Stmt
{
    AssignStmt(std::string _name, Expr* _expr): name(_name), expr(_expr) {}    

    std::string name;
    Expr* expr;
};

class PrintStmt: Stmt
{
    PrintStmt(Expr* _expr): expr(_expr) {}

    Expr* expr;
};

class InputStmt: Stmt
{
    InputStmt(std::string _name): name(_name) {}

    std::string name;
};

template<typename T>
class PrimaryExpr: Expr
{
    PrimaryExpr(T _value): value(_value) {}

    T value;
};

class BinaryOpExpr: Expr
{
    BinaryOpExpr(char _op, Expr* _left, Expr* _right): op(_op), left(_left), right(_right) {}

    char op;
    Expr* left;
    Expr* right;
};

class GroupingExpr: Expr
{
    GroupingExpr(Expr* _expr): expr(_expr) {}

    Expr* expr;
};

#endif
