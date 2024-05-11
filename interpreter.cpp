#include "interpreter.hpp"

void Interpreter::interpret()
{
    while(current != statements.size()-1)
    {
        statements[current]->execute();
    }
}
