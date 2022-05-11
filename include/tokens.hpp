#include <string>
struct token
{
	std::string type;
	std::string value;
};


token * tokenize(std::string type, std::string value);