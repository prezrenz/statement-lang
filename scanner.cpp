#include <iostream>
#include <cctype>
#include "scanner.hpp"
#include "token.hpp"

using namespace std;

Scanner::Scanner(ifstream* file)
{
    program = file;
}

vector<Token*> Scanner::scan()
{
    line = 0;
    current = program->get();

    try
    {
        while(!program->eof())
        {
            scanToken();
        }
    }
    catch (const char* e)
    {
        cout << e << endl;
        tokens.clear();
    }

    return tokens;
}

void Scanner::advance()
{
    previous = current;
    current = program->get();
}

char Scanner::peek()
{
    char peeked = program->get();
    program->unget();
    return peeked;
}

TokenTypes Scanner::matchReservedWord(string token)
{
    if(token == "var")
    {
        return TOK_VAR;
    }
    else if(token == "print")
    {
        return TOK_PRINT;
    }
    else if(token == "input")
    {
        return TOK_INPUT;
    }
    else if(token == "true")
    {
        return TOK_TRUE;
    }
    else if(token == "false")
    {
        return TOK_FALSE;
    }
    else if(token == "none")
    {
        return TOK_NONE;
    }
    else if(token == "if")
    {
        return TOK_IF;
    }
    else if(token == "else")
    {
        return TOK_ELSE;
    }
    else
    {
        return TOK_WORD;
    }
}

void Scanner::createToken(TokenTypes type, string token)
{
    Token* newToken = new Token;

    newToken->type = type;
    newToken->token = token;
    newToken->num_literal = 0;

    if(type == TOK_NUM)
    {
        newToken->num_literal = stoi(token);
    }

    tokens.push_back(newToken);
}

void Scanner::createSingleToken(TokenTypes type, string token)
{
    token += current;
    advance();

    createToken(type, token);
}

void Scanner::createDoubleToken(TokenTypes type, string token)
{
    token += current;
    advance();
    token += current;
    advance();

    createToken(type, token);
}

void Scanner::createWordToken(string token)
{
    while (isalpha(current))
    {
        token += current;
        advance();
    }

    TokenTypes type = matchReservedWord(token);
            
    createToken(type, token);
}

void Scanner::createIntToken(string token)
{
    while (isdigit(current))
    {
        token += current;
        advance();
    }

    createToken(TOK_NUM, token);
}

void Scanner::createStringToken(string token)
{
    while(current != '"' && !program->eof())
    {
        token += current;
        advance();
    }

    createToken(TOK_STR, token);
}

void Scanner::scanToken()
{
    string token;
    switch (current)
    {
        case '+':
            createSingleToken(TOK_PLUS, token);
            break;
        case '-':
            createSingleToken(TOK_MINUS, token);
            break;
        case '/':
            createSingleToken(TOK_SLASH, token);
            break;
        case '*':
            createSingleToken(TOK_STAR, token);
            break;
        case '=':
            if(peek() == '=')
            {
                createDoubleToken(TOK_EEQUAL, token);
            }
            else
            {
                createSingleToken(TOK_EQUAL, token);
            }
            break;
        case '>':
            if(peek() == '=')
            {
                createDoubleToken(TOK_EGREATER, token);
            }
            else
            {
                createSingleToken(TOK_GREATER_THAN, token);
            }
            break;
        case '<':
            if(peek() == '=')
            {
                createDoubleToken(TOK_ELESS, token);
            }
            else
            {
                createSingleToken(TOK_LESS_THAN, token);
            }
            break;
        case '!':
            if(peek() == '=')
            {
                createDoubleToken(TOK_NEQUAL, token);
            }
            else
            {
                throw "Scanner Error: lone '!' is not a valid token in language";
            }
            break;
        case ';':
            createSingleToken(TOK_SCOLON, token);
            break;
        case ':':
            createSingleToken(TOK_COLON, token);
            break;
        case '(':
            createSingleToken(TOK_LPAREN, token);
            break;
        case ')':
            createSingleToken(TOK_RPAREN, token);
            break;
        case '"':
            // NOTE: should quotes be scanned and made to tokens for the parser?
            advance(); //createSingleToken(TOK_QUOTE, token);
            createStringToken(token);
                    
            if(program->eof())
            {
                throw "Scanner Error: unterminated string";
            }

            advance(); //createSingleToken(TOK_QUOTE, token); 
            break;
        case ' ':
        case '\n':
            advance();
            break;

        default:
            if(isalpha(current))
            {
                createWordToken(token);
            }
                    
            if(isdigit(current))
            {
                createIntToken(token);
            }
    }
}
