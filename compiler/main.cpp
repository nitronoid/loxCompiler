#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <interpreter.h>


static bool hadError = false;

ErrorReporter errRep;
Interpreter interpreter(errRep);

void run(const std::string &_input)
{ 
  Lexer lexer(errRep);
  std::vector<Token> tokens = lexer.lex(_input);
  Parser parser(tokens, errRep);
  std::vector<std::unique_ptr<Stmt>> test = parser.parse();
  if (!parser.hadError()) interpreter.interpret(test);
}

void runFile(const std::string &_path)
{
  std::ifstream ifs(_path);
  std::string rawProgram( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  run(rawProgram);
}

void runPrompt()
{
  std::string line;
  // exit loop with ctrl + C
  while(true)
  {
    std::cout<<">> ";
    if(std::getline(std::cin, line) && !line.empty())
    {
      run(line);
    }
  }
}


int main(int argc, char* argv[])
{
  if(argc > 2) std::cout<<"Usage: lox [script]\n";

  else if (argc == 2) runFile(argv[1]);

  else runPrompt();

  return 0;
}
