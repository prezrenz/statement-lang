#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum TokenTypes
{
    TOK_WORD, TOK_STR, TOK_NUM,
    TOK_TRUE, TOK_FALSE, TOK_NONE,
    
    TOK_EQUAL, TOK_EEQUAL, TOK_LESS_THAN,
    TOK_GREATER_THAN, TOK_EGREATER, TOK_ELESS,
    TOK_NEQUAL,

    TOK_PLUS, TOK_MINUS, TOK_STAR,
    TOK_SLASH, TOK_SCOLON,
    TOK_COLON, TOK_QUOTE, TOK_LPAREN,
    TOK_RPAREN,

    TOK_PRINT, TOK_VAR, TOK_INPUT,
    TOK_IF, TOK_ELSE, TOK_LABEL,
};

struct Token
{
    TokenTypes type;
    std::string token;
    int num_literal;
    int line;
};

#endif
