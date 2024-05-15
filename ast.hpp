#ifndef AST_HPP
#define AST_HPP

#include <any>
#include <cstddef>
#include <map>
#include <string>

class Environment
{
    public:

        Environment() {};

        int current = 0; // FIXME: this should be in the interpreter...                

        void addVariable(std::string name, std::any value);
        void addLabel(std::string label, int position);

        // FIX: Should check if label or variable exists, throw error if not
        std::any getVariable(std::string name) { return variables[name]; }
        void setVariable(std::string name, std::any value) { variables[name] = value; }
        int getLabel(std::string label) { return labels[label]; }

        ~Environment() {}

    private:

        std::map<std::string, std::any> variables;
        std::map<std::string, int> labels;   
};

class Expr
{
    public:
        virtual std::string stringify() = 0;
        virtual std::any execute(Environment* environment) = 0; // Only VarExpr needs this, poor design has led to this
        virtual ~Expr() {}
};

class Stmt
{
    public:
        virtual std::string stringify() = 0;
        virtual void execute(Environment* environment) = 0;
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

        void execute(Environment* environment);

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

        void execute(Environment* environment);

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

        void execute(Environment* environment);

        ~PrintStmt() {}

    private:
        Expr* expr;
};

class InputStmt: public Stmt
{
    public:
        InputStmt(std::string _var): var(_var) {}

        std::string stringify()
        {
            return "input " + var;
        }

        void execute(Environment* environment);

        ~InputStmt() {}

    private:
        std::string var;
};

class LabelStmt: public Stmt
{
    public:
        LabelStmt(std::string _name): name(_name) {}

        std::string stringify()
        {
            return name + ": ";
        }

        void execute(Environment* environment);

        ~LabelStmt(){}

    private:
        std::string name;
};

class IfStmt: public Stmt
{
    public:
        IfStmt(std::string _label, std::string _elseif, Expr* _condition): label(_label), elseif(_elseif), condition(_condition) {}
        
        std::string stringify()
        {
            if(!elseif.empty())
            {
                return "if " + condition->stringify() + " " + label + " else " + elseif;
            }
            return "if " + condition->stringify() + " " + label;
        }

        void execute(Environment* environment);

        ~IfStmt(){}

    private:
        std::string label;
        std::string elseif;
        Expr* condition;
};

class NumExpr: public Expr
{
    public:
        NumExpr(int _value): value(_value) {}

        std::string stringify()
        {
            return std::to_string(value);
        }

        std::any execute(Environment* environment);

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

        std::any execute(Environment* environment);

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

        std::any execute(Environment* environment);
        std::any execute();

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

        std::any execute(Environment* environment);

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
            return "none";
        }

        std::any execute(Environment* environment);

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

        std::any execute(Environment* environment);

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

        std::any execute(Environment* environment);

        ~GroupingExpr() {}

    private:
        Expr* expr;
};

#endif
