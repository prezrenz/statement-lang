#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "ast.hpp"
#include <vector>

class Interpreter
{
    public:

        Interpreter(std::vector<Stmt*> _statements): statements(_statements) {}
        void interpret();
        ~Interpreter() {}

    private:
        
        std::vector<Stmt*> statements;
        Environment* envir = new Environment();

        void scanLabels();
};

#endif
