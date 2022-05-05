#include <string>
#include <vector>
#include "tokens.hpp"
std::string getString(char quote, std::string sub);

std::string getNumber(std::string sub);

std::string getSymbol(std::string sub);

std::vector<token *> lexer(std::string *input);