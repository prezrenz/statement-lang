#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

enum TokenTypes
{
    TOK_WORD, TOK_STR, TOK_NUM,
    TOK_TRUE, TOK_FALSE, TOK_NONE,
    
    TOK_EQUAL, TOK_EEQUAL, TOK_LESS_THAN,
    TOK_GREATER_THAN, TOK_EGREATER, TOK_ELESS,

    TOK_PLUS, TOK_MINUS, TOK_STAR,
    TOK_SLASH, TOK_BANG, TOK_SCOLON,
    TOK_COLON, TOK_QUOTE, TOK_LPAREN,
    TOK_RPAREN,

    TOK_PRINT, TOK_VAR, TOK_INPUT,
    TOK_IF, TOK_ELSE, TOK_LABEL,
};

string tokenStrings[28] = {
    "TOK_WORD", "TOK_STR", "TOK_NUM",
    "TOK_TRUE", "TOK_FALSE", "TOK_NONE",
    
    "TOK_EQUAL", "TOK_EEQUAL", "TOK_LESS_THAN",
    "TOK_GREATER_THAN", "TOK_EGREATER", "TOK_ELESS",

    "TOK_PLUS", "TOK_MINUS", "TOK_STAR",
    "TOK_SLASH", "TOK_BANG", "TOK_SCOLON",
    "TOK_COLON", "TOK_QUOTE", "TOK_LPAREN",
    "TOK_RPAREN",

    "TOK_PRINT", "TOK_VAR", "TOK_INPUT",
    "TOK_IF", "TOK_ELSE", "TOK_LABEL"
};

struct Token
{
    TokenTypes type;
    string token;
    int num_literal;
};

class Scanner
{
    public:
        Scanner(ifstream* file)
        {
            program = file;
        }

        vector<Token*> scan()
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

    private:
        ifstream* program;
        int line;
        char current;
        vector<Token*> tokens; 

        void advance()
        {
            current = program->get();
        }

        TokenTypes matchReservedWord(string token)
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

        void createToken(TokenTypes type, string token)
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

        void createSingleToken(TokenTypes type, string token)
        {
            token += current;
            advance();

            createToken(type, token);
        }

        void createWordToken(string token)
        {
            while (isalpha(current))
            {
                token += current;
                advance();
            }

            TokenTypes type = matchReservedWord(token);
            
            createToken(type, token);
        }

        void createIntToken(string token)
        {
            while (isdigit(current))
            {
                token += current;
                advance();
            }

            createToken(TOK_NUM, token);
        }

        void createStringToken(string token)
        {
            while(current != '"' && !program->eof())
            {
                token += current;
                advance();
            }

            createToken(TOK_STR, token);
        }

        void scanToken()
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
                    createSingleToken(TOK_EQUAL, token);
                    break;
                case '>':
                    createSingleToken(TOK_GREATER_THAN, token);
                    break;
                case '<':
                    createSingleToken(TOK_LESS_THAN, token);
                    break;
                case '!':
                    createSingleToken(TOK_BANG, token);
                    break;
                case ';':
                    createSingleToken(TOK_COLON, token);
                    break;
                case '(':
                    createSingleToken(TOK_LPAREN, token);
                    break;
                case ')':
                    createSingleToken(TOK_RPAREN, token);
                    break;
                case '"':
                    createSingleToken(TOK_QUOTE, token);
                    createStringToken(token);
                    // TODO: should check if eof, if so report error unterminated string

                    if(program->eof())
                    {
                        throw "Scanner Error: unterminated string";
                    }

                    createSingleToken(TOK_QUOTE, token); 
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
};

int main(int argc, char** argv)
{
   if(argc <= 1)
    {
        cout << "Usage: statement <program>";
        return 1;
    }

    ifstream file;
    vector<Token*> tokens;

    file.open(argv[1]);

    if(!file.is_open())
    {
        cout << "Error: file " << "\"" << argv[1] << "\"" << " not found, exiting...";
        return 1;
    }

    Scanner scanner(&file);
    tokens = scanner.scan();

    if(tokens.empty()) return 1; 

    for (int i = 0; i < tokens.size(); i++)
    {
        cout << tokenStrings[tokens[i]->type] << endl;
        cout << tokens[i]->token << endl;
        cout << tokens[i]->num_literal << endl;
        cout << "----------------" << endl;
    }

    return 0;
}
