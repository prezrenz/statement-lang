#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Scanner
{
    public:
        Scanner(ifstream* file)
        {
            program = file;
        }

        vector<string> scan()
        {
            line = 0;
            current = program->get();

            while(!program->eof())
            {
                scanToken();
            }

            return tokens;
        }

    private:
        ifstream* program;
        int line;
        char current;
        vector<string> tokens;

        void advance()
        {
            current = program->get();
        }

        void createToken(string token)
        {
            token += current;
            tokens.push_back(token);
            advance();
        }

        void createWordToken(string* token)
        {
            while (isalpha(current))
            {
                *token += current;
                advance();
            }
        }

        void createIntToken(string* token)
        {
            while (isdigit(current))
            {
                *token += current;
                advance();
            }
        }

        void createStringToken(string* token)
        {
            while(current != '"' && !program->eof())
            {
                *token += current;
                advance();
            }
        }

        void scanToken()
        {
            string token;
            switch (current)
            {
                case '+':
                case '-':
                case '/':
                case '*':
                case '=':
                case '>':
                case '<':
                case '!':
                case ';':
                    createToken(token);
                    break;
                case '"':
                    advance();
                    createStringToken(&token);
                    advance();
                    tokens.push_back(token);
                    break;
                case ' ':
                case '\n':
                    advance();
                    break;

                default:
                    if(isalpha(current))
                    {
                        createWordToken(&token);
                        tokens.push_back(token);
                    }
                    
                    if(isdigit(current))
                    {
                        createIntToken(&token);
                        tokens.push_back(token);
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
    vector<string> tokens;

    file.open(argv[1]);

    if(!file.is_open())
    {
        cout << "Error: file " << "\"" << argv[1] << "\"" << " not found, exiting...";
        return 1;
    }

    Scanner scanner(&file);
    tokens = scanner.scan();

    for (int i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i] << endl;
    }

    return 0;
}
