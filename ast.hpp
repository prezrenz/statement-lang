#ifndef AST_HPP
#define AST_HPP

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
