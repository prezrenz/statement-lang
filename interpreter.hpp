#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "ast.hpp"
#include <any>
#include <map>
#include <string>
#include <vector>

class Environment
{
    public:

        Environment();

        void addVariable(std::string name, std::any value);
        void addLabel(std::string label, int position);

        // FIX: Should check if label or variable exists, throw error if not
        std::any getVariable(std::string name) { return variables[name]; }
        int getLabel(std::string label) { return labels[label]; }

    private:

        std::map<std::string, std::any> variables;
        std::map<std::string, int> labels;
};

class Interpreter
{
    public:

        Interpreter(std::vector<Stmt*> _statements): statements(_statements) {}
        void interpret();

    private:
        
        std::vector<Stmt*> statements;
        int current = 0;
        Environment* envir = new Environment(); 
                
};

#endif
