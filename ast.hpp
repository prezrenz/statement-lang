#ifndef AST_HPP
#define AST_HPP

#include <cstddef>
#include <string>

// TODO: Convert to classes and abstract class

class Expr
{
    public:
        virtual std::string stringify() = 0;
        virtual ~Expr() {}
};

class Stmt
{
    public:
        virtual std::string stringify() = 0;
        virtual ~Stmt() {}
};

class DeclStmt: public Stmt
{
    public:
        DeclStmt(std::string _name, Expr* _expr): name(_name), expr(_expr) {}
        std::string stringify()
        {
            return "var " + name + " = " + expr->stringify();
        }

        ~DeclStmt() {}

    private:
        std::string name;
        Expr* expr;
};

class AssignStmt: public Stmt
{
    public:
        AssignStmt(std::string _name, Expr* _expr): name(_name), expr(_expr) {}

        std::string stringify()
        {
            return name + " = " + expr->stringify();
        }

        ~AssignStmt() {}

    private:
        std::string name;
        Expr* expr;
};

class PrintStmt: public Stmt
{
    public:
        PrintStmt(Expr* _expr): expr(_expr) {}
        
        std::string stringify()
        {
            return "print " + expr->stringify();
        }

        ~PrintStmt() {}

    private:
        Expr* expr;
};

class InputStmt: public Stmt
{
    public:
        InputStmt(std::string _name): name(_name) {}

        std::string stringify()
        {
            return "input " + name;
        }

        ~InputStmt() {}

    private:
        std::string name;
};

class LabelStmt: public Stmt
{
    public:
        LabelStmt(std::string _name): name(_name) {}

        std::string stringify()
        {
            return name;
        }

        ~LabelStmt(){}

    private:
        std::string name;
};

class IfStmt: public Stmt
{
    public:
        IfStmt(LabelStmt _label, LabelStmt _elseif, Expr* _condition): label(_label), elseif(_elseif), condition(_condition) {}

    private:
        LabelStmt label;
        LabelStmt elseif;
        Expr* condition;
};

/*
template<typename T>
class PrimaryExpr: public Expr
{
    public:
        PrimaryExpr(T _value): value(_value) {}

        std::string stringify()
        {
            return std::to_string(value);
        }

        ~PrimaryExpr() {}

    private:
        T value;
};*/

class NumExpr: public Expr
{
    public:
        NumExpr(int _value): value(_value) {}

        std::string stringify()
        {
            return std::to_string(value);
        }

        ~NumExpr() {}

    private:
        int value;
};

class StrExpr: public Expr
{
    public:
        StrExpr(std::string _value): value(_value) {}

        std::string stringify()
        {
            return value;
        }

        ~StrExpr() {}

    private:
        std::string value;
};

class VarExpr: public Expr
{
    public:
        VarExpr(std::string _name): name(_name) {}

        std::string stringify()
        {
            return name;
        }

        ~VarExpr() {}

    private:
        std::string name;
};

class BoolExpr: public Expr
{
    public:
        BoolExpr(bool _value): value(_value) {}

        std::string stringify()
        {
            return std::to_string(value);
        }

        ~BoolExpr() {}

    private:
        bool value;
};

class NoneExpr: public Expr // NOTE: looks dangerous
{
    public:
        NoneExpr() {}

        std::string stringify()
        {
            return "null";
        }

        ~NoneExpr() {}

    private:
        std::nullptr_t value;
};


class BinaryOpExpr: public Expr
{
    public:
        BinaryOpExpr(std::string _op, Expr* _left, Expr* _right): op(_op), left(_left), right(_right) {}
    
        std::string stringify()
        {
            return "( " + op + " " + left->stringify() + " " + right->stringify() + " )";
        }

        ~BinaryOpExpr() {}

    private:
        std::string op;
        Expr* left;
        Expr* right;
};

class GroupingExpr: public Expr
{
    public:
        GroupingExpr(Expr* _expr): expr(_expr) {}
    
        std::string stringify()
        {
            return "( " + expr->stringify() + " )";
        }

        ~GroupingExpr() {}

    private:
        Expr* expr;
};

#endif
