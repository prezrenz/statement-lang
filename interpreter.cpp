#include "interpreter.hpp"
#include "ast.hpp"
#include <any>
#include <cctype>
#include <iostream>
#include <string>
#include <typeinfo>

bool isNumber(const std::string& a)
{
    std::string::const_iterator it = a.begin();
    while(it != a.end() && std::isdigit(*it)) ++it;
    return !a.empty() && it == a.end();
}

void Environment::addVariable(std::string name, std::any value)
{
    variables.insert({name, value});
}

void Environment::addLabel(std::string label, int position)
{
    labels.insert({label, position});
}

void Interpreter::scanLabels()
{
    while(envir->current <= statements.size()-1)
    {
        if(typeid(*statements[envir->current]) == typeid(LabelStmt))
        {
            statements[envir->current]->execute(envir);
        }
        envir->current++;
    }

    envir->current = 0;
}

void Interpreter::interpret()
{
    try
    {
        scanLabels();
        while(envir->current <= statements.size()-1)
        {
            statements[envir->current]->execute(envir);
            envir->current++;
        }
    }
    catch(std::bad_cast e)
    {
        std::cout << e.what();
    }
}

void DeclStmt::execute(Environment* environment)
{

    std::any value = expr->execute(environment);
    environment->addVariable(name, value);
}

void AssignStmt::execute(Environment* environment)
{
    std::any value = expr->execute(environment);
    environment->setVariable(name, value);
}

void PrintStmt::execute(Environment* environment)
{
    std::any value = expr->execute(environment);
    std::string toPrint;

    if(value.type() == typeid(int))
    {
        toPrint = std::to_string(std::any_cast<int>(value));
    }
    else
    {
        toPrint = std::any_cast<std::string>(value);
    }

    std::cout << toPrint << std::endl;
}

void InputStmt::execute(Environment* environment)
{
    std::string input;
    std::cin >> input;

    if(isNumber(input))
    {
        environment->setVariable(var, std::stoi(input));
    }
    else
    {
        environment->setVariable(var, input);
    }

}

void LabelStmt::execute(Environment* environment)
{
    environment->addLabel(name, environment->current);
}

void IfStmt::execute(Environment* environment)
{
    std::any expr = condition->execute(environment);
    bool cond;

    if(expr.type() == typeid(int) || expr.type() == typeid(bool))
    {
        cond = std::any_cast<bool>(expr);
    }
    else if(expr.type() == typeid(nullptr))
    {
        cond = false;
    }
    else
    {
        cond = false; // TODO: throw error if string
    }

    if(cond)
    {
        environment->current = environment->getLabel(label);
    }
    else
    {
        environment->current = environment->getLabel(elseif);
    }

}

std::any NumExpr::execute(Environment* environment)
{
    return value;
}

std::any StrExpr::execute(Environment* environment)
{
    return value;
}

std::any BoolExpr::execute(Environment* environment)
{
    return value;
}

std::any NoneExpr::execute(Environment* environment)
{
    return value;
}

std::any VarExpr::execute(Environment* environment)
{
    return environment->getVariable(name); 
}

std::any GroupingExpr::execute(Environment* environment)
{
    return expr->execute(environment);
}

std::any BinaryOpExpr::execute(Environment* environment)
{
    std::any leftVal = left->execute(environment);
    std::any rightVal = right->execute(environment);
    
    if(leftVal.type() == typeid(" ") && rightVal.type() == typeid(" "))
    {
        return std::any_cast<std::string>(leftVal) + std::any_cast<std::string>(leftVal);
    }
    else if(leftVal.type() == typeid(int) && rightVal.type() == typeid(int))
    {
        if(op == "+")
        {
            return  std::any_cast<int>(leftVal) + std::any_cast<int>(rightVal);
        }
        else if(op == "-")
        {
            return  std::any_cast<int>(leftVal) - std::any_cast<int>(rightVal);
        }
        else if(op == "/")
        {
            return  std::any_cast<int>(leftVal) / std::any_cast<int>(rightVal);
        }
        else if(op == "*")
        {
            return  std::any_cast<int>(leftVal) * std::any_cast<int>(rightVal);
        }
        else if(op == ">")
        {
            return  std::any_cast<int>(leftVal) > std::any_cast<int>(rightVal);
        }
        else if(op == "<")
        {
            return  std::any_cast<int>(leftVal) < std::any_cast<int>(rightVal);
        }
        else if(op == ">=")
        {
            return  std::any_cast<int>(leftVal) >= std::any_cast<int>(rightVal);
        }
        else if(op == "<=")
        {
            return  std::any_cast<int>(leftVal) <= std::any_cast<int>(rightVal);
        }
        else if(op == "==")
        {
            return  std::any_cast<int>(leftVal) == std::any_cast<int>(rightVal);
        }
        else if(op == "!=")
        {
            return  std::any_cast<int>(leftVal) != std::any_cast<int>(rightVal);
        }
    }
}
