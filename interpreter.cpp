#include "interpreter.hpp"
#include "ast.hpp"
#include <any>

void Environment::addVariable(std::string name, std::any value)
{
    variables.insert({name, value});
}

void Environment::addLabel(std::string label, int position)
{
    labels.insert({label, position});
}

void Interpreter::interpret()
{
    while(current != statements.size()-1)
    {
        statements[current]->execute();
    }
}

std::any DeclStmt::execute(std::map<std::string, std::any>* environment)
{
    // TODO
}
