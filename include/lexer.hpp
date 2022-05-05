#include <string>
#include <vector>
//#include <map>
//#include <regex>
//#include <iostream>

struct token
{
	std::string type;
	std::string value;
};

token * tokenize(std::string type, std::string value);

std::string getString(char quote, std::string sub);

std::string getNumber(std::string sub);

std::string getSymbol(std::string sub);

std::vector<token *> lexer(std::string *input);