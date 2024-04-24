#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>
#include <vector>
#include "token.hpp"

class Scanner
{
    public:
        Scanner(std::ifstream* file);
        std::vector<Token*> scan();
    private:
        std::ifstream* program;
        int line;
        char current;
        std::vector<Token*> tokens;

        void advance();
        TokenTypes matchReservedWord(std::string token);
        void createToken(TokenTypes type, std::string token);
        void createSingleToken(TokenTypes type, std::string token);
        void createWordToken(std::string token);
        void createIntToken(std::string token);
        void createStringToken(std::string token);
        void scanToken();
};

#endif
